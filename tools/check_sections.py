#!/usr/bin/env python3
"""Check that every region landed where regions.<ver>.txt says it should.

ld rejects a region that assembled too big -- it overlaps its neighbour --
and names the section. It says nothing about one that came out too small:
the next section still starts at its fixed address, objcopy fills the
hole, and the only symptom is a whole-ROM cmp failure. Section sizes are
no help either, since ld rounds them up to the section alignment.

gen_link.py brackets each region in __rgn_<name>_beg/__rgn_<name>_end, which
measure the real content. This reads those back out of the linked ELF.

Usage: check_sections.py <ver>   (after `ld`, before the sha1 compare)
"""
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from manifest import parse_manifest, read_placements  # noqa: E402


def marker_addresses(elf: str) -> dict[str, int]:
    nm = subprocess.run(["arm-none-eabi-nm", elf],
                        capture_output=True, text=True, check=True)
    return {
        m.group(2): int(m.group(1), 16)
        for m in (
            re.match(r"([0-9a-fA-F]+)\s+\S+\s+(__rgn_\S+_(?:beg|end))$", line.strip())
            for line in nm.stdout.splitlines()
        )
        if m
    }


def unplaced_sections(ver: str, placements) -> list[str]:
    """Non-empty sections of sectioned objects that no manifest row
    places. ld would put them somewhere of its own choosing."""
    placed = {(stem, section) for stem, section, _ in placements.values()}
    bad = []
    for stem in sorted({stem for stem, _, _ in placements.values()}):
        dump = subprocess.run(["arm-none-eabi-objdump", "-h", f"build/{ver}/obj/{stem}.o"],
                              capture_output=True, text=True, check=True).stdout
        for m in re.finditer(r"^\s*\d+\s+(\S+)\s+([0-9a-f]+)\s", dump, re.M):
            name, size = m.group(1), int(m.group(2), 16)
            if size and name != ".ARM.attributes" and (stem, name) not in placed:
                bad.append(f"  {stem}: {name} ({hex(size)} bytes) has no manifest row")
    return bad


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    regions, _ = parse_manifest(f"regions.{ver}.txt", ver)
    markers = marker_addresses(f"build/{ver}/rom.elf")
    placements = read_placements(f"regions.{ver}.txt")
    # A section that runs from RAM is linked, and so measured, there.
    run_address = {name: vma for name, (_, _, vma) in placements.items()
                   if vma is not None}

    bad = []
    for start, end, srcfile, name in regions:
        beg, fin = markers.get(f"__rgn_{name}_beg"), markers.get(f"__rgn_{name}_end")
        if beg is None or fin is None:
            sys.exit(f"__rgn_{name} markers missing -- rerun gen_link.py")
        if fin - beg != end - start:
            bad.append(f"  {name} ({srcfile}): assembled to {hex(fin - beg)} bytes, "
                       f"but regions.{ver}.txt claims {hex(start)}-{hex(end)} = "
                       f"{hex(end - start)}")
        elif beg != run_address.get(name, start):
            bad.append(f"  {name} ({srcfile}): landed at {hex(beg)}, not "
                       f"{hex(run_address.get(name, start))}")

    bad += unplaced_sections(ver, placements)
    if bad:
        print(f"{ver}: regions do not match the manifest", file=sys.stderr)
        print("\n".join(bad), file=sys.stderr)
        sys.exit(1)
    print(f"{ver}: all {len(regions)} regions are the size and address the "
          f"manifest claims")


if __name__ == "__main__":
    main()
