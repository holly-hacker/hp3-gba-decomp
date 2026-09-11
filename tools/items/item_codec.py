"""Shared record layout for the item/equipment table (g_pItemTable) and
its icon-naming convention. See docs/formats/items.md for field
semantics and how they were identified.

The table itself is committed as matched C source, src/data/items.c --
see docs/formats/items.md's "The extraction pipeline" section. This
module now serves only the item-icon extraction/pack pipeline
(extract_item_icons.py, pack_item_icons.py), which still needs to
locate each real item's record in the raw ROM and derive its icon's
label names.

52 bytes per record, all fields 4-byte little-endian, in on-disk order.
"""
import re
import struct
from pathlib import Path

# (field name, struct format char). "n"-prefixed fields are Ghidra's
# `int` (signed); "dw"/pointer fields are `undefined4`/pointer (unsigned).
FIELDS: list[tuple[str, str]] = [
    ("nNameTextId", "i"),        # 0x00 -- dialog string id for the display name
    ("pPalette", "I"),           # 0x04 -- palette pointer
    ("pTileData", "I"),          # 0x08 -- compressed tile-data pointer
    ("pFrameData", "I"),         # 0x0C -- frame/layout header pointer
    ("nBuyPrice", "i"),          # 0x10 -- shop buy price (Sickles)
    ("nSellPrice", "i"),         # 0x14 -- shop sell price (Sickles)
    ("dwCategory", "I"),         # 0x18 -- item category id (0x0-0x6, 0x8 used; 0x7 unused; 0xC on the dummy)
    ("nCharacterMask", "i"),     # 0x1C -- per-character equip mask
    ("dwUnk20", "I"),            # 0x20 -- flag word, bit 2 tested
    ("nDefenseX2", "i"),         # 0x24 -- Def stat, pre-doubled
    ("nAgility", "i"),           # 0x28 -- Agi stat, signed
    ("dwUnk2C", "I"),            # 0x2C -- unidentified
    ("dwMagicDefense", "I"),     # 0x30 -- M.Def stat
]

FIELD_STRUCT_FORMAT = "<" + "".join(fmt for _, fmt in FIELDS)
RECORD_SIZE = struct.calcsize(FIELD_STRUCT_FORMAT)
assert RECORD_SIZE == 0x34

ITEM_TABLE_ADDR = 0x08060EE4

# Indices 0..REAL_ITEM_COUNT-1 (79 entries) are real items -- PROVEN, see
# docs/formats/save.md "Item quantities and equipment": FUN_08026F48
# walks 0-78 (cmp r1, #0x4e) as the real-item bound. Index 79 is a dummy
# record (nNameTextId=0, dwCategory=0xC, icon pointers cloned from index
# 62's Rat Tonic) marking the end of the real items; indices 80-131 are
# genuine slots of the same 132-entry allocation but hold no item data
# at all (all-zero records).
REAL_ITEM_COUNT = 79


def unpack_record(data: bytes) -> dict:
    assert len(data) == RECORD_SIZE
    values = struct.unpack(FIELD_STRUCT_FORMAT, data)
    return {name: value for (name, _fmt), value in zip(FIELDS, values)}


def icon_slug(name: str) -> str:
    """PascalCase identifier derived from an item's display name, e.g.
    "Chocolate Frogs" -> "ChocolateFrogs". Used for the extracted PNG's
    filename, the data/images/items/*.bin filenames, and the
    icon_labels() symbol names, so all three stay in lockstep without
    being stored anywhere."""
    words = re.findall(r"[A-Za-z0-9]+", name)
    return "".join(word[0].upper() + word[1:] for word in words)


def icon_labels(slug: str) -> tuple[str, str, str]:
    """(palette, tiles, frames) label names for an item's icon_slug(),
    matching both src/data/items.c's `extern` declarations and the
    labels tools/items/pack_item_icons.py emits inside the
    `item-icon-data` region."""
    return (f"gItemIcon{slug}Palette", f"gItemIcon{slug}Tiles", f"gItemIcon{slug}Frames")


def icon_bin_paths(images_dir, slug: str):
    """(palette, tiles, frames) file paths for an item's icon_slug(),
    under the data/images/items/ directory `images_dir` -- e.g.
    data/images/items/OrdinaryBelt.palette.bin. Each file's own length is
    its data's boundary; no separate offset/length needs to be stored."""
    return tuple(Path(images_dir) / f"{slug}.{kind}.bin" for kind in ("palette", "tiles", "frames"))
