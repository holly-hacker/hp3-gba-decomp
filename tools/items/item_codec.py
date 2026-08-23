"""Shared record layout for the item/equipment table
(g_pItemTable). See docs/formats/save.md's "Item quantities and
equipment" section for how the table's address/stride/count and each
field were identified.

52 bytes per record, all fields 4-byte little-endian, in on-disk order.
Fields whose meaning isn't confirmed keep the project's Ghidra-matching
unk names (nUnk14, nUnk1C, dwUnk20, dwUnk2C, dwUnk30) rather than an
offset-derived placeholder, since those are the actual database names.

pIcon1/pIcon2/pIcon3 are stored as raw pointer integers only --
extracting the actual icon/sprite image assets those pointers reference
is future work, not done by this codec.
"""
import struct

# (json field name, struct format char)
FIELDS: list[tuple[str, str]] = [
    ("nNameTextId", "I"),        # 0x00 -- dialog string id for the display name
    ("pIcon1", "I"),             # 0x04 -- icon/sprite pointer (raw value only, see module docstring)
    ("pIcon2", "I"),             # 0x08 -- icon/sprite pointer (raw value only, see module docstring)
    ("pIcon3", "I"),             # 0x0C -- icon/sprite pointer (raw value only, see module docstring)
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
