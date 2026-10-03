#!/usr/bin/env python3
"""Extract every graphic-blobs manifest row from the baserom as indexed PNGs.

Each row's range is walked blob by blob (each blob's length follows from the
blob itself) and must end exactly at the row's end address. Every blob must
rebuild from its PNGs to the ROM's bytes. See docs/formats/graphic_blob.md and
tools/graphic_blob/blobs.py.

data/graphic_blobs/ is gitignored, same footing as the baserom; extraction
overwrites local PNG edits.

Usage: extract_graphic_blobs.py <ver> [bank ...]
"""
import json
import sys
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import blobs
from pack_graphic_blobs import blob_from_files, graphic_blob_rows

ROM_BASE = blobs.ROM_BASE


# BgGraphicNNN numbers (1-based, after the battle backgrounds) at which a
# battle effect's frames start; each runs up to the next start.
EFFECT_STARTS = (8, 22, 58, 104, 156)


def names(bank: str):
    """Blob names by position. The first 28 blobs of BgGraphics are the 14
    floor and wall pairs of the battle background table, the next two its
    alternate pair, then come single graphics and five battle effects'
    frames."""
    def name(i: int) -> str:
        if bank == "BgGraphics":
            if i < 28:
                return f"Battle{'Floor' if i % 2 == 0 else 'Wall'}{i // 2 + 1:02d}"
            if i < 30:
                return f"BattleAlt{'Floor' if i % 2 == 0 else 'Wall'}"
            n = i - 29
            starts = [e for e in EFFECT_STARTS if e <= n]
            if starts:
                return f"BattleEffectBg{len(starts)}Frame{n - starts[-1] + 1:02d}"
            return f"BgGraphic{n:03d}"
        return f"{bank}{i + 1:03d}"
    return name


def walk(rom: bytes, start: int, end: int):
    addr, found = start, []
    while addr < end:
        blob, next_addr, raw = blobs.parse(rom, addr)
        found.append((blob, raw))
        addr = next_addr
    if addr != end:
        raise ValueError(f"walk ends at {addr:#010x}, not the row end {end:#010x}")
    return found


def write_blob(args):
    source, name, blob, raw = args
    colors, high = blobs.decode_palette(blob.palette)
    size = (blob.width * 8, blob.height * 8)
    transparent = blobs.transparent_indices(blob.bpp8)
    blobs.write_png(source / f"{name}.png", size, blobs.image_pixels(blob), colors, transparent)
    entry = {"name": name, "flags": [blob.flags0, blob.flags1]}
    if high:
        entry["highBits"] = high
    unused = blob.tiles[blobs.used_tiles(blob):]
    if unused:
        entry["unused"] = len(unused)
        size, pixels = blobs.unused_sheet(unused)
        blobs.write_png(source / f"{name}.unused.png", size, pixels, colors, transparent)
    rebuilt = blobs.build(blob_from_files(source, entry))
    if rebuilt != raw:
        raise ValueError(f"{name}: rebuilding from the PNGs gives different bytes")
    return entry


def main() -> None:
    args = sys.argv[1:]
    if not args or args[0].startswith("-"):
        sys.exit(f"usage: {sys.argv[0]} <ver> [bank ...]")
    ver, wanted = args[0], args[1:]
    try:
        rom = Path(f"baserom.{ver}.gba").read_bytes()
        rows = [r for r in graphic_blob_rows(ver) if not wanted or r[3] in wanted]
        for start, end, source, name in rows:
            found = walk(rom, start, end)
            source.mkdir(parents=True, exist_ok=True)
            for old in source.glob("*.png"):
                old.unlink()
            namer = names(name)
            jobs = [(source, namer(i), blob, raw) for i, (blob, raw) in enumerate(found)]
            with ProcessPoolExecutor() as pool:
                entries = list(pool.map(write_blob, jobs))
            (source / "bank.json").write_text(
                '{\n "format": 1,\n "blobs": [\n' + ",\n".join("  " + json.dumps(e) for e in entries) + "\n ]\n}\n")
            print(f"{ver}: extracted {name}: {len(entries)} blobs in {source}")
        if not rows:
            print(f"{ver}: no graphic-blobs regions")
    except (OSError, ValueError) as exc:
        sys.exit(str(exc))


if __name__ == "__main__":
    main()
