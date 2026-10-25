#!/usr/bin/env python3
"""Compare build/<ver>/rom.gba with the donor ROM byte for byte.

On a mismatch, names the region holding the first differing byte that the
linker did not fill in. Every region after a resized one moves, and so do
pointers to them anywhere in the ROM; skipping those, the first difference
is where to look (just diff-region <name> <ver>).

Usage: compare.py <ver>   (after `just build <ver>`)
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from rom_elf import region_at, region_ranges, relocated_bytes  # noqa: E402

ROM_BASE = 0x08000000


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]
    want = open(f"baserom.{ver}.gba", "rb").read()
    got = open(f"build/{ver}/rom.gba", "rb").read()
    if want == got:
        print("MATCH")
        return
    linked = relocated_bytes(f"build/{ver}/rom.elf")
    differ = [i for i, (a, b) in enumerate(zip(want, got)) if a != b]
    first = next((i for i in differ if ROM_BASE + i not in linked),
                 differ[0] if differ else min(len(want), len(got)))
    addr = ROM_BASE + first
    if first == min(len(want), len(got)):
        print(f"{ver}: the build is {len(got):#x} bytes, the donor ROM {len(want):#x}; "
              f"they agree up to there", file=sys.stderr)
    region = region_at(region_ranges(f"build/{ver}/rom.elf"), addr)
    where = f"in region {region}" if region else "outside every region"
    print(f"{ver}: first difference at {addr:#010x}, {where}", file=sys.stderr)
    sys.exit(1)


if __name__ == "__main__":
    main()
