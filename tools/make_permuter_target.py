#!/usr/bin/env python3
"""Scaffold a decomp-permuter project directory for one function.

decomp-permuter scores a candidate by diffing it against a *relocatable*
target.o (see .claude/skills/match-function/SKILL.md's step 4) -- comparing
against bytes cut straight from the linked ROM is close to useless, since the
score plateaus on relocation-vs-resolved-address noise regardless of
candidate quality. Building that target.o by hand (wrapping the real
disassembly in thumb_func_start/_end, turning every RAM-global literal-pool
load into an .extern reference so it shows up as a relocation on both sides)
is the tedious, mechanical, easy-to-get-subtly-wrong part of setting up a
permuter run -- this automates it.

Usage: make_permuter_target.py <ver> <function-name> <out-dir>

<function-name> must have a c-file row in regions.<ver>.txt (so its current
best-candidate source can be preprocessed into base.c) and a matching
thumb_func_start/arm_func_start label in build/<ver>/full_disasm.s (run
`just disasm-compare` first if that's stale). Writes target.o, base.c,
compile.sh, and settings.toml into <out-dir>.
"""
import os
import re
import shutil
import subprocess
import sys

FUNC_START_RE = re.compile(r"^\s*(thumb|arm)_func_start\s+(\S+)")
LITERAL_RE = re.compile(r"^(\s*)\.4byte\s+(0[xX][0-9a-fA-F]+)\s*$")

COMPILE_SH = """\
#!/bin/bash
# Compile a candidate base.c-derived source with the real project's agbcc
# invocation (see tools/c/compile_c.py's game-code profile) and the same
# .rodata-into-.text folding gen_link.py relies on, since permuter mutates
# base.c directly and won't go through that pipeline itself.
set -e

CC1=$(command -v agbcc) || {{ echo "agbcc not found -- run inside \\`nix develop\\`" >&2; exit 1; }}

INPUT="$1"; shift
[ "$1" = "-o" ] && shift
OUTPUT="$1"

TMPASM=$(mktemp --suffix=.s)
trap 'rm -f "$TMPASM" "$TMPASM.fixed"' EXIT

"$CC1" -O2 -mthumb-interwork -Wimplicit -Wparentheses -Werror -fhex-asm \\
    -o "$TMPASM" "$INPUT"

{{
    echo ".syntax divided"
    sed -E 's/^\\s*\\.section\\s+\\.rodata\\b.*$/.text/' "$TMPASM"
    echo -e "\\t.align\\t2, 0"
    echo ".syntax unified"
}} > "$TMPASM.fixed"

arm-none-eabi-as -mcpu={cpu} -o "$OUTPUT" "$TMPASM.fixed"
"""


def find_agbcc_prefix() -> str:
    exe = shutil.which("agbcc")
    if exe is None:
        sys.exit("agbcc not found -- are you in `nix develop`?")
    return os.path.dirname(os.path.dirname(os.path.realpath(exe)))


def ram_symbols(ver: str) -> dict[int, str]:
    out = {}
    path = f"ram_symbols.{ver}.inc"
    if not os.path.exists(path):
        return out
    for line in open(path):
        m = re.match(r"^\.set\s+(\S+?),\s*(0[xX][0-9a-fA-F]+)", line)
        if m:
            out[int(m.group(2), 16)] = m.group(1)
    return out


def build_target_asm(ver: str, name: str) -> tuple[str, str]:
    """Returns (asm_text, 'arm'|'thumb')."""
    path = f"build/{ver}/full_disasm.s"
    if not os.path.exists(path):
        sys.exit(f"{path} missing -- run `just disasm-compare {ver}` first")
    lines = open(path).readlines()
    starts = [(i, mode, fname) for i, l in enumerate(lines)
              if (m := FUNC_START_RE.match(l))
              for mode, fname in [(m.group(1), m.group(2))]]
    idx = next((i for i, (_, _, n) in enumerate(starts) if n == name), None)
    if idx is None:
        sys.exit(f"{name!r} not found as a func_start label in {path}")
    begin, mode, _ = starts[idx]
    end = starts[idx + 1][0] if idx + 1 < len(starts) else len(lines)
    body = lines[begin + 1:end]  # skip the func_start directive itself

    symbols = ram_symbols(ver)
    externs, out = set(), []
    for line in body:
        m = LITERAL_RE.match(line)
        if m and int(m.group(2), 16) in symbols:
            sym = symbols[int(m.group(2), 16)]
            externs.add(sym)
            out.append(f"{m.group(1)}.4byte {sym}\n")
        else:
            out.append(line)

    macro = "arm" if mode == "arm" else "thumb"
    header = "".join(f".extern {s}\n" for s in sorted(externs))
    header += (
        ".syntax unified\n"
        f".align 2, 0\n.global {name}\n.{macro}\n"
        + (".thumb_func\n" if macro == "thumb" else "")
        + f".type {name}, %function\n{name}:\n"
    )
    footer = f".size {name}, .-{name}\n"
    return header + "".join(out) + footer, macro


def find_c_source(ver: str, name: str) -> str:
    """The original .c path for a c-file row -- manifest.py discards this
    after resolving it to the generated build/<ver>/c/<name>.s path, since
    gen_link.py only needs the latter, so read the raw manifest line."""
    path = f"regions.{ver}.txt"
    for line in open(path):
        parts = line.split()
        if len(parts) == 5 and parts[0] == "c-file" and parts[4] == name:
            return parts[3]
    sys.exit(f"no c-file region named {name!r} in {path}")


def build_base_c(ver: str, name: str, agbcc_prefix: str) -> str:
    src = find_c_source(ver, name)
    inc = os.path.join(agbcc_prefix, "include")
    pre = subprocess.run(
        ["cpp", "-I", "include", "-I", inc, "-nostdinc", "-undef",
         "-std=gnu89", src],
        capture_output=True, text=True,
    )
    if pre.returncode:
        sys.exit(f"cpp failed on {src}:\n{pre.stderr}")
    return pre.stdout


def main() -> None:
    if len(sys.argv) != 4:
        sys.exit(f"usage: {sys.argv[0]} <ver> <function-name> <out-dir>")
    ver, name, out_dir = sys.argv[1:]

    os.makedirs(out_dir, exist_ok=True)
    agbcc_prefix = find_agbcc_prefix()

    target_asm, mode = build_target_asm(ver, name)
    target_s = os.path.join(out_dir, "target.s")
    open(target_s, "w").write(target_asm)
    cpu = "arm7tdmi"
    subprocess.run(
        ["arm-none-eabi-as", f"-mcpu={cpu}", "-o",
         os.path.join(out_dir, "target.o"), target_s],
        check=True,
    )

    open(os.path.join(out_dir, "base.c"), "w").write(
        build_base_c(ver, name, agbcc_prefix))

    compile_sh = os.path.join(out_dir, "compile.sh")
    open(compile_sh, "w").write(COMPILE_SH.format(cpu=cpu))
    os.chmod(compile_sh, 0o755)

    open(os.path.join(out_dir, "settings.toml"), "w").write(
        f'func_name = "{name}"\ncompiler_type = "gcc"\n')

    print(f"{out_dir}: target.o ({mode}), base.c, compile.sh, "
          f"settings.toml written for {name}")
    print("Sanity check target.o against the real opcode sequence with:\n"
          f"  python3 tools/opcode_diff.py {ver} {name} {out_dir}/target.o")


if __name__ == "__main__":
    main()
