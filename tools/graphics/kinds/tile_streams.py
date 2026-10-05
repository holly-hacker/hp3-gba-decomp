"""tile-streams runs: tile streams drawn as PNG tile sheets (see
tools/graphic_blob/tile_streams.py and docs/formats/graphic_blob.md).

Settings: the ordered `streams` list. Each stream is labeled g<Name>.
"""
import re
from pathlib import Path

import blobs
import tile_streams as codec

ITEMS = "streams"
SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
ENTRY_KEYS = {"name", "width", "height", "tiles"}


def check(run: dict) -> None:
    if set(run) != {ITEMS}:
        raise ValueError(f"expected {ITEMS}")
    names = set()
    for entry in run["streams"]:
        if set(entry) != ENTRY_KEYS:
            raise ValueError(f"{entry.get('name')}: expected keys {', '.join(sorted(ENTRY_KEYS))}")
        name = entry["name"]
        if not isinstance(name, str) or not SYMBOL.fullmatch(name) or name in names:
            raise ValueError(f"invalid or duplicate stream name {name!r}")
        names.add(name)
        for key in ("width", "height", "tiles"):
            if not (isinstance(entry[key], int) and 0 < entry[key] < 1 << 16):
                raise ValueError(f"{name}: {key} must be a positive 16-bit integer")


def item_files(run: dict, entry: dict) -> list[str]:
    return [f"{entry['name']}.png"]


def files(run: dict) -> list[str]:
    return [f for entry in run[ITEMS] for f in item_files(run, entry)]


def stream_from_file(source: Path, entry: dict):
    size, pixels, _ = blobs.read_png(source / f"{entry['name']}.png")
    rows = (entry["tiles"] + codec.TILES_PER_ROW - 1) // codec.TILES_PER_ROW
    if size != (codec.TILES_PER_ROW * 8, rows * 8):
        raise ValueError(f"{entry['name']}.png: expected {codec.TILES_PER_ROW * 8}x{rows * 8}, got {size[0]}x{size[1]}")
    if max(pixels) > 15:
        raise ValueError(f"{entry['name']}.png: color number above 15")
    return codec.tiles_from_sheet(pixels, entry["tiles"])


def build(source: Path, name: str, settings: dict, entry: dict) -> list[tuple[str, bytes]]:
    return [(f"g{entry['name']}", codec.build(entry["width"], entry["height"], stream_from_file(source, entry)))]


# Names by position, per bank: (first position, prefix) of each group.
GROUPS = {"RainTiles": ((0, "RainStreak"), (32, "RainSplash"))}


def name(bank: str, i: int) -> str:
    groups = GROUPS.get(bank, ((0, bank),))
    start, prefix = [g for g in groups if g[0] <= i][-1]
    return f"{prefix}{i - start + 1:02d}"


def extract(rom: bytes, ver: str, start: int, end: int, bank: str, source: Path) -> dict:
    addr, entries = start, []
    while addr < end:
        (width, height, tiles), next_addr, raw = codec.parse(rom, addr)
        entry = {"name": name(bank, len(entries)), "width": width, "height": height, "tiles": len(tiles)}
        size, pixels = codec.sheet(tiles)
        blobs.write_png(source / f"{entry['name']}.png", size, pixels, codec.GRAY,
                        blobs.transparent_indices(False)[:1])
        if codec.build(width, height, stream_from_file(source, entry)) != raw:
            raise ValueError(f"{entry['name']}: rebuilding from the PNG gives different bytes")
        entries.append(entry)
        addr = next_addr
    if addr != end:
        raise ValueError(f"walk ends at {addr:#010x}, not the row end {end:#010x}")
    return {ITEMS: entries}
