#!/usr/bin/env python3
"""Check that every region landed where regions.<ver>.txt says it should.

ld rejects a region that assembled too big -- it overlaps its neighbour --
and names the section. It says nothing about one that came out too small:
the next section still starts at its fixed address, objcopy fills the
hole, and the only symptom is a whole-ROM cmp failure. Section sizes are
no help either, since ld rounds them up to the section alignment.

gen_link.py brackets each region in __rgn<N>_beg/__rgn<N>_end, which
measure the real content. This reads those back out of the linked ELF.

Usage: check_sections.py <ver>   (after `ld`, before the sha1 compare)
"""
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from manifest import parse_manifest  # noqa: E402


# Code placed this far up the ROM is out of `bl` range of the game code, so
# the linker appends veneers to it and the region may be larger than its code.
FAR_CODE_START = 0x08400000


def marker_addresses(elf: str) -> dict[str, int]:
    nm = subprocess.run(["arm-none-eabi-nm", elf],
                        capture_output=True, text=True, check=True)
    return {
        m.group(2): int(m.group(1), 16)
        for m in (
            re.match(r"([0-9a-fA-F]+)\s+\S+\s+(__rgn\d+_(?:beg|end))$", line.strip())
            for line in nm.stdout.splitlines()
        )
        if m
    }


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    regions, _ = parse_manifest(f"regions.{ver}.txt", ver)
    markers = marker_addresses(f"build/{ver}/rom.elf")

    bad = []
    for i, (start, end, srcfile, name) in enumerate(regions):
        beg, fin = markers.get(f"__rgn{i:03d}_beg"), markers.get(f"__rgn{i:03d}_end")
        if beg is None or fin is None:
            sys.exit(f"__rgn{i:03d} markers missing -- rerun gen_link.py")
        # A far `bl` needs a linker veneer appended to the region.
        veneer_room = start >= FAR_CODE_START and fin - beg < end - start
        if fin - beg != end - start and not veneer_room:
            bad.append(f"  {name} ({srcfile}): assembled to {hex(fin - beg)} bytes, "
                       f"but regions.{ver}.txt claims {hex(start)}-{hex(end)} = "
                       f"{hex(end - start)}")
        elif beg != start:
            bad.append(f"  {name} ({srcfile}): landed at {hex(beg)}, not {hex(start)}")

    if bad:
        print(f"{ver}: regions do not match the manifest", file=sys.stderr)
        print("\n".join(bad), file=sys.stderr)
        sys.exit(1)
    print(f"{ver}: all {len(regions)} regions are the size and address the "
          f"manifest claims")


if __name__ == "__main__":
    main()
