"""Shared record layout for the item/equipment table (g_pItemTable).
See docs/formats/items.md for field
semantics and how they were identified.

The table itself is committed as matched C source, src/data/items.c --
see docs/formats/items.md's "The extraction pipeline" section. This
module serves item-icon extraction (extract_item_icons.py), which locates
each real item's record in the raw ROM and assigns a numbered file stem.
The shared
tools/images/pack_images.py consumes the extracted bank.json index.

52 bytes per record, all fields 4-byte little-endian, in on-disk order.
"""
import struct

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


def icon_stem(index: int) -> str:
    """One-based, stable file stem in item-table order (Item001, ...)."""
    return f"Item{index + 1:03d}"


def icon_labels(index: int) -> tuple[str, str, str]:
    """Assembly labels matching the three components of one item icon."""
    stem = icon_stem(index)
    return (f"g{stem}Palette", f"g{stem}Tiles", f"g{stem}Frames")
