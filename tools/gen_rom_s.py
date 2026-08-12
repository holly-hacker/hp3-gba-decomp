#!/usr/bin/env python3
"""Generate build/<ver>/rom.s by stitching together regions.<ver>.txt.

Everything not covered by a region in the manifest is pulled in verbatim
via .incbin from the baserom. Never commit the output of this script --
it's fully reproducible from the manifest + the user's local ROM.

Usage: gen_rom_s.py <ver>   (writes to stdout)
"""
import os
import sys

# (start, end, asmfile, name)
Region = tuple[int, int, str, str]
# address -> name, for symbols inside not-yet-extracted (still-incbin)
# territory that extracted code needs to reference
Labels = dict[int, str]


def parse_manifest(path: str) -> tuple[list[Region], Labels]:
    """Returns (regions, labels): regions sorted and non-overlapping."""
    regions: list[Region] = []
    labels: Labels = {}
    with open(path) as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            if parts[0] == "label":
                if len(parts) != 3:
                    sys.exit(f"{path}:{lineno}: expected 'label <addr> <name>'")
                addr = int(parts[1], 16)
                labels[addr] = parts[2]
                continue
            if len(parts) != 4:
                sys.exit(f"{path}:{lineno}: expected 4 fields, got {len(parts)}")
            start_s, end_s, asmfile, name = parts
            start, end = int(start_s, 16), int(end_s, 16)
            if end <= start:
                sys.exit(f"{path}:{lineno}: end must be after start")
            regions.append((start, end, asmfile, name))
    regions.sort(key=lambda r: r[0])
    for i in range(1, len(regions)):
        if regions[i][0] < regions[i - 1][1]:
            sys.exit(f"overlapping regions: {regions[i-1]} and {regions[i]}")
    return regions, labels


def emit_gap(
    out: list[str],
    addr: int,
    end: int,
    labels: Labels,
    rom_path: str,
    base_addr: int,
) -> None:
    """Emit .incbin for [addr, end), splitting at any declared label
    (including addr itself) so extracted code can reference addresses
    inside still-raw territory."""
    cur = addr
    split_points = sorted(a for a in labels if cur <= a < end)
    for point in split_points:
        if point > cur:
            out.append(f'.incbin "{rom_path}", {hex(cur - base_addr)}, {hex(point - cur)}')
        out.append(f'{labels[point]}:')
        cur = point
    if cur < end:
        out.append(f'.incbin "{rom_path}", {hex(cur - base_addr)}, {hex(end - cur)}')


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    rom_path = f"baserom.{ver}.gba"
    rom_size = os.path.getsize(rom_path)
    base_addr = 0x08000000

    regions, labels = parse_manifest(f"regions.{ver}.txt")

    out: list[str] = []
    out.append(".syntax unified")
    out.append('.include "macros.inc"')
    out.append("")
    out.append(".text")
    out.append("")

    addr = base_addr
    i = 0
    while i < len(regions):
        start, end, asmfile, name = regions[i]

        if start > addr:
            emit_gap(out, addr, start, labels, rom_path, base_addr)
        elif start < addr:
            sys.exit(f"region {name} starts before current position, should be unreachable")

        out.append(f'.include "{asmfile}"  @ {hex(start)}-{hex(end)} {name}')
        addr = end
        i += 1

    if addr < base_addr + rom_size:
        emit_gap(out, addr, base_addr + rom_size, labels, rom_path, base_addr)

    print("\n".join(out))


if __name__ == "__main__":
    main()
