"""fonts runs: fonts drawn as PNG glyph atlases (see tools/fonts/fonts.py and
docs/formats/fonts.md).

Settings: the ordered `fonts` list. Each font is labeled g<Name>.
"""
import re
from pathlib import Path

import blobs
import fonts as codec

ITEMS = "fonts"
SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
ENTRY_KEYS = {"name", "first", "last", "height", "widths"}
OPTIONAL_ENTRY_KEYS = {"flags"}


def check(run: dict) -> None:
    if set(run) != {ITEMS}:
        raise ValueError(f"expected {ITEMS}")
    names = set()
    for entry in run["fonts"]:
        if not ENTRY_KEYS <= set(entry) <= ENTRY_KEYS | OPTIONAL_ENTRY_KEYS:
            raise ValueError(f"{entry.get('name')}: unrecognized set of keys")
        name = entry["name"]
        if not isinstance(name, str) or not SYMBOL.fullmatch(name) or name in names:
            raise ValueError(f"invalid or duplicate font name {name!r}")
        names.add(name)
        for key in ("first", "last"):
            if not (isinstance(entry[key], int) and 0 <= entry[key] < 1 << 16):
                raise ValueError(f"{name}: {key} must be a 16-bit integer")
        if not (isinstance(entry["height"], int) and 0 < entry["height"] < 256):
            raise ValueError(f"{name}: height must be 1-255")
        widths = entry["widths"]
        if not (isinstance(widths, list) and len(widths) == entry["last"] - entry["first"] + 1
                and all(isinstance(w, int) and 0 < w < 256 for w in widths)):
            raise ValueError(f"{name}: widths must list one width (1-255) per glyph code")
        flags = entry.get("flags")
        if flags is not None and not (isinstance(flags, str) and len(flags) == len(widths)
                                      and set(flags) <= set("0123")):
            raise ValueError(f"{name}: flags must be one digit 0-3 per glyph code")


def item_files(run: dict, entry: dict) -> list[str]:
    return [f"{entry['name']}.png"]


def files(run: dict) -> list[str]:
    return [f for entry in run[ITEMS] for f in item_files(run, entry)]


def font_from_file(source: Path, entry: dict) -> codec.Font:
    size, pixels, _ = blobs.read_png(source / f"{entry['name']}.png")
    widths, height = entry["widths"], entry["height"]
    rows = (len(widths) + codec.GLYPHS_PER_ROW - 1) // codec.GLYPHS_PER_ROW
    if size != (codec.GLYPHS_PER_ROW * max(widths), rows * height):
        raise ValueError(f"{entry['name']}.png: expected {codec.GLYPHS_PER_ROW * max(widths)}x{rows * height}, "
                         f"got {size[0]}x{size[1]}")
    if max(pixels) > 3:
        raise ValueError(f"{entry['name']}.png: pixel value above 3")
    flags = [int(c) for c in entry["flags"]] if "flags" in entry else None
    return codec.Font(entry["first"], entry["last"], height, widths,
                      codec.glyphs_from_atlas(pixels, widths, height), flags)


def build(source: Path, name: str, settings: dict, entry: dict) -> list[tuple[str, bytes]]:
    return [(f"g{entry['name']}", codec.build(font_from_file(source, entry)))]


def extract(rom: bytes, ver: str, start: int, end: int, bank: str, source: Path) -> dict:
    addr, entries = start, []
    while addr < end:
        font, next_addr, raw = codec.parse(rom, addr)
        entry = {"name": f"{bank.removesuffix('s')}{len(entries):02d}", "first": font.first, "last": font.last,
                 "height": font.height, "widths": font.widths}
        if font.flags is not None:
            entry["flags"] = "".join(map(str, font.flags))
        size, pixels = codec.atlas(font)
        blobs.write_png(source / f"{entry['name']}.png", size, pixels, codec.GRAY, [0])
        if codec.build(font_from_file(source, entry)) != raw:
            raise ValueError(f"{entry['name']}: rebuilding from the PNG gives different bytes")
        entries.append(entry)
        addr = next_addr
    if addr != end:
        raise ValueError(f"walk ends at {addr:#010x}, not the row end {end:#010x}")
    return {ITEMS: entries}
