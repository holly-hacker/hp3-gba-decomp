#!/usr/bin/env python3
"""Compare an existing linked ROM region against the donor bytes.

Does not rebuild: use just diff-region NAME VERSION for a fresh build.
Instruction mode comes from the row's directive (ARM for c-file-arm and
c-file-gcc3-arm objects), or for assembly from the source's first mode
directive; --arm/--thumb override it. Byte equality includes literal pools and padding.
"""
import argparse
import os
import re
import sys

import capstone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from manifest import (  # noqa: E402
    ASM_CPP_DIRECTIVE,
    ASM_FILE_DIRECTIVE,
    C_SECTION_DIRECTIVE,
    LABEL_DIRECTIVES,
    SECTIONED_DIRECTIVES,
    parse_manifest,
    read_rows,
)

CONTEXT = 4


ARM_C_DIRECTIVES = {"c-file-arm", "c-file-gcc3-arm"}
ASM_MODE = re.compile(r"^\s*(arm_func_start|thumb_func_start|\.arm|\.thumb|\.code\s+(?:16|32))\b",
                      re.I | re.M)


def asm_mode(path: str) -> str:
    with open(path) as f:
        found = ASM_MODE.search(f.read())
    if found is None:
        return "thumb"
    directive = found.group(1).lower()
    return "arm" if directive.startswith(("arm", ".arm")) or directive.endswith("32") else "thumb"


def mode_for(ver: str, address: int) -> str:
    """The mode of the row starting at address: ARM C objects by directive,
    assembly by its source's first mode directive, otherwise Thumb."""
    rows = [parts for _, parts in read_rows(f"regions.{ver}.txt")
            if parts[0] not in LABEL_DIRECTIVES]
    objects = {parts[4]: parts for parts in rows if parts[0] in SECTIONED_DIRECTIVES}
    for parts in rows:
        if int(parts[1], 16) != address:
            continue
        if parts[0] == C_SECTION_DIRECTIVE:
            parts = objects[parts[3]]
        if parts[0] in ARM_C_DIRECTIVES:
            return "arm"
        if parts[0] in (ASM_FILE_DIRECTIVE, ASM_CPP_DIRECTIVE):
            return asm_mode(parts[3])
        return "thumb"
    return "thumb"


def disasm(data: bytes, address: int, mode: str) -> list[str]:
    md = capstone.Cs(
        capstone.CS_ARCH_ARM,
        capstone.CS_MODE_ARM if mode == "arm" else capstone.CS_MODE_THUMB,
    )
    step = 4 if mode == "arm" else 2
    out, off = [], 0
    while off < len(data):
        decoded = list(md.disasm(data[off:], address + off, count=1))
        if decoded:
            i = decoded[0]
            out.append((i.address, i.bytes.hex(), f"{i.mnemonic} {i.op_str}".strip()))
            off += i.size
        else:
            out.append((address + off, data[off:off + step].hex(), ".word"))
            off += step
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('version', choices=['us', 'jp'])
    parser.add_argument('name')
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('--arm', action='store_true')
    mode.add_argument('--thumb', action='store_true')
    args = parser.parse_args()
    ver, name = args.version, args.name

    regions, _ = parse_manifest(f"regions.{ver}.txt", ver)
    match = [r for r in regions if r[3] == name]
    if not match:
        sys.exit(f"no region named {name} in regions.{ver}.txt")
    start, end, srcfile, _ = match[0]

    base = f"baserom.{ver}.gba"
    built = f"build/{ver}/rom.gba"
    if not os.path.exists(built):
        sys.exit(f"{built} missing -- run `just build {ver}` first")
    off, size = start - 0x08000000, end - start
    want = open(base, "rb").read()[off:off + size]
    got = open(built, "rb").read()[off:off + size]

    print(f"{name}  {srcfile}  {hex(start)}-{hex(end)} ({size} bytes)")
    if want == got:
        print("MATCH")
        return

    mode = ("arm" if args.arm else
            "thumb" if args.thumb else mode_for(ver, start))
    a, b = disasm(want, start, mode), disasm(got, start, mode)
    print(f"{mode} mode; ROM on the left, build on the right\n")
    differing = [i for i in range(max(len(a), len(b)))
                 if i >= len(a) or i >= len(b) or a[i][1] != b[i][1]]
    shown = {j for i in differing for j in range(i - CONTEXT, i + CONTEXT + 1)}
    last = None
    for i in sorted(j for j in shown if 0 <= j < max(len(a), len(b))):
        if last is not None and i != last + 1:
            print("           ...")
        left = a[i] if i < len(a) else (0, "", "")
        right = b[i] if i < len(b) else (0, "", "")
        flag = " " if left[1] == right[1] else "|"
        print(f"  {left[0]:08X}  {left[1]:<8} {left[2]:<26} {flag} "
              f"{right[1]:<8} {right[2]}")
        last = i
    print(f"\n{len(differing)} differing instruction(s)")
    sys.exit(1)


if __name__ == "__main__":
    main()
