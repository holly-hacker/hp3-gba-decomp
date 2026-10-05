"""image-bank runs: indexed PNG sprites and palettes (see tools/images/sprite.py).

Options: `bpp` (4 or 8); `componentOrder`, the ROM order of each image's
palette/tiles/frames components; `storedCells`, whether each frame keeps its
OAM cells (its palette is then optional per sprite, and a palette not
followed by tiles is its own image); `noPalette`, sprites without a palette
whose next data is not a tile stream (the palette of other records, or the
next run); and `paletteHeader`/`paletteTrailer`, bytes around every
palette; and `paletteSources`, which maps a sprite without a palette to
the item whose palette its PNGs are drawn with (display only; packing
ignores it). Each component is labeled g<Image><Component>. See
docs/formats/graphics.md ("Sprite images").
"""
import re
import struct
from pathlib import Path

from sprite import (COMPONENT_KINDS, COMPRESSION_TYPES, OAM_SHAPES, build as build_image, component_length,
                    extract_images, image_files, tile_stream_length)

ROM_BASE = 0x08000000
ITEMS = "images"
SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
OPTIONS = {"bpp": 4, "componentOrder": ["tiles", "frames", "palette"], "storedCells": True,
           "noPalette": [], "paletteHeader": [], "paletteTrailer": [], "paletteSources": {}}
ENTRY_KEYS = [
    {"name", "offset", "compression"},
    {"name", "palette", "header", "frames"},
    {"name", "palette", "header", "frames", "bpp"},
    {"name", "paletteOnly"},
    {"name", "paletteOnly", "highBits"},
]
FRAME_KEYS = {"offset", "compression", "cells", "parts", "extra"}
OPTIONAL_FRAME_KEYS = {"padding"}


def _ints(value, count: int, what: str) -> None:
    if (not isinstance(value, list) or len(value) != count
            or not all(isinstance(v, int) and not isinstance(v, bool) for v in value)):
        raise ValueError(f"{what} must be a list of {count} integers")


def check_compression(value) -> None:
    if value not in COMPRESSION_TYPES:
        raise ValueError(f"compression must be one of {', '.join(COMPRESSION_TYPES)}")


def check_entry(image: dict) -> None:
    if image.get("paletteOnly") is not None:
        if image["paletteOnly"] is not True:
            raise ValueError("paletteOnly must be true")
        _ints(image.get("highBits", []), len(image.get("highBits", [])), "highBits")
        if not all(0 <= i < 1 << 8 for i in image.get("highBits", [])):
            raise ValueError("highBits must be palette indices")
        return
    if "offset" in image:
        check_compression(image["compression"])
        _ints(image["offset"], 2, "offset")
        return
    if not isinstance(image["palette"], bool):
        raise ValueError("palette must be true or false")
    if image.get("bpp", 4) not in (4, 8) or ("bpp" in image and image["palette"]):
        raise ValueError("bpp must be 4 or 8, on a sprite without its own palette")
    _ints(image["header"], 4, "header")
    frames = image["frames"]
    if not isinstance(frames, list) or not frames:
        raise ValueError("frames must be a nonempty list")
    for frame in frames:
        if not isinstance(frame, dict) or not FRAME_KEYS <= set(frame) <= FRAME_KEYS | OPTIONAL_FRAME_KEYS:
            raise ValueError(f"each frame needs {', '.join(sorted(FRAME_KEYS))} "
                             f"(optionally {', '.join(sorted(OPTIONAL_FRAME_KEYS))})")
        check_compression(frame["compression"])
        if "padding" in frame:
            _ints(frame["padding"], len(frame["padding"]), "padding")
            if not all(0 <= b <= 0xFF for b in frame["padding"]):
                raise ValueError("padding must be a list of bytes")
        _ints(frame["offset"], 2, "frame offset")
        for cell in frame["cells"]:
            _ints(cell, 4, "cell")
            if tuple(cell[2:]) not in OAM_SHAPES:
                raise ValueError(f"cell size {cell[2]}x{cell[3]} is not an OAM shape")
        for part in frame["parts"]:
            _ints(part, 6, "part")
        _ints(frame["extra"], len(frame["extra"]), "extra")


def check(run: dict) -> None:
    sources = run["paletteSources"]
    if not isinstance(sources, dict) or not all(
            isinstance(k, str) and isinstance(v, str) and SYMBOL.fullmatch(v) for k, v in sources.items()):
        raise ValueError("paletteSources must map image names to item names")
    for key in ("paletteHeader", "paletteTrailer"):
        _ints(run[key], len(run[key]), key)
        if not all(0 <= b <= 0xFF for b in run[key]):
            raise ValueError(f"{key} must be a list of bytes")
    if run["bpp"] not in (4, 8) or not isinstance(run["storedCells"], bool):
        raise ValueError("bpp must be 4 or 8, and storedCells true or false")
    order = run["componentOrder"]
    if not order or len(set(order)) != len(order) or not set(order) <= set(COMPONENT_KINDS):
        raise ValueError(f"componentOrder must list distinct kinds from {', '.join(COMPONENT_KINDS)}")
    images = run["images"]
    if not isinstance(images, list) or not images:
        raise ValueError("images must be a nonempty list")
    names = set()
    for i, image in enumerate(images):
        if not isinstance(image, dict) or set(image) not in ENTRY_KEYS:
            raise ValueError(f"image {i} has an unrecognized set of keys")
        name = image["name"]
        if not isinstance(name, str) or not SYMBOL.fullmatch(name) or name in names:
            raise ValueError(f"invalid or duplicate image name {name!r}")
        names.add(name)
        try:
            check_entry(image)
        except (ValueError, TypeError) as exc:
            raise ValueError(f"{name}: {exc}") from None


def files(run: dict) -> list[str]:
    return [f for image in run["images"] for f in image_files(image)]


def item_files(image: dict) -> list[str]:
    return image_files(image)


def build(source: Path, settings: dict, image: dict) -> list[tuple[str, bytes]]:
    try:
        components = build_image(source, image, settings["bpp"])
    except (OSError, ValueError) as exc:
        raise ValueError(f"{source / image['name']}: {exc}") from None
    missing = set(components) - set(settings["componentOrder"])
    if missing:
        raise ValueError(f"{image['name']} has {', '.join(sorted(missing))} outside componentOrder")
    pieces = []
    for kind in settings["componentOrder"]:
        if kind in components:
            data = components[kind]
            if kind == "palette":
                data = bytes(settings["paletteHeader"]) + data + bytes(settings["paletteTrailer"])
            pieces.append((f"g{image['name']}{kind.capitalize()}", data))
    return pieces


def split_bank(rom: bytes, run, palettes: dict[str, int] | None = None
               ) -> list[tuple[str, int, int, dict[str, bytes]]]:
    """Each image of a run, from its start: (name, start, end, components).
    palettes, when given, receives each palette's ROM address by image name."""
    settings = run.options
    bpp, stored = settings["bpp"], settings["storedCells"]
    entries = []
    cursor, limit = run.start - ROM_BASE, run.limit - ROM_BASE
    for entry_name in run.names:
        entry_start = cursor
        components = {}
        if stored and tile_stream_length(rom[cursor:limit]) is None:
            components["palette"] = rom[cursor:cursor + (2 << bpp)]
            if palettes is not None:
                palettes[entry_name] = cursor + ROM_BASE
            cursor += 2 << bpp
            entries.append((entry_name, entry_start + ROM_BASE, cursor + ROM_BASE, components))
            continue
        for kind in settings["componentOrder"]:
            start_at = cursor
            try:
                if kind == "tiles":
                    # One stream per frame, back to back.
                    while cursor < limit and (length := tile_stream_length(rom[cursor:limit])):
                        cursor += length
                    if cursor == start_at:
                        raise ValueError("no tile stream starts here")
                elif kind == "palette" and stored and (
                        entry_name in settings["noPalette"]
                        or tile_stream_length(rom[cursor:limit]) is not None):
                    continue
                elif kind == "palette":
                    header, trailer = settings["paletteHeader"], settings["paletteTrailer"]
                    if list(rom[cursor:cursor + len(header)]) != header:
                        raise ValueError(f"palette header is not {bytes(header).hex()}")
                    cursor += len(header)
                    palette_at = cursor
                    cursor += component_length(kind, rom[cursor:limit], bpp)
                    if list(rom[cursor:cursor + len(trailer)]) != trailer:
                        raise ValueError(f"palette trailer is not {bytes(trailer).hex()}")
                    components[kind] = rom[palette_at:cursor]
                    if palettes is not None:
                        palettes[entry_name] = palette_at + ROM_BASE
                    cursor += len(trailer)
                    continue
                else:
                    cursor += component_length(kind, rom[cursor:limit], bpp)
            except (ValueError, IndexError, struct.error) as exc:
                raise ValueError(f"{entry_name} {kind} at {start_at + ROM_BASE:#010x}: {exc}") from None
            components[kind] = rom[start_at:cursor]
        entries.append((entry_name, entry_start + ROM_BASE, cursor + ROM_BASE, components))
    return entries


def walk(rom: bytes, ver: str, run) -> list[tuple[int, int]]:
    return [(start, end) for _, start, end, _ in split_bank(rom, run)]


def palettes(rom: bytes, ver: str, run) -> dict[str, int]:
    """The ROM address of each image's palette, by image name."""
    found = {}
    split_bank(rom, run, found)
    return found


def extract(rom: bytes, ver: str, run, source: Path, find) -> list[dict]:
    size = 2 << run.options["bpp"]
    shown = {}
    for name, item in run.options["paletteSources"].items():
        addr = find(f"{item}.palette") - ROM_BASE
        shown[name] = rom[addr:addr + size]
    return extract_images(source, run.options["bpp"], [(n, c) for n, _, _, c in split_bank(rom, run)],
                          run.options["storedCells"], shown)
