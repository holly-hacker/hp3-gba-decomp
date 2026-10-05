"""tile-frames runs: tile frames drawn as PNG tile sheets (see
tools/graphic_blob/tile_frames.py and docs/formats/special_scene_frames.md).

Each frame is labeled g<Name>.
"""
import re
from pathlib import Path

import blobs
import tile_frames as codec

ITEMS = "frames"
OPTIONS = {}
SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
ENTRY_KEYS = {"name", "kind", "tiles"}


def check(run: dict) -> None:
    names = set()
    for entry in run["frames"]:
        if set(entry) != ENTRY_KEYS:
            raise ValueError(f"{entry.get('name')}: expected keys {', '.join(sorted(ENTRY_KEYS))}")
        name = entry["name"]
        if not isinstance(name, str) or not SYMBOL.fullmatch(name) or name in names:
            raise ValueError(f"invalid or duplicate frame name {name!r}")
        names.add(name)
        for key in ("kind", "tiles"):
            if not (isinstance(entry[key], int) and 0 < entry[key] < 1 << 16):
                raise ValueError(f"{name}: {key} must be a positive 16-bit integer")


def item_files(entry: dict) -> list[str]:
    return [f"{entry['name']}.png"]


def files(run: dict) -> list[str]:
    return [f for entry in run[ITEMS] for f in item_files(entry)]


def frame_from_file(source: Path, entry: dict):
    size, pixels, _ = blobs.read_png(source / f"{entry['name']}.png")
    rows = (entry["tiles"] + codec.TILES_PER_ROW - 1) // codec.TILES_PER_ROW
    if size != (codec.TILES_PER_ROW * 8, rows * 8):
        raise ValueError(f"{entry['name']}.png: expected {codec.TILES_PER_ROW * 8}x{rows * 8}, got {size[0]}x{size[1]}")
    limit = 255 if entry["kind"] & codec.KIND_8BPP else 15
    if max(pixels) > limit:
        raise ValueError(f"{entry['name']}.png: color number above {limit}")
    return codec.tiles_from_sheet(pixels, entry["tiles"])


def build(source: Path, settings: dict, entry: dict) -> list[tuple[str, bytes]]:
    return [(f"g{entry['name']}", codec.build(entry["kind"], frame_from_file(source, entry)))]


def walk(rom: bytes, ver: str, run) -> list[tuple[int, int]]:
    spans, addr = [], run.start
    for _ in range(run.count):
        _, end, _ = codec.parse(rom, addr)
        spans.append((addr, end))
        addr = end
    return spans


def extract(rom: bytes, ver: str, run, source: Path, find) -> list[dict]:
    entries = []
    for name, (addr, _) in zip(run.names, walk(rom, ver, run)):
        (kind, tiles), end, raw = codec.parse(rom, addr)
        entry = {"name": name, "kind": kind, "tiles": len(tiles)}
        size, pixels = codec.sheet(tiles)
        blobs.write_png(source / f"{name}.png", size, pixels,
                        codec.GRAY8 if kind & codec.KIND_8BPP else codec.GRAY,
                        blobs.transparent_indices(False)[:1])
        if codec.build(kind, frame_from_file(source, entry)) != raw:
            raise ValueError(f"{name}: rebuilding from the PNG gives different bytes")
        entries.append(entry)
    return entries
