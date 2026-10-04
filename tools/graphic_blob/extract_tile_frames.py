#!/usr/bin/env python3
"""Extract every tile-frames manifest row from the baserom as PNG tile sheets.

Each row's range is walked frame by frame (a frame's length follows from
the frame itself) and must end exactly at the row's end address. Every
frame must rebuild from its PNG to the ROM's bytes. See tile_frames.py and
docs/formats/special_scene_frames.md.

data/tile_frames/ is gitignored, same footing as the baserom; extraction
overwrites local PNG edits.

Usage: extract_tile_frames.py <ver> [bank ...]
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import blobs
import tile_frames
from pack_tile_frames import frame_from_file, tile_frame_rows

def name(bank: str, i: int) -> str:
    return f"{bank.removesuffix('s')}{i + 1:03d}"


def main() -> None:
    args = sys.argv[1:]
    if not args or args[0].startswith("-"):
        sys.exit(f"usage: {sys.argv[0]} <ver> [bank ...]")
    ver, wanted = args[0], args[1:]
    try:
        rom = Path(f"baserom.{ver}.gba").read_bytes()
        rows = [r for r in tile_frame_rows(ver) if not wanted or r[3] in wanted]
        for start, end, source, bank in rows:
            addr, found = start, []
            while addr < end:
                parsed, next_addr, raw = tile_frames.parse(rom, addr)
                found.append((parsed, raw))
                addr = next_addr
            if addr != end:
                raise ValueError(f"walk ends at {addr:#010x}, not the row end {end:#010x}")
            source.mkdir(parents=True, exist_ok=True)
            for old in source.glob("*.png"):
                old.unlink()
            entries = []
            for i, ((kind, tiles), raw) in enumerate(found):
                entry = {"name": name(bank, i), "kind": kind, "tiles": len(tiles)}
                size, pixels = tile_frames.sheet(tiles)
                blobs.write_png(source / f"{entry['name']}.png", size, pixels,
                                tile_frames.GRAY8 if kind & tile_frames.KIND_8BPP else tile_frames.GRAY,
                                blobs.transparent_indices(False)[:1])
                if tile_frames.build(kind, frame_from_file(source, entry)) != raw:
                    raise ValueError(f"{entry['name']}: rebuilding from the PNG gives different bytes")
                entries.append(entry)
            (source / "bank.json").write_text(
                '{\n "format": 1,\n "frames": [\n' + ",\n".join("  " + json.dumps(e) for e in entries) + "\n ]\n}\n")
            print(f"{ver}: extracted {bank}: {len(entries)} frames in {source}")
        if not rows:
            print(f"{ver}: no tile-frames regions")
    except (OSError, ValueError) as exc:
        sys.exit(str(exc))


if __name__ == "__main__":
    main()
