#!/usr/bin/env python3
"""Pack every image-bank manifest row from its PNG sprites and bank.json.

Each bank has one fixed ROM range. Its index lists the images in ROM order
with their settings (see sprite.py for the three entry kinds), the bank's
bit depth, and the order of each image's palette/tiles/frames components;
component addresses follow from that order and the encoded sizes. See docs/formats/graphics.md
("Image-bank build format"). Encoded components and assembly go under
build/<ver>/images/; the matching C header goes under include/gen/<ver>/.
"""
import json
import re
import sys
from pathlib import Path

from sprite import COMPONENT_KINDS, COMPRESSION_TYPES, OAM_SHAPES, build, image_files

SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
BANK_KEYS = {"format", "bpp", "componentOrder", "images"}
ENTRY_KEYS = [
    {"name", "offset", "compression"},
    {"name", "palette", "header", "frames"},
    {"name", "paletteOnly"},
]
FRAME_KEYS = {"offset", "compression", "cells", "parts", "extra"}


def image_banks(ver: str):
    path = Path(f"regions.{ver}.txt")
    for lineno, raw in enumerate(path.read_text().splitlines(), 1):
        parts = raw.split("#", 1)[0].split()
        if not parts or parts[0] != "image-bank":
            continue
        if len(parts) != 5:
            raise ValueError(f"{path}:{lineno}: expected image-bank <start> <end> <dir> <name>")
        _, start, end, source, name = parts
        if not SYMBOL.fullmatch(name):
            raise ValueError(f"{path}:{lineno}: invalid bank name {name!r}")
        yield int(start, 16), int(end, 16), Path(source), name


def component_symbol(image: str, kind: str) -> str:
    return f"g{image}{kind.capitalize()}"


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
        return
    if "offset" in image:
        check_compression(image["compression"])
        _ints(image["offset"], 2, "offset")
        return
    if not isinstance(image["palette"], bool):
        raise ValueError("palette must be true or false")
    _ints(image["header"], 4, "header")
    frames = image["frames"]
    if not isinstance(frames, list) or not frames:
        raise ValueError("frames must be a nonempty list")
    for frame in frames:
        if not isinstance(frame, dict) or set(frame) != FRAME_KEYS:
            raise ValueError(f"each frame needs {', '.join(sorted(FRAME_KEYS))}")
        check_compression(frame["compression"])
        _ints(frame["offset"], 2, "frame offset")
        for cell in frame["cells"]:
            _ints(cell, 4, "cell")
            if tuple(cell[2:]) not in OAM_SHAPES:
                raise ValueError(f"cell size {cell[2]}x{cell[3]} is not an OAM shape")
        for part in frame["parts"]:
            _ints(part, 6, "part")
        _ints(frame["extra"], len(frame["extra"]), "extra")


def load_index(source: Path) -> dict:
    index_path = source / "bank.json"
    index = json.loads(index_path.read_text())
    if set(index) != BANK_KEYS or index["format"] != 2:
        raise ValueError(f"{index_path}: expected format 2 with {', '.join(sorted(BANK_KEYS))}")
    if index["bpp"] not in (4, 8):
        raise ValueError(f"{index_path}: bpp must be 4 or 8")
    order = index["componentOrder"]
    if not order or len(set(order)) != len(order) or not set(order) <= set(COMPONENT_KINDS):
        raise ValueError(f"{index_path}: componentOrder must list distinct kinds from "
                         f"{', '.join(COMPONENT_KINDS)}")
    images = index["images"]
    if not isinstance(images, list) or not images:
        raise ValueError(f"{index_path}: images must be a nonempty list")
    names, files = set(), set()
    for i, image in enumerate(images):
        if not isinstance(image, dict) or set(image) not in ENTRY_KEYS:
            raise ValueError(f"{index_path}: image {i} has an unrecognized set of keys")
        name = image["name"]
        if not isinstance(name, str) or not SYMBOL.fullmatch(name) or name in names:
            raise ValueError(f"{index_path}: invalid or duplicate image name {name!r}")
        names.add(name)
        try:
            check_entry(image)
        except (ValueError, TypeError) as exc:
            raise ValueError(f"{index_path}: {name}: {exc}") from None
        files.update(image_files(image))
    extras = {p.name for p in source.glob("*.png")} - files
    if extras:
        raise ValueError(f"{index_path}: unlisted PNG files: {', '.join(sorted(extras))}")
    return index


def pack_bank(ver: str, start: int, end: int, source: Path, name: str) -> int:
    index = load_index(source)
    out = Path(f"build/{ver}/images")
    bin_dir = out / name
    bin_dir.mkdir(parents=True, exist_ok=True)
    asm = []
    header = [
        "/* Code generated by tools/images/pack_images.py; DO NOT EDIT. */",
        "#pragma once",
        "",
        '#include "types.h"',
        "",
    ]
    cursor = start
    for image in index["images"]:
        try:
            components = build(source, image, index["bpp"])
        except (OSError, ValueError) as exc:
            raise ValueError(f"{source / image['name']}: {exc}") from None
        missing = set(components) - set(index["componentOrder"])
        if missing:
            raise ValueError(f"{name}: {image['name']} has {', '.join(sorted(missing))} "
                             "outside componentOrder")
        for kind in index["componentOrder"]:
            if kind not in components:
                continue
            data = components[kind]
            symbol = component_symbol(image["name"], kind)
            bin_path = bin_dir / f"{image['name']}.{kind}.bin"
            if not bin_path.is_file() or bin_path.read_bytes() != data:
                bin_path.write_bytes(data)
            cursor += len(data)
            if cursor > end:
                raise ValueError(f"{name}: {image['name']} {kind} exceeds {end:#010x}")
            asm += [f"{symbol}:", f'.incbin "{bin_path.as_posix()}"']
            header.append(f"extern const u8 {symbol}[];")
    if cursor != end:
        raise ValueError(f"{name}: packed {cursor - start:#x} bytes; region needs {end - start:#x}")

    header_out = Path(f"include/gen/{ver}")
    header_out.mkdir(parents=True, exist_ok=True)
    (out / f"{name}.s").write_text("\n".join(asm) + "\n")
    (header_out / f"{name}.h").write_text("\n".join(header) + "\n")
    return len(index["images"])


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]
    try:
        banks = list(image_banks(ver))
        names = [name for _, _, _, name in banks]
        if len(names) != len(set(names)):
            raise ValueError(f"regions.{ver}.txt: duplicate image-bank name")
        for start, end, source, name in banks:
            count = pack_bank(ver, start, end, source, name)
            print(f"{ver}: packed {name}: {count} images, {end - start} bytes")
        if not banks:
            print(f"{ver}: no image-bank regions")
    except (OSError, ValueError, TypeError) as exc:
        sys.exit(str(exc))


if __name__ == "__main__":
    main()
