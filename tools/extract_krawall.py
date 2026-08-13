#!/usr/bin/env python3
"""Locate and precisely bound all Krawall audio data in a ROM, and write
each region out as a raw binary asm/krawall/<kind>/<name>.bin file plus
the corresponding regions.<ver>.txt row (gen_rom_s.py .incbin's these
directly -- see its handling of a .bin asm-file extension). The .bin
files are the game's actual copyrighted audio content and must never be
committed (gitignored, like baserom.*.gba); regenerate them locally by
running this script before building -- see the `extract-krawall` recipe.

Uses the `unkrawerter` binary purely for discovery (its heuristic search
for sample/module/instrument pointer lists -- see flake.nix), then computes
exact byte spans itself using Krawall's struct layouts, ported from
UnkrawerterGBA's readSampleFile/readModuleFile/readPatternFile:
  https://github.com/MCJack123/UnkrawerterGBA (unkrawerter.cpp)

See docs/formats/krawall.md for what's confirmed and what's still open.

Usage: extract_krawall.py <ver>   (writes asm/krawall/, prints manifest
                                    rows for regions.<ver>.txt to stdout)
"""
import re
import struct
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path

ROM_BASE = 0x08000000

# krawerter's Sample.cpp: fixed-size mixer overrun buffer appended after
# every sample's real PCM data ("17*4 cause the max inc in the mixer can be
# (rounded up) 17 and we go 4 samples over the end in the worst case, +1
# for interpolation"). See docs/formats/krawall.md's Trailing padding
# absorption -- verified byte-for-byte against every sample in both ROMs.
SAMPLES_ADD = 17 * 4 + 1


def align4(addr: int) -> int:
    return (addr + 3) & ~3

KIND_DIRS = {
    "sample_list": "",
    "sample": "samples",
    "module_header": "modules",
    "pattern": "patterns",
}


@dataclass
class Region:
    start: int
    end: int
    kind: str  # "sample_list", "sample", "module_header", "pattern"
    name: str
    ver: str

    @property
    def size(self) -> int:
        return self.end - self.start

    @property
    def path(self) -> str:
        # per-version subdir -- US and JP regions use the same discovery-
        # order names (KrawallPattern0 etc.) but have different content
        sub = KIND_DIRS[self.kind]
        return f"asm/krawall/{self.ver}/{sub}/{self.name}.bin" if sub \
            else f"asm/krawall/{self.ver}/{self.name}.bin"


def run_unkrawerter(rom_path: str) -> str:
    with tempfile.TemporaryDirectory() as tmp:
        result = subprocess.run(
            ["unkrawerter", "-k", "-v", "-r", "-o", tmp, rom_path],
            capture_output=True, text=True,
        )
        return result.stdout + result.stderr


def parse_discovery(log: str) -> tuple[int, int, list[int]]:
    """Returns (sample_list_addr, sample_count, module_addrs), all as file offsets."""
    sample_addr = None
    sample_count = None
    modules = []
    for line in log.splitlines():
        m = re.match(r"Found (\d+) matches at ([0-9A-Fa-f]+) with type sample", line)
        if m:
            sample_count = int(m.group(1))
            sample_addr = int(m.group(2), 16)
        m = re.match(r"> Found module at address ([0-9A-Fa-f]+)", line)
        if m:
            modules.append(int(m.group(1), 16))
    if sample_addr is None or sample_count is None:
        sys.exit("could not find sample list in unkrawerter output")
    return sample_addr, sample_count, modules


def u8(data: bytes, off: int) -> int:
    return data[off]


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]


def is_rom_ptr(v: int) -> bool:
    return bool(v & 0x08000000) and not (v & 0xF6000000)


def sample_span(data: bytes, addr: int) -> int:
    """Port of readSampleFile: the 'size' field at +4 actually stores the
    next sample's ROM address; span = next_addr - this_addr."""
    size_field = u32(data, addr + 4)
    next_addr = size_field & 0x1FFFFFF
    return next_addr - addr


def pattern_span(data: bytes, addr: int) -> int:
    """Port of readPatternFile: walk the compressed row stream to find its
    true length. -k (old/2003 format) uses a 1-byte row count."""
    pos = addr + 32
    rows = u8(data, pos)
    pos += 1
    for _ in range(rows):
        while True:
            follow = u8(data, pos)
            pos += 1
            if not follow:
                break
            if follow & 0x20:
                pos += 2  # note, instrument (old format: never a 3rd byte)
            if follow & 0x40:
                pos += 1  # volume
            if follow & 0x80:
                pos += 2  # effect, effectop
    return pos - addr


def module_header_span(data: bytes, addr: int) -> tuple[int, list[int]]:
    """Port of readModuleFile's header-sizing logic. Returns (span,
    pattern_pointers) -- the fixed 364-byte header plus one 4-byte pointer
    per pattern referenced in the order list."""
    num_orders = u8(data, addr + 1)
    order = data[addr + 3: addr + 3 + 256]
    max_pattern = 0
    for i in range(num_orders):
        if order[i] != 254:
            max_pattern = max(max_pattern, order[i])
    pattern_ptrs = []
    for i in range(max_pattern + 1):
        p = u32(data, addr + 364 + i * 4)
        if not is_rom_ptr(p):
            break
        pattern_ptrs.append(p & 0x1FFFFFF)
    span = 364 + 4 * len(pattern_ptrs)
    return span, pattern_ptrs


def find_regions(ver: str) -> tuple[bytes, list[Region]]:
    rom_path = f"baserom.{ver}.gba"
    with open(rom_path, "rb") as f:
        data = f.read()

    log = run_unkrawerter(rom_path)
    sample_addr, sample_count, module_addrs = parse_discovery(log)

    regions: list[Region] = []
    regions.append(Region(sample_addr, sample_addr + sample_count * 4,
                           "sample_list", f"KrawallSampleList_{sample_count}", ver))

    for i in range(sample_count):
        ptr = u32(data, sample_addr + i * 4)
        if not is_rom_ptr(ptr):
            continue
        s_addr = ptr & 0x1FFFFFF
        span = sample_span(data, s_addr)
        end = align4(s_addr + span + SAMPLES_ADD)
        regions.append(Region(s_addr, end, "sample", f"KrawallSample{i}", ver))

    seen_patterns: dict[int, int] = {}  # addr -> span; keyed by address as a
    # safety net in case two modules ever point at the same pattern -- in
    # practice this never happens in this game (378 refs, 378 unique addrs,
    # verified), each pattern belongs to exactly one module
    for m_i, m_addr in enumerate(module_addrs):
        header_span, pattern_ptrs = module_header_span(data, m_addr)
        regions.append(Region(m_addr, m_addr + header_span, "module_header",
                               f"KrawallModule{m_i}", ver))
        for p_addr in pattern_ptrs:
            if p_addr not in seen_patterns:
                seen_patterns[p_addr] = pattern_span(data, p_addr)

    for i, (p_addr, span) in enumerate(sorted(seen_patterns.items())):
        # krawerter emits ".align" (4-byte on this target) before every
        # Pattern label, zero-padded -- see docs/formats/krawall.md's
        # Trailing padding absorption.
        end = align4(p_addr + span)
        regions.append(Region(p_addr, end, "pattern", f"KrawallPattern{i}", ver))

    regions.sort(key=lambda r: r.start)

    overlaps = 0
    for i in range(1, len(regions)):
        if regions[i].start < regions[i - 1].end:
            overlaps += 1
            print(f"WARNING: overlap: {regions[i-1]} and {regions[i]}", file=sys.stderr)
    if overlaps:
        sys.exit(f"{overlaps} overlaps found -- see warnings above, refusing to generate")

    # Every sample/pattern's computed end must land exactly on the next
    # region's start -- there's no format reason for a real gap here (see
    # docs/formats/krawall.md's Trailing padding absorption). If it doesn't,
    # something about the ROM's layout doesn't match our understanding of
    # the format and this needs investigating, not silently leaving a
    # fallback .incbin gap in its place.
    unexplained = 0
    for i in range(len(regions) - 1):
        r, nxt = regions[i], regions[i + 1]
        if r.kind in ("sample", "pattern") and r.end != nxt.start:
            unexplained += 1
            print(f"WARNING: unexplained {nxt.start - r.end}-byte gap after "
                  f"{r.name} (kind={r.kind}), before {nxt.name}", file=sys.stderr)
    if unexplained:
        sys.exit(f"{unexplained} unexplained sample/pattern gaps found -- "
                  "see warnings above, refusing to generate")

    return data, regions


def write_region_file(data: bytes, region: Region) -> None:
    """Raw binary, not a hex-text .s dump -- this is the game's actual
    copyrighted audio content, so it must never be committed (see
    asm/krawall/ in .gitignore). gen_rom_s.py .incbin's it directly."""
    path = Path(region.path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data[region.start:region.end])


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    data, regions = find_regions(ver)

    total = sum(r.size for r in regions)
    kinds = {k: sum(1 for r in regions if r.kind == k) for k in KIND_DIRS}
    print(f"# {ver}: {len(regions)} regions, {total} bytes total ({kinds})",
          file=sys.stderr)

    for r in regions:
        write_region_file(data, r)
        print(f"0x{ROM_BASE + r.start:08X} 0x{ROM_BASE + r.end:08X} {r.path} {r.name}")


if __name__ == "__main__":
    main()
