#!/usr/bin/env python3
"""Compute the krawall-module/krawall-samples rows for regions.<ver>.txt
from the baserom, using the same address tables and span math as
tools/krawall/extract_krawall.py. See docs/formats/krawall.md.

Unlike extract_krawall.py's per-pattern/per-sample rows, this emits one
row per module (covering that module's own patterns, which are contiguous
and immediately precede its header -- confirmed in
docs/formats/krawall.md) and a single row for the whole sample block
(samples + the pointer list are one contiguous run, also confirmed
there). Also double-checks those contiguity assumptions the packer relies
on, refusing to emit if a future baserom's layout doesn't match.

Module names come from krawall_names.txt (see krawall_codec.py's
load_krawall_names) the same way tools/krawall/krawall_migrate.py resolves them --
re-run this (and splice the output into regions.<ver>.txt) any time
krawall_names.txt changes, so the row names/paths keep matching the
renamed data/audio/modules/*.json files.

Usage: gen_krawall_regions.py <ver>   (prints manifest rows to stdout)
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from extract_krawall import (
    SAMPLE_LIST, MODULE_ADDRS, sample_span, module_header_span,
    align4, SAMPLES_ADD, u32,
)
from krawall_codec import load_krawall_names, resolve_names

ROM_BASE = 0x08000000


def compute_samples_bounds(data: bytes, ver: str) -> tuple[int, int]:
    sample_list_addr, sample_count = SAMPLE_LIST[ver]
    addrs = [u32(data, sample_list_addr + i * 4) & 0x1FFFFFF for i in range(sample_count)]
    if sorted(addrs) != addrs:
        sys.exit("sample index order doesn't match address order -- would "
                 "make krawall_migrate.py's per-sample 'index' field disagree "
                 "with the ROM's own instrument-reference numbering")
    cur = addrs[0]
    for a in addrs:
        if a != cur:
            sys.exit(f"sample block not contiguous at 0x{a:X} (expected 0x{cur:X})")
        cur = align4(a + sample_span(data, a) + SAMPLES_ADD)
    if cur != sample_list_addr:
        sys.exit(f"sample block doesn't end exactly at the sample list "
                 f"(0x{cur:X} vs 0x{sample_list_addr:X})")
    return addrs[0], sample_list_addr + sample_count * 4


def compute_module_bounds(data: bytes, m_addr: int) -> tuple[int, int]:
    header_span, pattern_ptrs = module_header_span(data, m_addr)
    if not pattern_ptrs:
        return m_addr, m_addr + header_span
    start = min(pattern_ptrs)
    if max(pattern_ptrs) >= m_addr:
        sys.exit(f"module at 0x{m_addr:X}: pattern pointer >= header address, "
                  "contiguity assumption violated")
    return start, m_addr + header_span


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    with open(f"baserom.{ver}.gba", "rb") as f:
        data = f.read()

    rows: list[tuple[int, int, str]] = []

    s_start, s_end = compute_samples_bounds(data, ver)
    rows.append((s_start, s_end,
                 f"krawall-samples 0x{ROM_BASE+s_start:08X} 0x{ROM_BASE+s_end:08X} "
                 f"data/audio/samples KrawallSamples"))

    module_names, _ = load_krawall_names()
    resolved_names = resolve_names("module", len(MODULE_ADDRS[ver]), module_names)
    for m_i, m_addr in enumerate(MODULE_ADDRS[ver]):
        start, end = compute_module_bounds(data, m_addr)
        name = resolved_names[m_i]
        rows.append((start, end,
                     f"krawall-module 0x{ROM_BASE+start:08X} 0x{ROM_BASE+end:08X} "
                     f"data/audio/modules/{name}.json {name}"))

    rows.sort(key=lambda r: r[0])
    for _, _, line in rows:
        print(line)


if __name__ == "__main__":
    main()
