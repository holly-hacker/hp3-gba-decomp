#!/usr/bin/env python3
"""Disassemble one region side by side against the donor ROM.

check_sections.py catches a region of the wrong size or at the wrong
address. A region that is the right size but the wrong bytes -- the usual
state of a function being decompiled -- shows up only as a whole-ROM cmp
failure, which says nothing about where or why. This diffs a single
region.

Instruction mode comes from functions.<ver>.cfg where the region's start
is listed, else Thumb; --arm and --thumb override.

Usage: diff_region.py <ver> <name> [--arm|--thumb]
"""
import os
import sys

import capstone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from manifest import parse_manifest  # noqa: E402

CONTEXT = 4


def mode_for(ver: str, address: int) -> str:
    try:
        with open(f"functions.{ver}.cfg") as f:
            for line in f:
                parts = line.split()
                if len(parts) >= 2 and parts[0] in ("arm_func", "thumb_func"):
                    if int(parts[1], 16) == address:
                        return "arm" if parts[0] == "arm_func" else "thumb"
    except FileNotFoundError:
        pass
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
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    flags = [a for a in sys.argv[1:] if a.startswith("--")]
    if len(args) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver> <name> [--arm|--thumb]")
    ver, name = args

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

    mode = ("arm" if "--arm" in flags else
            "thumb" if "--thumb" in flags else mode_for(ver, start))
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
