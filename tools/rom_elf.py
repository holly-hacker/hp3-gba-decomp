#!/usr/bin/env python3
"""Where each region of a linked build is stored in ROM.

gen_link.py brackets every region in __rgn_<name>_beg/__rgn_<name>_end. A
region that runs from RAM is linked, and so marked, at its RAM address;
the section holding it says where it is stored.
"""
import re
import subprocess

MARKER = re.compile(r"^([0-9a-f]+)\s+\S+\s+__rgn_(\S+)_(beg|end)$")
SECTION = re.compile(r"^\s*\d+\s+\S+\s+([0-9a-f]+)\s+([0-9a-f]+)\s+([0-9a-f]+)\s", re.M)
RELOC = re.compile(r"^([0-9a-f]{8})\s+\S+\s+(R_ARM_\w+)", re.M)


def _sections(elf: str) -> list[tuple[int, int, int]]:
    headers = subprocess.run(["arm-none-eabi-objdump", "-h", elf],
                             capture_output=True, text=True, check=True).stdout
    return [(int(vma, 16), int(lma, 16), int(size, 16))
            for size, vma, lma in SECTION.findall(headers) if int(size, 16)]


def _stored(sections: list[tuple[int, int, int]], addr: int) -> int:
    for vma, lma, size in sections:
        if vma <= addr < vma + size:
            return addr - vma + lma
    # An empty region's marker sits just past a section's last byte.
    for vma, lma, size in sections:
        if addr == vma + size:
            return addr - vma + lma
    return addr


def relocated_bytes(elf: str) -> set[int]:
    """The ROM addresses of every byte the linker filled in: pointers and
    branch offsets. Needs an ELF linked with --emit-relocs."""
    sections = _sections(elf)
    relocs = subprocess.run(["arm-none-eabi-readelf", "-rW", elf],
                            capture_output=True, text=True, check=True).stdout
    out = set()
    for addr, kind in RELOC.findall(relocs):
        if kind != "R_ARM_V4BX":
            start = _stored(sections, int(addr, 16))
            out.update(range(start, start + 4))
    return out


def region_ranges(elf: str) -> dict[str, tuple[int, int]]:
    """Region name -> (start, end) of where it is stored in ROM."""
    sections = _sections(elf)
    symbols = subprocess.run(["arm-none-eabi-nm", elf],
                             capture_output=True, text=True, check=True).stdout
    found: dict[str, dict[str, int]] = {}
    for line in symbols.splitlines():
        m = MARKER.match(line.strip())
        if m:
            found.setdefault(m.group(2), {})[m.group(3)] = int(m.group(1), 16)
    return {name: (_stored(sections, ends["beg"]),
                   _stored(sections, ends["beg"]) + ends["end"] - ends["beg"])
            for name, ends in found.items() if len(ends) == 2}


def region_at(ranges: dict[str, tuple[int, int]], addr: int) -> str | None:
    """The region whose bytes include addr."""
    for name, (start, end) in ranges.items():
        if start <= addr < end:
            return name
    return None
