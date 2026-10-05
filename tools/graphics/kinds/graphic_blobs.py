"""graphic-blobs runs: graphic blobs (see tools/graphic_blob/blobs.py).

Each blob is labeled g<Name>. Blobs without a palette draw with one that is
already loaded; the option `paletteSources` maps such a blob to the item
whose colors its PNG shows, recorded as its `palette` setting, which packing
does not use. A blob whose tiles and tilemap the standard rebuild does not
reproduce lists its tilemap cells' tiles and flips as `layout`. See
docs/formats/graphic_blob.md.
"""
import re
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

import blobs

ITEMS = "blobs"
SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
ENTRY_KEYS = {"name", "flags"}
OPTIONAL_ENTRY_KEYS = {"highBits", "unused", "palette", "layout"}
OPTIONS = {"paletteSources": {}}

def check(run: dict) -> None:
    if not all(isinstance(v, str) for v in run["paletteSources"].values()):
        raise ValueError("paletteSources must map blob names to item names")
    names = set()
    for entry in run["blobs"]:
        if not ENTRY_KEYS <= set(entry) <= ENTRY_KEYS | OPTIONAL_ENTRY_KEYS:
            raise ValueError(f"{entry.get('name')}: unrecognized set of keys")
        name = entry["name"]
        if not isinstance(name, str) or not SYMBOL.fullmatch(name) or name in names:
            raise ValueError(f"invalid or duplicate blob name {name!r}")
        names.add(name)
        flags = entry["flags"]
        if not (isinstance(flags, list) and len(flags) == 2 and all(isinstance(f, int) and 0 <= f < 256 for f in flags)):
            raise ValueError(f"{name}: flags must be two bytes")
        blobs.check_flags(*flags)
        for key in OPTIONAL_ENTRY_KEYS & set(entry):
            value = entry[key]
            if key == "palette":
                ok = isinstance(value, str) and SYMBOL.fullmatch(value)
            elif key == "layout":
                ok = isinstance(value, list) and all(isinstance(i, int) and 0 <= i < 0x1000 for i in value)
            elif key == "unused":
                ok = isinstance(value, int) and value > 0
            else:
                ok = isinstance(value, list) and all(isinstance(i, int) and 0 <= i < 256 for i in value)
            if not ok:
                raise ValueError(f"{name}: invalid {key}")


def item_files(entry: dict) -> list[str]:
    return [f"{entry['name']}.png"] + ([f"{entry['name']}.unused.png"] if entry.get("unused") else [])


def files(run: dict) -> list[str]:
    return [f for entry in run[ITEMS] for f in item_files(entry)]


def blob_from_files(source: Path, entry: dict) -> blobs.Blob:
    size, pixels, colors = blobs.read_png(source / f"{entry['name']}.png")
    if size[0] % 8 or size[1] % 8:
        raise ValueError(f"{entry['name']}.png: {size[0]}x{size[1]} is not a multiple of 8 pixels")
    unused = []
    if entry.get("unused"):
        _, sheet, _ = blobs.read_png(source / f"{entry['name']}.unused.png")
        unused = blobs.unused_from_sheet(sheet, entry["unused"])
    flags0 = entry["flags"][0]
    palette = None
    if flags0 & 3:
        palette = blobs.encode_palette(colors, entry.get("highBits", []), 256 if flags0 & 1 else 16)
    return blobs.blob_from_image(*entry["flags"], palette, size[0] // 8, size[1] // 8, pixels, unused,
                                   entry.get("layout"))


def build(source: Path, settings: dict, entry: dict) -> list[tuple[str, bytes]]:
    return [(f"g{entry['name']}", blobs.build(blob_from_files(source, entry)))]


def walk(rom: bytes, ver: str, run) -> list[tuple[int, int]]:
    spans, addr = [], run.start
    for _ in range(run.count):
        _, end, _ = blobs.parse(rom, addr)
        spans.append((addr, end))
        addr = end
    return spans


def gray_palette(bpp8: bool):
    return [((i if bpp8 else (i % 16) * 17),) * 3 for i in range(256)]


def write_blob(source, name, palette_from, colors, blob, raw):
    high = []
    if blob.palette is not None:
        colors, high = blobs.decode_palette(blob.palette)
    size = (blob.width * 8, blob.height * 8)
    transparent = blobs.transparent_indices(blob.bpp8)
    blobs.write_png(source / f"{name}.png", size, blobs.image_pixels(blob), colors, transparent)
    entry = {"name": name, "flags": [blob.flags0, blob.flags1]}
    if palette_from:
        entry["palette"] = palette_from
    if high:
        entry["highBits"] = high
    unused = blob.tiles[blobs.used_tiles(blob):]
    if unused:
        entry["unused"] = len(unused)
        size, pixels = blobs.unused_sheet(unused)
        blobs.write_png(source / f"{name}.unused.png", size, pixels, colors, transparent)
    rebuilt = blobs.build(blob_from_files(source, entry))
    if rebuilt != raw:
        entry["layout"] = blobs.layout_of(blob)
        rebuilt = blobs.build(blob_from_files(source, entry))
    if rebuilt != raw:
        raise ValueError(f"{name}: rebuilding from the PNGs gives different bytes")
    return entry


def extract(rom: bytes, ver: str, run, source: Path, find) -> list[dict]:
    jobs = []
    for name, (addr, _) in zip(run.names, walk(rom, ver, run)):
        blob, _, raw = blobs.parse(rom, addr)
        palette_from = run.options["paletteSources"].get(name)
        colors = gray_palette(blob.bpp8)
        if palette_from:
            colors, _ = blobs.decode_palette(blobs.parse(rom, find(palette_from))[0].palette)
        jobs.append((source, name, palette_from, colors, blob, raw))
    with ProcessPoolExecutor() as pool:
        return list(pool.map(write_blob, *zip(*jobs)))
