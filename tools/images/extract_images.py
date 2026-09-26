#!/usr/bin/env python3
"""Extract every image-bank manifest row from the baserom as indexed PNGs.

Each bank is walked from its start address: component lengths follow from
the components themselves (see sprite.component_length), so no pointer
table is read. The walk must end exactly at the bank's end address, and
every sprite must rebuild from its PNG byte for byte. Sprite names are the
bank's prefix plus a one-based position (Item001, Portrait001, ...), which
the generated labels and src/ tables use. See docs/formats/graphics.md
("Image-bank build format").

data/images/ is gitignored, same footing as the baserom (AGENTS.md hard
rule 2); extraction overwrites local PNG edits.

Usage: extract_images.py <ver> [--index-only] [bank ...]
  --index-only keeps existing PNGs and regenerates only bank.json.
"""
import sys
from pathlib import Path

from pack_images import image_banks
from sprite import extract_bank, component_length

ROM_BASE = 0x08000000

# Version-independent settings of each bank; ROM ranges live in the manifest.
BANKS = {
    "ItemIcons": {"prefix": "Item", "bpp": 4, "componentOrder": ("palette", "tiles", "frames")},
    "Portraits": {"prefix": "Portrait", "bpp": 8, "componentOrder": ("tiles", "frames", "palette")},
}


def split_bank(rom: bytes, start: int, end: int, name: str) -> list[tuple[str, dict[str, bytes]]]:
    settings = BANKS[name]
    sprites = []
    cursor = start - ROM_BASE
    while cursor < end - ROM_BASE:
        sprite_name = f"{settings['prefix']}{len(sprites) + 1:03d}"
        components = {}
        for kind in settings["componentOrder"]:
            data = rom[cursor:end - ROM_BASE]
            try:
                length = component_length(kind, data, settings["bpp"])
            except (ValueError, IndexError) as exc:
                raise ValueError(f"{name}: {sprite_name} {kind} at {cursor + ROM_BASE:#010x}: {exc}") from None
            components[kind] = data[:length]
            cursor += length
        sprites.append((sprite_name, components))
    if cursor != end - ROM_BASE:
        raise ValueError(f"{name}: walk ends at {cursor + ROM_BASE:#010x}, past the bank end {end:#010x}")
    return sprites


def main() -> None:
    args = sys.argv[1:]
    if not args or args[0].startswith("-"):
        sys.exit(f"usage: {sys.argv[0]} <ver> [--index-only] [bank ...]")
    ver, args = args[0], args[1:]
    index_only = "--index-only" in args
    wanted = [a for a in args if a != "--index-only"]
    try:
        rom = Path(f"baserom.{ver}.gba").read_bytes()
        banks = [row for row in image_banks(ver) if not wanted or row[3] in wanted]
        missing = set(wanted) - {row[3] for row in banks}
        if missing:
            raise ValueError(f"regions.{ver}.txt has no image-bank named {', '.join(sorted(missing))}")
        for start, end, source, name in banks:
            if name not in BANKS:
                raise ValueError(f"no extraction settings for image bank {name}")
            settings = BANKS[name]
            sprites = split_bank(rom, start, end, name)
            extract_bank(source, settings["bpp"], settings["componentOrder"], sprites, index_only)
            print(f"{ver}: {'indexed' if index_only else 'extracted'} {name}: {len(sprites)} images in {source}")
        if not banks:
            print(f"{ver}: no image-bank regions")
    except (OSError, ValueError) as exc:
        sys.exit(str(exc))


if __name__ == "__main__":
    main()
