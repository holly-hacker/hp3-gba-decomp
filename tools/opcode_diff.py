#!/usr/bin/env python3
"""Opcode-only diff between a real function's ground-truth disassembly and a
candidate object file, for iterating on a match.

Byte/instruction-count size is not monotonic with correctness while matching
a function (see .claude/skills/match-function/SKILL.md): a structurally
wrong candidate can hit the target byte count by coincidence, and a genuine
fix can move the byte count away from the target while making the candidate
strictly closer in every real sense. This compares mnemonic sequences with
difflib so insertions/deletions realign instead of cascading into a wall of
noise, and normalizes purely cosmetic differences (a disassembler's `.n`
narrow-encoding suffix, and the `bhs`/`bcs`, `blo`/`bcc` condition-code
aliases) before counting diff groups.

Usage: opcode_diff.py <ver> <function-name> <object-file>

<function-name> must appear as a `thumb_func_start`/`arm_func_start` label in
build/<ver>/full_disasm.s (run `just disasm-compare` first if that's stale).
The real function's extent is taken as everything between that label and the
next function-start label. <object-file> is disassembled with
arm-none-eabi-objdump -dr.
"""
import difflib
import re
import subprocess
import sys

FUNC_START_RE = re.compile(r"^\s*(?:thumb|arm)_func_start\s+(\S+)")


def normalize(mnemonic: str) -> str:
    mnemonic = re.sub(r"\.n$", "", mnemonic)
    return {"bhs": "bcs", "blo": "bcc"}.get(mnemonic, mnemonic)


def real_ops(ver: str, name: str) -> list[str]:
    path = f"build/{ver}/full_disasm.s"
    lines = open(path).readlines()
    starts = [(i, m.group(1)) for i, l in enumerate(lines)
              if (m := FUNC_START_RE.match(l))]
    idx = next((i for i, (_, n) in enumerate(starts) if n == name), None)
    if idx is None:
        sys.exit(f"{name!r} not found as a func_start label in {path}")
    begin = starts[idx][0]
    end = starts[idx + 1][0] if idx + 1 < len(starts) else len(lines)
    ops = []
    for l in lines[begin:end]:
        l = l.strip()
        if not l:
            continue
        first = l.split()[0]
        if first.endswith(":") or l.startswith(".") or \
                l.startswith("thumb_func") or l.startswith("arm_func"):
            continue
        ops.append(normalize(first))
    return ops


def candidate_ops(obj_path: str) -> list[str]:
    out = subprocess.run(
        ["arm-none-eabi-objdump", "-dr", obj_path],
        check=True, capture_output=True, text=True,
    ).stdout
    ops = []
    for l in out.splitlines():
        m = re.match(r"^\s*[0-9a-f]+:\s+[0-9a-f ]+\t(\S+)", l)
        if not m or "R_ARM" in l:
            continue
        mnem = m.group(1)
        if mnem in (".short", ".word"):
            continue
        ops.append(normalize(mnem))
    return ops


def main() -> None:
    if len(sys.argv) != 4:
        sys.exit(f"usage: {sys.argv[0]} <ver> <function-name> <object-file>")
    ver, name, obj_path = sys.argv[1:]

    real = real_ops(ver, name)
    cand = candidate_ops(obj_path)

    sm = difflib.SequenceMatcher(None, real, cand, autojunk=False)
    groups = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            continue
        groups += 1
        print(f"{tag}: real[{i1}:{i2}]={real[i1:i2]}  cand[{j1}:{j2}]={cand[j1:j2]}")

    print(f"\n{groups} real opcode-diff group(s); real={len(real)} cand={len(cand)}")
    sys.exit(1 if groups else 0)


if __name__ == "__main__":
    main()
