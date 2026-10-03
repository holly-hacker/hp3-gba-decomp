#!/usr/bin/env python3
"""Extract every tile-streams manifest row from the baserom as PNG tile sheets.

Each row's range is walked stream by stream (a stream's length follows from
the stream itself) and must end exactly at the row's end address. Every
stream must rebuild from its PNG to the ROM's bytes. See tile_streams.py and
docs/formats/graphic_blob.md.

data/tile_streams/ is gitignored, same footing as the baserom; extraction
overwrites local PNG edits.

Usage: extract_tile_streams.py <ver> [bank ...]
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import blobs
import tile_streams
from pack_tile_streams import stream_from_file, tile_stream_rows

# Names by position, per bank: (first position, prefix) of each group.
GROUPS = {"RainTiles": ((0, "RainStreak"), (32, "RainSplash"))}


def name(bank: str, i: int) -> str:
    groups = GROUPS.get(bank, ((0, bank),))
    start, prefix = [g for g in groups if g[0] <= i][-1]
    return f"{prefix}{i - start + 1:02d}"


def main() -> None:
    args = sys.argv[1:]
    if not args or args[0].startswith("-"):
        sys.exit(f"usage: {sys.argv[0]} <ver> [bank ...]")
    ver, wanted = args[0], args[1:]
    try:
        rom = Path(f"baserom.{ver}.gba").read_bytes()
        rows = [r for r in tile_stream_rows(ver) if not wanted or r[3] in wanted]
        for start, end, source, bank in rows:
            addr, found = start, []
            while addr < end:
                parsed, next_addr, raw = tile_streams.parse(rom, addr)
                found.append((parsed, raw))
                addr = next_addr
            if addr != end:
                raise ValueError(f"walk ends at {addr:#010x}, not the row end {end:#010x}")
            source.mkdir(parents=True, exist_ok=True)
            for old in source.glob("*.png"):
                old.unlink()
            entries = []
            for i, ((width, height, tiles), raw) in enumerate(found):
                entry = {"name": name(bank, i), "width": width, "height": height, "tiles": len(tiles)}
                size, pixels = tile_streams.sheet(tiles)
                blobs.write_png(source / f"{entry['name']}.png", size, pixels, tile_streams.GRAY,
                                blobs.transparent_indices(False)[:1])
                if tile_streams.build(width, height, stream_from_file(source, entry)) != raw:
                    raise ValueError(f"{entry['name']}: rebuilding from the PNG gives different bytes")
                entries.append(entry)
            (source / "bank.json").write_text(
                '{\n "format": 1,\n "streams": [\n' + ",\n".join("  " + json.dumps(e) for e in entries) + "\n ]\n}\n")
            print(f"{ver}: extracted {bank}: {len(entries)} streams in {source}")
        if not rows:
            print(f"{ver}: no tile-streams regions")
    except (OSError, ValueError) as exc:
        sys.exit(str(exc))


if __name__ == "__main__":
    main()
