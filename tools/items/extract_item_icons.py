#!/usr/bin/env python3
"""One-time bootstrap: extract every real item's icon data
(g_pItemTable's pPalette/pTileData/pFrameData, see
tools/items/icon_codec.py) verbatim to data/images/items/, and render
each to a viewable PNG under extracted/graphics/items/ for humans -- see
docs/formats/graphics.md's "Item icons" section.

Reads baserom.us.gba directly -- src/data/items.c references the packed
labels by name, not by address. The ROM's g_pItemTable identifies each
component. The extractor also writes bank.json in component order for the
shared image-bank packer. --index-only regenerates that index without
overwriting existing local assets.

All 79 real items' icon data is one fully contiguous ROM span with
zero gaps between items, in table order -- this is verified below
(the extraction fails loudly if a future baserom ever breaks that),
not assumed. Each item's 3 pieces are written as 3 SEPARATE files
(Item001.palette.bin/.tiles.bin/.frames.bin, etc.), not one concatenated
blob: palette is a fixed 32 bytes by format (2-byte header + 15
colors, a convention hard-coded in the consuming code, see
graphics.md), but the frame-header's length is not -- it depends on
fields stored inside it (frame count, sub-entry counts), and nothing
in the tile data preceding it declares how many bytes the compressed
stream actually occupies. Keeping them as separate files means each
one's own length is its boundary; no offset/length has to be stored
anywhere to parse them back apart.

data/images/items/ is gitignored, same footing as the baserom (hard
rule 2, AGENTS.md) -- every clone needs to run this once (see the
`extract-item-icons` recipe) before building. extracted/ is a
different, fully gitignored tree for human-viewing output only -- the
PNGs there are never build input (see justfile).

Usage: extract_item_icons.py [--index-only]
  Without the flag, reads baserom.us.gba and writes local .bin files,
  bank.json, and viewable PNGs. --index-only writes only bank.json.
"""
import json
import sys
from pathlib import Path

from PIL import Image

sys.path.insert(0, str(Path(__file__).parent))
from icon_codec import decode_icon
from item_codec import ITEM_TABLE_ADDR, REAL_ITEM_COUNT, RECORD_SIZE, icon_labels, icon_stem, unpack_record

ROM_BASE = 0x08000000
VER = "us"

PALETTE_SIZE = 0x20
FRAMES_SIZE = 0x1C
# The next icon resource after the 79th real item's frame-header --
# FUN_08026bcc's id==0x86 special case (`&DAT_080ac6a0`), an
# equip-slot placeholder outside this table. Confirms the region's
# true end independently of the table itself.
NEXT_RESOURCE_ADDR = 0x080AC6A0


def main() -> None:
    if sys.argv[1:] not in ([], ["--index-only"]):
        sys.exit(f"usage: {sys.argv[0]} [--index-only]")
    index_only = sys.argv[1:] == ["--index-only"]
    with open(f"baserom.{VER}.gba", "rb") as f:
        rom = f.read()

    base = ITEM_TABLE_ADDR - ROM_BASE
    records = []
    for i in range(REAL_ITEM_COUNT):
        off = base + i * RECORD_SIZE
        record = unpack_record(rom[off:off + RECORD_SIZE])
        records.append(record)

    # Verify the whole span is one contiguous run before extracting anything
    # -- see module docstring. Fails loudly rather than silently extracting
    # a wrong/truncated byte range.
    for i, record in enumerate(records):
        pPalette, pTileData, pFrameData = record["pPalette"], record["pTileData"], record["pFrameData"]
        if pTileData - pPalette != PALETTE_SIZE:
            sys.exit(f"item {i + 1}: palette is {pTileData - pPalette:#x} bytes, expected {PALETTE_SIZE:#x}")
        frames_end = pFrameData + FRAMES_SIZE
        next_addr = records[i + 1]["pPalette"] if i + 1 < len(records) else NEXT_RESOURCE_ADDR
        if frames_end != next_addr:
            sys.exit(f"item {i + 1}: frame-header ends at {frames_end:#010x}, "
                      f"expected the next resource to start there ({next_addr:#010x}) -- "
                      f"icon data is not contiguous, extraction assumptions are wrong")

    images_dir = Path("data/images/items")
    images_dir.mkdir(parents=True, exist_ok=True)
    extracted_dir = Path("extracted/graphics/items")
    if not index_only:
        extracted_dir.mkdir(parents=True, exist_ok=True)

    components = []
    for i, record in enumerate(records):
        pPalette, pTileData, pFrameData = record["pPalette"], record["pTileData"], record["pFrameData"]
        stem = icon_stem(i)
        for kind, symbol in zip(("palette", "tiles", "frames"), icon_labels(i)):
            component = f"{stem}.{kind}.bin"
            if index_only and not (images_dir / component).is_file():
                sys.exit(f"missing {images_dir / component}; run extract-item-icons first")
            components.append({"file": component, "symbol": symbol})

        if index_only:
            continue

        palette_bytes = rom[pPalette - ROM_BASE:pTileData - ROM_BASE]
        tiles_bytes = rom[pTileData - ROM_BASE:pFrameData - ROM_BASE]
        frames_bytes = rom[pFrameData - ROM_BASE:pFrameData - ROM_BASE + FRAMES_SIZE]
        (images_dir / f"{stem}.palette.bin").write_bytes(palette_bytes)
        (images_dir / f"{stem}.tiles.bin").write_bytes(tiles_bytes)
        (images_dir / f"{stem}.frames.bin").write_bytes(frames_bytes)

        width, height, pixels = decode_icon(rom, VER, pPalette, pTileData, pFrameData)
        img = Image.new("RGBA", (width, height))
        img.putdata(pixels)
        img.save(extracted_dir / f"{stem}.png")

    (images_dir / "bank.json").write_text(json.dumps({"format": 1, "components": components}, indent=2) + "\n")
    if index_only:
        print(f"indexed {REAL_ITEM_COUNT} existing item icons in {images_dir / 'bank.json'}", file=sys.stderr)
    else:
        print(f"{REAL_ITEM_COUNT} item icons -> {images_dir}/*.bin, {extracted_dir}/*.png", file=sys.stderr)


if __name__ == "__main__":
    main()
