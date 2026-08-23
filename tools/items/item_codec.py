"""Shared record layout for the item/equipment table
(g_pItemTable). See docs/formats/save.md's "Item quantities and
equipment" section for how the table's address/stride/count and each
field were identified.

52 bytes per record, all fields 4-byte little-endian, in on-disk order.
Fields whose meaning isn't confirmed keep the project's Ghidra-matching
unk names (nUnk14, nUnk1C, dwUnk20, dwUnk2C, dwUnk30) rather than an
offset-derived placeholder, since those are the actual database names.

pIcon1/pIcon2/pIcon3 point respectively at a palette, type-4-codec
compressed tile data, and a frame/layout header -- see
docs/formats/graphics.md's "Item icons" section. A real item's record
carries no icon pointers in JSON at all: its icon is referenced by
`sIconPath` (e.g. "items/OrdinaryBelt.png", the viewable render at
`extracted/items/OrdinaryBelt.png`; the actual build input is the 3
files `data/images/items/OrdinaryBelt.{palette,tiles,frames}.bin`), and
packing emits `.word` references to `icon_labels()`-named symbols
instead of literal addresses. Those symbols come from
regions.<ver>.txt's `item-icon-data` row -- a single region covering
all 79 real items' icon data at once (they sit in one contiguous ROM
span, see that row's comment), packed by
tools/items/pack_item_icons.py. No ROM address is stored in items.json
or in data/images/items/ -- only in that one region row. Entries with
no real icon (`sIconPath` is null: the dummy record and the all-zero
padding past REAL_ITEM_COUNT) keep pIcon1/pIcon2/pIcon3 as literal
packed integers instead, since there is no label/PNG to name.
"""
import re
import struct
from pathlib import Path

# (json field name, struct format char)
FIELDS: list[tuple[str, str]] = [
    ("nNameTextId", "I"),        # 0x00 -- dialog string id for the display name
    ("pIcon1", "I"),             # 0x04 -- palette pointer, see module docstring
    ("pIcon2", "I"),             # 0x08 -- compressed tile-data pointer, see module docstring
    ("pIcon3", "I"),             # 0x0C -- frame/layout header pointer, see module docstring
    ("nOwlRewardWeight", "I"),   # 0x10 -- owl-mail reward weighting
    ("nUnk14", "I"),             # 0x14 -- unidentified; nonzero gates membership of item-list filter 0xB
    ("dwCategory", "I"),         # 0x18 -- item category id (0x0-0x6, 0x8 used; 0x7 unused; 0xC on the dummy)
    ("nUnk1C", "I"),             # 0x1C -- unidentified
    ("dwUnk20", "I"),            # 0x20 -- flag word, bit 2 tested
    ("nType", "I"),              # 0x24 -- not decoded
    ("nParam", "I"),             # 0x28 -- not decoded
    ("dwUnk2C", "I"),            # 0x2C -- unidentified
    ("dwUnk30", "I"),            # 0x30 -- unidentified
]

FIELD_STRUCT_FORMAT = "<" + "".join(fmt for _, fmt in FIELDS)
RECORD_SIZE = struct.calcsize(FIELD_STRUCT_FORMAT)
assert RECORD_SIZE == 0x34

ITEM_TABLE_ADDR = 0x08060EE4
ITEM_COUNT = 132

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


def pack_record(record: dict) -> bytes:
    values = [record[name] for name, _fmt in FIELDS]
    return struct.pack(FIELD_STRUCT_FORMAT, *values)


# FIELDS split around the 3 icon-pointer fields (index 1..3), so a real
# item's record can be packed as head bytes + 3 label words + tail bytes
# instead of one literal blob. See module docstring.
_HEAD_FIELDS = FIELDS[0:1]
_ICON_FIELD_NAMES = tuple(name for name, _fmt in FIELDS[1:4])
_TAIL_FIELDS = FIELDS[4:]

HEAD_STRUCT_FORMAT = "<" + "".join(fmt for _, fmt in _HEAD_FIELDS)
TAIL_STRUCT_FORMAT = "<" + "".join(fmt for _, fmt in _TAIL_FIELDS)


def pack_head(record: dict) -> bytes:
    return struct.pack(HEAD_STRUCT_FORMAT, *(record[name] for name, _fmt in _HEAD_FIELDS))


def pack_tail(record: dict) -> bytes:
    return struct.pack(TAIL_STRUCT_FORMAT, *(record[name] for name, _fmt in _TAIL_FIELDS))


def pack_icons_literal(record: dict) -> bytes:
    """Pack pIcon1/pIcon2/pIcon3 as literal integers, for records with no
    sIconPath (see module docstring)."""
    return struct.pack("<3I", *(record[name] for name in _ICON_FIELD_NAMES))


def icon_slug(name: str) -> str:
    """PascalCase identifier derived from an item's display name, e.g.
    "Chocolate Frogs" -> "ChocolateFrogs". Used for both the extracted
    PNG's filename and the icon_labels() symbol names, so the two stay
    in lockstep without either one being stored anywhere."""
    words = re.findall(r"[A-Za-z0-9]+", name)
    return "".join(word[0].upper() + word[1:] for word in words)


def icon_path(name: str) -> str:
    """sIconPath value for a real item's display name, e.g. "items/ChocolateFrogs.png"."""
    return f"items/{icon_slug(name)}.png"


def icon_labels(path: str) -> tuple[str, str, str]:
    """(palette, tiles, frames) label names for an sIconPath value, matching
    the labels tools/items/pack_item_icons.py emits inside the
    `item-icon-data` region. Derived purely from the path's basename --
    no address is stored in items.json or here, only in
    regions.<ver>.txt's single `item-icon-data` row."""
    slug = Path(path).stem
    return (f"gItemIcon{slug}Palette", f"gItemIcon{slug}Tiles", f"gItemIcon{slug}Frames")


def icon_bin_paths(images_dir, path: str):
    """(palette, tiles, frames) file paths for an sIconPath value, under
    the data/images/items/ directory `images_dir` -- e.g.
    data/images/items/OrdinaryBelt.palette.bin. Each file's own length is
    its data's boundary; no separate offset/length needs to be stored."""
    slug = Path(path).stem
    return tuple(Path(images_dir) / f"{slug}.{kind}.bin" for kind in ("palette", "tiles", "frames"))
