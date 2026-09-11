#!/usr/bin/env python3
"""Mnemonic-only structural diagnostic for a selected function in an object.

Ignores operands, relocations and literal data: zero groups does not prove a match.
Reference extent runs to the next function label; prefer workspace compare for
validated boundaries and exact bytes. Requires build/VERSION/full_disasm.s.
"""
import argparse
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


def candidate_ops(obj_path: str, name: str) -> list[str]:
    out = subprocess.run(
        ["arm-none-eabi-objdump", "-dr", "--disassemble=" + name, obj_path],
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
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('version', choices=['us', 'jp'])
    parser.add_argument('name')
    parser.add_argument('object')
    args = parser.parse_args()
    ver, name, obj_path = args.version, args.name, args.object

    real = real_ops(ver, name)
    cand = candidate_ops(obj_path, name)

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
