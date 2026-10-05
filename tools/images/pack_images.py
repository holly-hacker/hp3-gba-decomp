#!/usr/bin/env python3
"""Pack every image-bank manifest row from its PNG sprites and bank.json.

Each bank has one fixed ROM range. Its index lists the images in ROM order
with their settings (see sprite.py for the three entry kinds), the bank's
bit depth, and the order of each image's palette/tiles/frames components;
component addresses follow from that order and the encoded sizes. See docs/formats/graphics.md
("Image-bank build format"). Encoded components and assembly go under
build/<ver>/images/; the matching C header goes under include/gen/. Headers
depend only on bank.json, so a bank name must use the same directory in every
version's manifest.
"""
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import buildcache  # noqa: E402
from sprite import COMPONENT_KINDS, COMPRESSION_TYPES, OAM_SHAPES, build, image_files

SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
BANK_KEYS = {"format", "bpp", "componentOrder", "images"}
OPTIONAL_BANK_KEYS = {"paletteHeader", "paletteTrailer"}
ENTRY_KEYS = [
    {"name", "offset", "compression"},
    {"name", "palette", "header", "frames"},
    {"name", "palette", "header", "frames", "bpp"},
    {"name", "paletteOnly"},
    {"name", "paletteOnly", "highBits"},
]
FRAME_KEYS = {"offset", "compression", "cells", "parts", "extra"}
OPTIONAL_FRAME_KEYS = {"padding"}


def image_banks(ver: str, path: Path | None = None):
    path = path or Path(f"regions.{ver}.txt")
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


def load_index(source: Path) -> dict:
    index_path = source / "bank.json"
    index = json.loads(index_path.read_text())
    if not BANK_KEYS <= set(index) <= BANK_KEYS | OPTIONAL_BANK_KEYS or index["format"] != 2:
        raise ValueError(f"{index_path}: expected format 2 with {', '.join(sorted(BANK_KEYS))} "
                         f"(optionally {', '.join(sorted(OPTIONAL_BANK_KEYS))})")
    for key in OPTIONAL_BANK_KEYS & set(index):
        _ints(index[key], len(index[key]), f"{index_path}: {key}")
        if not all(0 <= b <= 0xFF for b in index[key]):
            raise ValueError(f"{index_path}: {key} must be a list of bytes")
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


def _build(source: Path, image: dict, bpp: int) -> dict[str, bytes]:
    """build(), with a failure naming the image."""
    try:
        return build(source, image, bpp)
    except (OSError, ValueError) as exc:
        raise ValueError(f"{source / image['name']}: {exc}") from None


def pack_bank(ver: str, start: int, end: int, source: Path, name: str, tools: str) -> int:
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
    images = index["images"]
    keys = [buildcache.digest(tools, index["bpp"], image,
                              [buildcache.file_digest(source / f) for f in image_files(image)])
            for image in images]
    built = buildcache.cached_map("images", _build, [(source, image, index["bpp"]) for image in images], keys)
    for image, components in zip(images, built):
        missing = set(components) - set(index["componentOrder"])
        if missing:
            raise ValueError(f"{name}: {image['name']} has {', '.join(sorted(missing))} "
                             "outside componentOrder")
        for kind in index["componentOrder"]:
            if kind not in components:
                continue
            data = components[kind]
            if kind == "palette":
                data = bytes(index.get("paletteHeader", [])) + data + bytes(index.get("paletteTrailer", []))
            symbol = component_symbol(image["name"], kind)
            bin_path = bin_dir / f"{image['name']}.{kind}.bin"
            buildcache.write_if_changed(bin_path, data)
            cursor += len(data)
            if cursor > end:
                raise ValueError(f"{name}: {image['name']} {kind} exceeds {end:#010x}")
            asm += [f"{symbol}:", f'.incbin "{bin_path.as_posix()}"']
            header.append(f"extern const u8 {symbol}[];")
    if cursor != end:
        raise ValueError(f"{name}: packed {cursor - start:#x} bytes; region needs {end - start:#x}")

    buildcache.write_if_changed(out / f"{name}.s", "\n".join(asm) + "\n")
    buildcache.write_if_changed(f"include/gen/{name}.h", "\n".join(header) + "\n")
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
        # Generated headers are shared between versions.
        sources = {name: source for _, _, source, name in banks}
        for other in sorted(Path(".").glob("regions.*.txt")):
            for _, _, source, name in image_banks(ver, other):
                if name in sources and sources[name] != source:
                    raise ValueError(f"{other}: image bank {name} uses {source}, "
                                     f"not {sources[name]} as in regions.{ver}.txt")
        tools = buildcache.tool_digest()
        for start, end, source, name in banks:
            count = pack_bank(ver, start, end, source, name, tools)
            print(f"{ver}: packed {name}: {count} images, {end - start} bytes")
        if not banks:
            print(f"{ver}: no image-bank regions")
    except (OSError, ValueError, TypeError) as exc:
        sys.exit(str(exc))


if __name__ == "__main__":
    main()
