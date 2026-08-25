#!/usr/bin/env python3
"""One-time bootstrap: extract every real item's icon data
(g_pItemTable's pPalette/pTileData/pFrameData, see
tools/items/icon_codec.py) verbatim to data/images/items/, and render
each to a viewable PNG under extracted/items/ for humans -- see
docs/formats/graphics.md's "Item icons" section.

Reads baserom.us.gba directly rather than data/items/items.json --
real items no longer carry pPalette/pTileData/pFrameData in that JSON
at all (see item_codec module docstring); those addresses are recorded
nowhere but regions.us.txt's single `item-icon-data` row, so this
script re-derives them from the ROM the same way extract_items.py
does, purely to locate and copy bytes -- nothing from this pass gets
written back into JSON.

All 79 real items' icon data is one fully contiguous ROM span with
zero gaps between items, in table order -- this is verified below
(the extraction fails loudly if a future baserom ever breaks that),
not assumed. Each item's 3 pieces are written as 3 SEPARATE files
(<Name>.palette.bin/.tiles.bin/.frames.bin), not one concatenated
blob: palette is a fixed 32 bytes by format (2-byte header + 15
colors, a convention hard-coded in the consuming code, see
graphics.md), but the frame-header's length is not -- it depends on
fields stored inside it (frame count, sub-entry counts), and nothing
in the tile data preceding it declares how many bytes the compressed
stream actually occupies. Keeping them as separate files means each
one's own length is its boundary; no offset/length has to be stored
anywhere to parse them back apart.

data/images/items/ is gitignored, same footing as the baserom (hard
rule 2, CLAUDE.md) -- every clone needs to run this once (see the
`extract-item-icons` recipe) before building. extracted/ is a
different, fully gitignored tree for human-viewing output only -- the
PNGs there are never build input (see justfile).

Usage: extract_item_icons.py   (reads baserom.us.gba, writes
                                 data/images/items/*.bin and
                                 extracted/items/*.png)
"""
import sys
from pathlib import Path

from PIL import Image

sys.path.insert(0, str(Path(__file__).parent))
from icon_codec import decode_icon
from item_codec import ITEM_TABLE_ADDR, REAL_ITEM_COUNT, RECORD_SIZE, icon_slug, unpack_record

sys.path.insert(0, str(Path(__file__).parent.parent / "text"))
from decode_dialog_text import decode_dialog_text

ROM_BASE = 0x08000000
VER = "us"

PALETTE_SIZE = 0x20
FRAMES_SIZE = 0x1C
# The next icon resource after the 79th real item's frame-header --
# FUN_08026bcc's id==0x86 special case (`&DAT_080ac6a0`), an
# equip-slot placeholder outside this table. Confirms the region's
# true end independently of the table itself.
NEXT_RESOURCE_ADDR = 0x080AC6A0


def decode_name(rom: bytes, string_id: int) -> str:
    data = decode_dialog_text(rom, 0, string_id).rstrip(b"\x00")  # lang 0 = English US
    return data.decode("latin-1")


def main() -> None:
    with open(f"baserom.{VER}.gba", "rb") as f:
        rom = f.read()

    base = ITEM_TABLE_ADDR - ROM_BASE
    records = []
    for i in range(REAL_ITEM_COUNT):
        off = base + i * RECORD_SIZE
        record = unpack_record(rom[off:off + RECORD_SIZE])
        records.append((decode_name(rom, record["nNameTextId"]), record))

    # Verify the whole span is one contiguous run before extracting anything
    # -- see module docstring. Fails loudly rather than silently extracting
    # a wrong/truncated byte range.
    for i, (name, record) in enumerate(records):
        pPalette, pTileData, pFrameData = record["pPalette"], record["pTileData"], record["pFrameData"]
        if pTileData - pPalette != PALETTE_SIZE:
            sys.exit(f"{name!r} (index {i}): palette is {pTileData - pPalette:#x} bytes, expected {PALETTE_SIZE:#x}")
        frames_end = pFrameData + FRAMES_SIZE
        next_addr = records[i + 1][1]["pPalette"] if i + 1 < len(records) else NEXT_RESOURCE_ADDR
        if frames_end != next_addr:
            sys.exit(f"{name!r} (index {i}): frame-header ends at {frames_end:#010x}, "
                      f"expected the next resource to start there ({next_addr:#010x}) -- "
                      f"icon data is not contiguous, extraction assumptions are wrong")

    images_dir = Path("data/images/items")
    images_dir.mkdir(parents=True, exist_ok=True)
    extracted_dir = Path("extracted/items")
    extracted_dir.mkdir(parents=True, exist_ok=True)

    for i, (name, record) in enumerate(records):
        pPalette, pTileData, pFrameData = record["pPalette"], record["pTileData"], record["pFrameData"]
        slug = icon_slug(name)

        palette_bytes = rom[pPalette - ROM_BASE:pTileData - ROM_BASE]
        tiles_bytes = rom[pTileData - ROM_BASE:pFrameData - ROM_BASE]
        frames_bytes = rom[pFrameData - ROM_BASE:pFrameData - ROM_BASE + FRAMES_SIZE]
        (images_dir / f"{slug}.palette.bin").write_bytes(palette_bytes)
        (images_dir / f"{slug}.tiles.bin").write_bytes(tiles_bytes)
        (images_dir / f"{slug}.frames.bin").write_bytes(frames_bytes)

        width, height, pixels = decode_icon(rom, VER, pPalette, pTileData, pFrameData)
        img = Image.new("RGBA", (width, height))
        img.putdata(pixels)
        img.save(extracted_dir / f"{slug}.png")

    print(f"{REAL_ITEM_COUNT} item icons -> {images_dir}/*.bin, {extracted_dir}/*.png", file=sys.stderr)


if __name__ == "__main__":
    main()
