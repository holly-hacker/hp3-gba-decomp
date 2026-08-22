#!/usr/bin/env python3
"""Parse/re-encode a Harry Potter and the Prisoner of Azkaban (GBA) .sav file.

Format reference: docs/formats/save.md

The backup is an 8KB (64Kbit) EEPROM: 1024 blocks of 8 bytes each. Each
block is stored byte-reversed in the .sav file relative to the game's own
logical layout. The 1024 blocks are divided into a 16-byte header (blocks
0-1), a 40-byte options block (blocks 2-6), and three 2712-byte save slots
(339 blocks each, starting at blocks 7, 346, 685). Header/options/each slot
all share one checksum convention: sum every little-endian u16 word of the
region (including its own trailing checksum word) mod 0x10000; a valid
region sums to zero. A region's `wChecksum` key is only present in the
JSON when that region is actually invalid (the value is then the bad
stored checksum) -- encoding always recomputes a fresh, correct checksum
from the region's data, so a valid region has nothing worth showing there.

A save slot's 2712 bytes are not a fixed-offset struct: the game builds
each slot as a bitstream (SerializeGameStateToSaveBuffer, 0x08021498),
appending fields with three primitives (PackBytesToSaveStream/
PackBitsToSaveStream/PackNibblesToSaveStream, 0x0803C00C/0x0803C050/
0x0803BAF4) that track a shared byte-cursor + bit-position and realign
differently depending on which primitive runs next. SaveWriter/SaveReader
below reimplement that exact alignment behavior (derived from the three
primitives' disassembly) so a slot can be losslessly decoded to JSON and
re-encoded byte-for-byte.

JSON keys use camelCase with a Hungarian-notation type/size prefix (the
same convention already used for this ROM's globals, e.g. `wHp`,
`bLevel`, `g_abDefaultSaveHeader`):

    b   1-byte scalar (JSON int)
    w   2-byte scalar / u16 (JSON int)
    dw  4-byte scalar / u32 (JSON int)
    fx  4-byte 16.16 fixed-point scalar (JSON float -- dividing/multiplying
        by 65536 is exact in IEEE754 double, so this round-trips losslessly)
    fl  1-bit flag (JSON bool or 0/1 int)
    sz  fixed-length ASCII string
    ab  byte array/blob, size given by its JSON length (hex string or
        list of ints, depending on the field)
    an  nibble array (each element 0-15), size given by list length
    a3  array of 3-bit values (each element 0-7), size given by list
        length

Struct-shaped fields (`partyStats`, `roomObjectState`) carry no prefix --
a single type/size doesn't describe them. Fields whose real meaning
isn't identified are named `<prefix>UnknownN`, where N is that field's
0-based index among its immediate siblings (not a global counter) --
e.g. `roomObjectState`'s own `unknownN` record tables (see below) are
indexed separately from the top-level slot fields, and carry no prefix
since each is a list of fixed-size records, not a scalar/blob. Each
slot's fields are plain named keys on the slot object, in their on-disk
order (JSON object order is preserved end to end); there is no separate
index/name wrapper. A table's entry count is never serialized on its
own -- it's exactly the JSON list's length, recomputed on encode.

Usage:
    parse_save.py decode <in.sav> [out.json]     (default: stdout)
    parse_save.py encode [in.json] <out.sav>     (default: stdin)
"""
import argparse
import json
import struct
import sys

BLOCK_SIZE = 8
TOTAL_BLOCKS = 1024

HEADER_BLOCKS = (0, 2)
OPTIONS_BLOCKS = (2, 5)
SLOT_BLOCKS = 339
SLOT_BYTES = SLOT_BLOCKS * BLOCK_SIZE  # 2712 = 0xA98
SLOT_START_BLOCKS = [7 + i * SLOT_BLOCKS for i in range(3)]

# Trailing digit differs by ROM version (US "HPPOA001", JP "HPPOA004");
# both share the "HPPOA0" prefix.
KNOWN_HEADER_MAGICS = (b"HPPOA001", b"HPPOA004")

PARTY_MEMBER_COUNT = 3
MONSTER_DEX_COUNT = 0x45  # 69
FOLIO_BRUTI_COUNT = 53  # MonsterTable rows actually shown in the bestiary grid


# --------------------------------------------------------------------------
# Block-level (EEPROM byte-reversal) helpers
# --------------------------------------------------------------------------

def logical_bytes(raw: bytes, start_block: int, block_count: int) -> bytes:
    """Undo the per-block byte reversal for a range of blocks."""
    out = bytearray()
    for i in range(block_count):
        off = (start_block + i) * BLOCK_SIZE
        out += raw[off:off + BLOCK_SIZE][::-1]
    return bytes(out)


def physical_bytes(data: bytes) -> bytes:
    """Re-apply the per-block byte reversal (inverse of logical_bytes)."""
    assert len(data) % BLOCK_SIZE == 0
    out = bytearray()
    for i in range(0, len(data), BLOCK_SIZE):
        out += data[i:i + BLOCK_SIZE][::-1]
    return bytes(out)


def sum16(data: bytes) -> int:
    words = struct.unpack(f"<{len(data)//2}H", data)
    return sum(words) & 0xFFFF


def checksum_ok(data: bytes) -> bool:
    return sum16(data) == 0


def bytes_to_bits(data: bytes, count: int):
    """Unpack the low `count` bits of `data`, LSB-first per byte."""
    bits = []
    for byte in data:
        for i in range(8):
            bits.append((byte >> i) & 1)
    return bits[:count]


def bits_to_bytes(bits, byte_count: int) -> bytes:
    """Inverse of bytes_to_bits; unused high bits zero-fill."""
    out = bytearray(byte_count)
    for i, bit in enumerate(bits):
        if bit:
            out[i // 8] |= 1 << (i % 8)
    return bytes(out)


# --------------------------------------------------------------------------
# Save-slot bitstream engine
#
# Mirrors PackBytesToSaveStream (0x0803C00C) / PackBitsToSaveStream
# (0x0803C050) / PackNibblesToSaveStream (0x0803BAF4). SaveReader is the
# exact inverse of SaveWriter (both implemented here; the game's own
# Unpack* functions at 0x0803BDDC/0x0803BE10/0x0803BEE4 are not
# reimplemented -- they consume the same bit sequence a matching call
# shape produces, which is a separate, self-consistent guarantee from
# "this tool's writer and reader invert each other", which is what
# round-tripping through JSON actually needs).
# --------------------------------------------------------------------------

class SaveWriter:
    def __init__(self):
        self.buf = bytearray()
        self.bitpos = 0  # 0 = byte-aligned (no partial byte pending)

    def write_bytes(self, data: bytes):
        if self.bitpos > 0:
            mask = 0xFF >> (8 - self.bitpos)
            self.buf[-1] &= mask
            self.bitpos = 0
        self.buf.extend(data)

    def write_bit(self, bit: int):
        if self.bitpos == 0:
            self.buf.append(0)
        mask = 0xFF >> (8 - self.bitpos) if self.bitpos else 0
        base = self.buf[-1] & mask
        self.buf[-1] = base | ((bit & 1) << self.bitpos)
        self.bitpos += 1
        if self.bitpos > 7:
            self.bitpos = 0

    def write_nibbles(self, values):
        if self.bitpos % 4 != 0:
            mask = 0xFF >> (8 - self.bitpos)
            self.buf[-1] &= mask
            self.bitpos = 4 if self.bitpos < 4 else 0
        for v in values:
            v &= 0xF
            if self.bitpos == 0:
                self.buf.append(v)
                self.bitpos = 4
            else:
                self.buf[-1] = (v << 4) | (self.buf[-1] & 0xF)
                self.bitpos = 0

    def tell(self):
        """Byte offset of the next fully-fresh byte (>= bytes written so far)."""
        return len(self.buf)


class SaveReader:
    def __init__(self, data: bytes):
        self.data = data
        self.pos = 0
        self.bitpos = 0

    def read_bytes(self, n: int) -> bytes:
        if self.bitpos > 0:
            self.pos += 1
            self.bitpos = 0
        out = self.data[self.pos:self.pos + n]
        self.pos += n
        return bytes(out)

    def read_bit(self) -> int:
        byte = self.data[self.pos]
        bit = (byte >> self.bitpos) & 1
        self.bitpos += 1
        if self.bitpos > 7:
            self.bitpos = 0
            self.pos += 1
        return bit

    def read_nibbles(self, n: int):
        if self.bitpos % 4 != 0:
            if self.bitpos < 4:
                self.bitpos = 4
            else:
                self.bitpos = 0
                self.pos += 1
        out = []
        for _ in range(n):
            byte = self.data[self.pos]
            if self.bitpos == 0:
                out.append(byte & 0xF)
                self.bitpos = 4
            else:
                out.append((byte >> 4) & 0xF)
                self.bitpos = 0
                self.pos += 1
        return out

    def tell(self):
        return self.pos + (1 if self.bitpos > 0 else 0)


# --------------------------------------------------------------------------
# Header / options
# --------------------------------------------------------------------------

# SaveHeader offset 0xD (SaveManager_03005598.aHeader[0xd] in Ghidra) is a
# bitmask, confirmed field-by-field against the minigame-select screen
# (FUN_0802d1c8/FUN_0802d148/FUN_0802d08c) and against a real save going
# from the options menu's default to Gamma=High (bit 0x80 -- also read by
# a menu-graphics selector, FUN_0800d1a4). File-level (part of SaveHeader,
# shared across all 3 save slots), unlike the per-slot abQuestEventState --
# also confirmed against a real save where this went from 0x00 to 0x04
# (bit 0x04) at the exact save unlocking the 2nd minigame ("Buckbeak's
# Hippogriff Glide").
HEADER_FLAG_BITS = {
    # bit 0 is confirmed read elsewhere (a menu-background selector,
    # FUN_08036038) but its actual purpose isn't identified.
    "flHeaderBit0": 0x01,
    "flMinigame1Unlocked": 0x02,
    "flMinigame2Unlocked": 0x04,  # confirmed: "Buckbeak's Hippogriff Glide"
    "flMinigame3Unlocked": 0x08,
    "flMinigame4Unlocked": 0x10,
    # bits 5/6 have no known reader at all yet.
    "flHeaderBit5": 0x20,
    "flHeaderBit6": 0x40,
    "flGammaHigh": 0x80,  # options menu: Gamma Normal/High
}


def decode_header_flags(byte_val: int) -> dict:
    return {name: bool(byte_val & bit) for name, bit in HEADER_FLAG_BITS.items()}


def encode_header_flags(h: dict) -> int:
    value = 0
    for name, bit in HEADER_FLAG_BITS.items():
        if h[name]:
            value |= bit
    return value


def parse_header(raw: bytes) -> dict:
    data = logical_bytes(raw, *HEADER_BLOCKS)
    magic = data[0:8]
    lang_byte = data[8]
    result = {
        "szMagic": magic.decode("ascii", errors="replace"),
        "flLanguageConfigured": bool(lang_byte & 0x80),
        # Options menu language selector (0=English US, 1=English UK, ...
        # per CLAUDE.md's 8-language cart list); confirmed against a real
        # save switching to English UK.
        "bLanguageIndex": lang_byte & 0x7F,
        # Options menu: Music/Sound volume (0-10 scale, 0x0a default).
        # Confirmed against real saves with each set to 0 (off).
        "bMusicVolume": data[9],
        "bSoundVolume": data[10],
        "abUnknown0": data[11:13].hex(),
    }
    result.update(decode_header_flags(data[13]))
    if not checksum_ok(data):
        result["wChecksum"] = struct.unpack_from("<H", data, 14)[0]
    return result


def encode_header(h: dict) -> bytes:
    data = bytearray(16)
    data[0:8] = h["szMagic"].encode("ascii")
    data[8] = (0x80 if h["flLanguageConfigured"] else 0) | (h["bLanguageIndex"] & 0x7F)
    data[9] = h["bMusicVolume"]
    data[10] = h["bSoundVolume"]
    data[11:13] = bytes.fromhex(h["abUnknown0"])
    data[13] = encode_header_flags(h)
    struct.pack_into("<H", data, 14, 0)
    struct.pack_into("<H", data, 14, (-sum16(bytes(data))) & 0xFFFF)
    return bytes(data)


# SaveOptions holds minigame high scores (SaveManager+0x10, live RAM copy
# at DAT_030055A8, synced to EEPROM by SyncSaveOptionsIfDirty). Confirmed
# byte-exact against a real save: bytes 4-5 are Wizard Cracker Pop-it's
# Medium-difficulty high score (0->1080 in the sample). The write code
# (FUN_08032534, case 4/6) does `*(u32*)(&DAT_030055A8 + difficulty*4)`,
# and the display/erase-check code (DrawDifficultySelectMenu) reads 3
# consecutive u32s per minigame (`minigameIndex*0xC` outer stride) -- so
# bytes 0-3/4-7/8-11 are very likely Wizard Cracker Pop-it's Easy/Medium/
# Hard scores (a u32 slot per the code, even though only the low 16 bits
# were nonzero in the one sample seen).
#
# Tea Leaf Divination has no high scores at all, so only 3 of the 4
# minigames need storage: 3 x 3 difficulties x 4 bytes = 36 bytes, which
# fits the 38 available data bytes almost exactly. Buckbeak's Hippogriff
# Glide and Riddikulus Boggart Challenge's blocks (offsets 12-23/24-35)
# are confirmed in-game: they immediately follow Wizard Cracker Pop-it's
# block, in minigame-unlock-bit order. Bytes 36-37 are leftover/
# unaccounted for.
OPTIONS_MINIGAME_NAMES = [
    "WizardCrackerPopIt",
    "BuckbeaksHippogriffGlide",
    "RiddikulusBoggartChallenge",
]
OPTIONS_DIFFICULTY_NAMES = ["Easy", "Medium", "Hard"]


def parse_options(raw: bytes) -> dict:
    data = logical_bytes(raw, *OPTIONS_BLOCKS)
    result = {}
    for i, minigame in enumerate(OPTIONS_MINIGAME_NAMES):
        for j, difficulty in enumerate(OPTIONS_DIFFICULTY_NAMES):
            key = f"dw{minigame}{difficulty}HighScore"
            result[key] = struct.unpack_from("<I", data, i * 12 + j * 4)[0]
    result["abUnknown0"] = data[36:38].hex()
    if not checksum_ok(data):
        result["wChecksum"] = struct.unpack_from("<H", data, 38)[0]
    return result


def encode_options(o: dict) -> bytes:
    data = bytearray(40)
    for i, minigame in enumerate(OPTIONS_MINIGAME_NAMES):
        for j, difficulty in enumerate(OPTIONS_DIFFICULTY_NAMES):
            key = f"dw{minigame}{difficulty}HighScore"
            struct.pack_into("<I", data, i * 12 + j * 4, o[key])
    data[36:38] = bytes.fromhex(o["abUnknown0"])
    struct.pack_into("<H", data, 38, 0)
    struct.pack_into("<H", data, 38, (-sum16(bytes(data))) & 0xFFFF)
    return bytes(data)


# --------------------------------------------------------------------------
# Save slot: item quantities + equipped items (g_abItemQuantities, 152 bytes)
#
# Index 0-131 is a flat item-ID-indexed quantity array (0-78 confirmed as
# battle items, per g_pBattleItemTable). Index 132-149 is
# g_abEquippedItemIds, an alias into this same array (not a separate
# allocation): 3 fighters x 6 equip slots, each an item ID or 0xff (empty).
# Fighter order confirmed from a real save (Harry 0 items, Hermione 4,
# Ron 1 -- all distinct counts, unambiguous). Slot order confirmed as
# belt, charm, gloves, boots, hat, cloak (slot 2 = gloves matches Ron's
# one equipped item independently). Trailing 2 bytes are always-zero
# padding so far.
# --------------------------------------------------------------------------

EQUIPPED_FIGHTER_NAMES = ["harry", "hermione", "ron"]
EQUIP_SLOT_NAMES = ["belt", "charm", "gloves", "boots", "hat", "cloak"]
ITEM_QUANTITY_COUNT = 132

# Item index == g_pBattleItemTable[index] (ROM 0x08060ED4, stride 0x34).
# Each entry's +0x10 field is a text-string ID (nNameTextId);
# resolving it through data/text/en_us.json's decoded string table gives
# every one of these names directly -- PROVEN, cross-checked against 6
# real-save-confirmed items (Grand Wiggenweld Potion, Monster Book of
# Monsters, Pocket Watch, and a real save's own listed Belt/Gloves/Boots/
# Cloak), every one landing exactly. Save order == item-ID order == the
# order g_pBattleItemTable itself is laid out in ROM (which in turn
# groups into per-equipment-slot/category runs, each with its own local
# string-ID base -- not one single global offset across the whole table).
# Contiguous from index 0, so a plain list (not an index->name map) is
# all this needs. Confirmed to end here: index 79's nNameTextId reads
# 0 from ROM (decoding to "There you are, Harry!", the table's first
# dialog string) -- not a real item, just zeroed/unrelated memory past
# the table's real end. Matches an in-game observation of item 79 as a
# visibly broken entry (Rat Tonic sprite, wrong name, showing under "all
# items" but no real category). Don't extend this list past index 78
# without new evidence.
ITEM_NAMES = [
    "bOrdinaryBelt",
    "bLeatherBelt",
    "bRope",
    "bSwedishShortsnoutDragonHideBelt",
    "bCommonWelshGreenDragonHideBelt",
    "bRomanianLonghornDragonHideBelt",
    "bChineseFireballDragonHideBelt",
    "bHungarianHorntailDragonHideBelt",
    "bBracelet",
    "bBeads",
    "bPocketWatch",
    "bQuidditchWristGuards",
    "bHeadBand",
    "bEagleFeatherQuill",
    "bCrystalBall",
    "bDragonLiver",
    "bRabbitFurGloves",
    "bRemembrall",
    "bSpellotape",
    "bGoldenSnitch",
    "bMittens",
    "bLeatherGloves",
    "bQuidditchGloves",
    "bPotionsGloves",
    "bSwedishShortsnoutDragonHideGloves",
    "bCommonWelshGreenDragonHideGloves",
    "bRomanianLonghornDragonHideGloves",
    "bChineseFireballDragonHideGloves",
    "bHungarianHorntailDragonHideGloves",
    "bSneakers",
    "bLeatherBoots",
    "bGaloshes",
    "bQuidditchBoots",
    "bSwedishShortsnoutDragonHideBoots",
    "bCommonWelshGreenDragonHideBoots",
    "bRomanianLonghornDragonHideBoots",
    "bChineseFireballDragonHideBoots",
    "bHungarianHorntailDragonHideBoots",
    "bCap",
    "bBlackPointedHat",
    "bRearAdmiralsHat",
    "bQuidditchHelmet",
    "bSwedishShortsnoutDragonHideCap",
    "bCommonWelshGreenDragonHideCap",
    "bRomanianLonghornDragonHideCap",
    "bChineseFireballDragonHideCap",
    "bHungarianHorntailDragonHideCap",
    "bSchoolRobe",
    "bQuidditchRobe",
    "bWinterCloak",
    "bPotionsRobe",
    "bSwedishShortsnoutDragonHideCloak",
    "bCommonWelshGreenDragonHideCloak",
    "bRomanianLonghornDragonHideCloak",
    "bChineseFireballDragonHideCloak",
    "bHungarianHorntailDragonHideCloak",
    "bWiggenweldPotion",
    "bGrandWiggenweldPotion",
    "bPepperupPotion",
    "bGrandPepperupPotion",
    "bAntidoteToCommonPoisons",
    "bAntiParalysisPotion",
    "bRatTonic",
    "bShrivelfig",
    "bDaisyRoots",
    "bRatSpleen",
    "bLeechJuice",
    "bFirebolt",
    "bScabbers",
    "bHedwig",
    "bChocolateFrogs",
    "bCrookshanks",
    "bTimeTurner",
    "bTrevor",
    "bABookPage",
    "bValveHandle",
    "bChocolate",
    "bDeadCaterpillar",
    "bMonsterBookOfMonsters",
]


def _item_quantity_key(i: int) -> str:
    if i < len(ITEM_NAMES):
        return ITEM_NAMES[i]
    return f"bItemQuantity{i:03d}"


def decode_item_quantities(r: SaveReader) -> dict:
    quantities = list(r.read_bytes(ITEM_QUANTITY_COUNT))
    equipped = {}
    for fighter in EQUIPPED_FIGHTER_NAMES:
        slot_ids = r.read_bytes(len(EQUIP_SLOT_NAMES))
        equipped[fighter] = dict(zip(EQUIP_SLOT_NAMES, slot_ids))
    padding = r.read_bytes(2)

    # One field per item, in on-disk order (item ID == save-file position);
    # named ones use their real name, the rest a placeholder keyed by index.
    item_quantities = {_item_quantity_key(i): q for i, q in enumerate(quantities)}

    result = {"itemQuantities": item_quantities, "equippedItems": equipped}
    if any(padding):
        result["abItemQuantitiesPadding"] = padding.hex()
    return result


def encode_item_quantities(w: SaveWriter, item_data: dict):
    item_quantities = item_data["itemQuantities"]
    quantities = [item_quantities[_item_quantity_key(i)] for i in range(ITEM_QUANTITY_COUNT)]
    w.write_bytes(bytes(quantities))
    for fighter in EQUIPPED_FIGHTER_NAMES:
        slots = item_data["equippedItems"][fighter]
        w.write_bytes(bytes(slots[name] for name in EQUIP_SLOT_NAMES))
    if "abItemQuantitiesPadding" in item_data:
        padding = bytes.fromhex(item_data["abItemQuantitiesPadding"])
    else:
        padding = b"\x00\x00"
    w.write_bytes(padding)


# --------------------------------------------------------------------------
# Save slot: party stats (BattleFighter+0x8..+0x23, 28 bytes x 3 members)
# --------------------------------------------------------------------------

def decode_party_member(r: SaveReader) -> dict:
    hp, mp, reward_xp = struct.unpack("<HHH", r.read_bytes(6))
    level = r.read_bytes(1)[0]
    unk_0f = r.read_bytes(1)[0]
    spell_cast_level = list(r.read_bytes(10))
    spell_usage_progress = list(r.read_bytes(10))
    return {
        "wHp": hp,
        "wMp": mp,
        "wXpToNextLevel": reward_xp,
        "bLevel": level,
        "bUnknown0": unk_0f,
        "abSpellCastLevel": spell_cast_level,
        "abSpellUsageProgress": spell_usage_progress,
    }


def encode_party_member(w: SaveWriter, m: dict):
    w.write_bytes(struct.pack("<HHH", m["wHp"], m["wMp"], m["wXpToNextLevel"]))
    w.write_bytes(bytes([m["bLevel"], m["bUnknown0"]]))
    w.write_bytes(bytes(m["abSpellCastLevel"]))
    w.write_bytes(bytes(m["abSpellUsageProgress"]))


# --------------------------------------------------------------------------
# Save slot: room-object state (0x0802A570)
#
# A snapshot of every non-default object active in the player's current
# room (spawned monsters, pickups, switches, chests, etc.), restored when
# the room is re-entered -- not an inventory list, despite the shape of
# the on-disk field order. See docs/formats/save.md's "Room-object state"
# section.
#
# Fixed header (player position/facing, a room switch flag, and one
# entry-count byte per table below, in this exact order), then the 7
# tables' entries themselves, back to back in the same order. Each
# table's count byte is redundant with its JSON list's length, so it's
# not itself represented in JSON.
#
# Each table's record layout was traced byte-for-byte from the two
# symmetric producer/consumer functions: 0x0802A70C (capture, walks the
# live room-object list and picks a table per object per its "kind",
# *(short*)(obj+8)) and 0x0802AB34/0x0802AE64 (restore, respawn each
# tile's default object via 0x08005B70 then overlay these fields). Most
# fields copy a byte/word/dword straight from a fixed offset of the live
# `Object` struct (docs/formats/object_script.md); ones with no
# identified meaning keep that struct's own offset in their name
# (`bUnk_0xNN`/`wUnk_0xNN`/`dwUnk_0xNN`), matching this ROM's existing
# `bUnk_0x0F`-style convention for unnamed fields. A record's leftover,
# always-zero-in-practice padding bytes (confirmed zero because the
# capture side memsets the whole buffer before writing) are round-tripped
# via an `abPadding` key, omitted like `abTailPadding` when all-zero.
# --------------------------------------------------------------------------

# Field spec: (JSON key, byte offset within the record, struct format char).
# Bytes not covered by any field are padding (see `abPadding` above).

SPEC_DEFAULT_KIND = [
    # kind: the fallback/default case (any kind not handled below). The
    # richest record -- full Object state, plus 3 linked sub-objects'
    # tile positions (captured but never restored -- see docs).
    ("dwObjectFlags", 0x00, "I"),   # Object+0xc, capture masks off bit 0x00200000
    ("dwUnk_0x28", 0x04, "I"),
    ("dwUnk_0x80", 0x08, "I"),
    ("wUnk_0x86", 0x0C, "H"),
    ("wWaitTarget_0x8a", 0x0E, "H"),  # Object+0x8a, the WaitFrames/WaitForCounter target (object_script.md)
    ("bSubObjectATileX", 0x10, "B"),  # tile position of Object+0xa0's linked object -- capture-only, never restored
    ("bSubObjectATileY", 0x11, "B"),
    ("bSubObjectBTileX", 0x12, "B"),  # Object+0xa4's linked object -- capture-only
    ("bSubObjectBTileY", 0x13, "B"),
    ("bSubObjectCTileX", 0x14, "B"),  # Object+0xa8's linked object -- capture-only
    ("bSubObjectCTileY", 0x15, "B"),
    ("bFacing", 0x16, "B"),          # Object+0x12
    ("bUnk_0x8d", 0x17, "B"),
    ("bUnk_0x8f", 0x18, "B"),
    ("bUnk_0x8c", 0x19, "B"),
    ("bUnk_0x91", 0x1A, "B"),
    ("bTileX", 0x1B, "B"),           # spawn key, passed to 0x08005B70
    ("bTileY", 0x1C, "B"),
    ("dwUnk_0xd8", 0x20, "I"),
    ("dwUnk_0xdc", 0x24, "I"),
    ("dwUnk_0xe0", 0x28, "I"),
    ("dwUnk_0xe4", 0x2C, "I"),
    ("dwUnk_0xe8", 0x30, "I"),
    ("dwUnk_0x60", 0x40, "I"),
    ("dwUnk_0x64", 0x44, "I"),
    ("dwUnk_0x68", 0x48, "I"),
    ("dwUnk_0x6c", 0x4C, "I"),
    ("dwUnk_0x70", 0x50, "I"),
    ("dwUnk_0x74", 0x54, "I"),
    ("dwUnk_0x78", 0x58, "I"),
    ("wUnk_0x4cHi", 0x5C, "H"),      # Object+0x4c's high 16 bits only (integer/tile part)
    ("wUnk_0x50Hi", 0x5E, "H"),      # Object+0x50's high 16 bits only
    ("wPosXTile", 0x60, "H"),        # Object+0x2c's high 16 bits -- tile-level X, sub-tile part not saved
    ("wPosYTile", 0x62, "H"),        # Object+0x30's high 16 bits
    ("dwUnk_0x3c", 0x64, "I"),
    ("dwUnk_0x40", 0x68, "I"),
]

SPEC_KIND_4_OR_7 = [
    ("bTileX", 0x0, "B"),
    ("bTileY", 0x1, "B"),
    ("bUnk_0x8d", 0x3, "B"),
    ("dwObjectFlags", 0x4, "I"),     # Object+0xc, captured unmasked (unlike the other tables)
    ("dwUnk_0x80", 0x8, "I"),
]

SPEC_KIND_5 = [
    ("bTileX", 0x0, "B"),
    ("bTileY", 0x1, "B"),
    ("bUnk_0x8f", 0x2, "B"),
    ("bUnk_0x16", 0x3, "B"),
    ("bUnk_0x67", 0x4, "B"),
    ("bUnk_0x60", 0x5, "B"),
    ("wUnk_0x86", 0x6, "H"),
    ("dwObjectFlags", 0x8, "I"),     # Object+0xc, masked off bit 0x00200000
    ("dwUnk_0xd8", 0xC, "I"),
    ("dwUnk_0xdc", 0x10, "I"),
    ("dwUnk_0xe0", 0x14, "I"),
    ("dwUnk_0xe4", 0x18, "I"),
    ("dwUnk_0xe8", 0x1C, "I"),
    ("wPosXTile", 0x20, "H"),        # Object+0x2e (high half of current X) -- tile-level only
    ("wPosYTile", 0x22, "H"),        # Object+0x32
    ("dwUnk_0x3c", 0x24, "I"),
    ("dwUnk_0x40", 0x28, "I"),
    ("dwUnk_0x44", 0x2C, "I"),
    ("dwUnk_0x48", 0x30, "I"),
]

SPEC_FLOOR_ITEM = [
    # kind 1. The two dwords aren't Object fields at all: on restore, the
    # respawned object's own (tile-level) position is used to look up an
    # entry in a separate, static per-map item-drop table (0x08020504),
    # and these two dwords overwrite that table entry -- i.e. this
    # refreshes persistent floor-item state keyed by tile position, not
    # the spawned object itself.
    ("bTileX", 0x0, "B"),
    ("bTileY", 0x1, "B"),
    ("dwItemTableField0", 0x4, "I"),
    ("dwItemTableField1", 0x8, "I"),
]

SPEC_KIND_5_SWITCH = [
    # kind 5, sub-kind '3' (Object+0x61 == ASCII '3') -- a per-object
    # toggle, structurally the same idea as the single-instance
    # `bSwitchState` room switch above but with up to 32 independent
    # instances per room. `bTriggered` is encoded inverted: stored as
    # NOT(bit 0x4 of Object+0xc); a stored `1` makes restore call
    # 0x08046CA4, which plays a "consumed/vanish" animation and clears
    # that same bit -- i.e. `1` means "already triggered, redisplay as such".
    ("bTileX", 0x0, "B"),
    ("bTileY", 0x1, "B"),
    ("bTriggered", 0x2, "B"),
]

SPEC_PICKUP_MARKER = [
    # kind 0xB. `bUnk_0x80` round-trips with a +1 offset applied only on
    # restore (Object+0x80 becomes this value + 1); captured verbatim
    # (Object+0x80's raw low byte) on save. `bUnk_0x8f`, when it equals
    # `8` on restore, triggers an item-grant popup (0x08044A94).
    ("bTileX", 0x0, "B"),
    ("bTileY", 0x1, "B"),
    ("bUnk_0x80", 0x2, "B"),
    ("bUnk_0x8f", 0x3, "B"),
]

SPEC_PRESENCE_MARKER = [
    # kinds 2, 8, 10 unconditionally, plus kind 5/6 under specific
    # status-bit conditions (see docs/formats/save.md). Just a tile
    # position -- restore only respawns the tile's default object, no
    # further state applied.
    ("bTileX", 0x0, "B"),
    ("bTileY", 0x1, "B"),
]

ROOM_OBJECT_TABLES = [
    # (JSON key, record size, field spec) -- order matches the on-disk
    # count/table order.
    ("defaultKindObjects", 0x6C, SPEC_DEFAULT_KIND),
    ("kind4Or7Objects", 0x0C, SPEC_KIND_4_OR_7),
    ("kind5Objects", 0x34, SPEC_KIND_5),
    ("floorItemStates", 0x0C, SPEC_FLOOR_ITEM),
    ("kind5SwitchObjects", 0x04, SPEC_KIND_5_SWITCH),
    ("pickupMarkers", 0x04, SPEC_PICKUP_MARKER),
    ("presenceMarkers", 0x04, SPEC_PRESENCE_MARKER),
]

_RECORD_FMT_SIZE = {"B": 1, "H": 2, "I": 4}


def _record_padding_ranges(spec, record_size):
    """Byte ranges of `record_size` not covered by any field in `spec`."""
    covered = bytearray(record_size)
    for _, offset, fmt in spec:
        size = _RECORD_FMT_SIZE[fmt]
        for i in range(offset, offset + size):
            covered[i] = 1
    ranges = []
    i = 0
    while i < record_size:
        if not covered[i]:
            start = i
            while i < record_size and not covered[i]:
                i += 1
            ranges.append((start, i - start))
        else:
            i += 1
    return ranges


def decode_record(data: bytes, spec, record_size: int) -> dict:
    result = {}
    for name, offset, fmt in spec:
        result[name] = struct.unpack_from("<" + fmt, data, offset)[0]
    padding = b"".join(data[o:o + n] for o, n in _record_padding_ranges(spec, record_size))
    if any(padding):
        result["abPadding"] = padding.hex()
    return result


def encode_record(rec: dict, spec, record_size: int) -> bytes:
    data = bytearray(record_size)  # padding bytes default to 0 and are left alone below
    for name, offset, fmt in spec:
        struct.pack_into("<" + fmt, data, offset, rec[name])
    if "abPadding" in rec:
        padding = bytes.fromhex(rec["abPadding"])
        pos = 0
        for offset, length in _record_padding_ranges(spec, record_size):
            data[offset:offset + length] = padding[pos:pos + length]
            pos += length
    return bytes(data)


FIXED_POINT_SHIFT = 65536.0  # 16.16 fixed point; division/multiplication by a
                              # power of 2 is exact in IEEE754 double, so this
                              # round-trips losslessly.


def decode_room_object_state(r: SaveReader) -> dict:
    pos_x = struct.unpack("<i", r.read_bytes(4))[0] / FIXED_POINT_SHIFT
    pos_y = struct.unpack("<i", r.read_bytes(4))[0] / FIXED_POINT_SHIFT
    facing = r.read_bytes(1)[0]
    counts = [r.read_bytes(1)[0] for _ in ROOM_OBJECT_TABLES]
    switch_state = r.read_bytes(1)[0]

    result = {
        "fxPlayerPosX": pos_x,
        "fxPlayerPosY": pos_y,
        "bPlayerFacing": facing,
        "bSwitchState": switch_state,
    }
    for (key, rec_size, spec), count in zip(ROOM_OBJECT_TABLES, counts):
        result[key] = [decode_record(r.read_bytes(rec_size), spec, rec_size)
                        for _ in range(count)]
    return result


def encode_room_object_state(w: SaveWriter, state: dict):
    w.write_bytes(struct.pack("<i", round(state["fxPlayerPosX"] * FIXED_POINT_SHIFT)))
    w.write_bytes(struct.pack("<i", round(state["fxPlayerPosY"] * FIXED_POINT_SHIFT)))
    w.write_bytes(bytes([state["bPlayerFacing"]]))
    for key, _, _ in ROOM_OBJECT_TABLES:
        w.write_bytes(bytes([len(state[key])]))
    w.write_bytes(bytes([state["bSwitchState"]]))
    for key, rec_size, spec in ROOM_OBJECT_TABLES:
        for entry in state[key]:
            w.write_bytes(encode_record(entry, spec, rec_size))


# --------------------------------------------------------------------------
# Save slot: full field sequence (SerializeGameStateToSaveBuffer, 0x08021498)
# --------------------------------------------------------------------------

def decode_slot_stream(payload: bytes) -> dict:
    r = SaveReader(payload)
    slot = {}

    slot["dwMoney"] = struct.unpack("<I", r.read_bytes(4))[0]
    # Playtime, one byte each: hours, minutes, seconds, frames. The 4th
    # byte stays 0-28 across 26 real samples -- well under a 50/60fps
    # rollover, consistent with a sub-second frame counter, though no
    # direct incrementer was found in the disassembly (likely accessed
    # via computed offset, not a literal address Ghidra's xrefs catch).
    slot["bPlaytimeHours"] = r.read_bytes(1)[0]
    slot["bPlaytimeMinutes"] = r.read_bytes(1)[0]
    slot["bPlaytimeSeconds"] = r.read_bytes(1)[0]
    slot["bPlaytimeFrames"] = r.read_bytes(1)[0]
    slot["bUnknown2"] = r.read_bytes(1)[0]
    # bit0 clear makes the slot unrecognized (invalid); bit1 set loads to
    # the start of the game. Other bits: no observed effect.
    slot["bSaveFlags"] = r.read_bytes(1)[0]
    # Index into the main-menu current-objective string table (Ghidra:
    # g_bMainMenuObjectiveIndex, 0x030027b9) -- the same live byte as
    # abQuestEventState[25] below, serialized twice.
    slot["bMainMenuObjectiveIndex"] = r.read_bytes(1)[0]
    slot["bPartyLeaderDisplayLevel"] = r.read_bytes(1)[0]
    # Overworld follower sprite per party slot -- observed values: 3 =
    # Harry (Lumos, headless -- likely an overlay), 4 = Harry (GBC),
    # 5 = Harry, 7 = Ron, 8 = Buckbeak; 9 is out of bounds (severe
    # graphical glitches, crashes).
    slot["bOverworldSprite0"] = r.read_bytes(1)[0]
    slot["bOverworldSprite1"] = r.read_bytes(1)[0]
    slot["bOverworldSprite2"] = r.read_bytes(1)[0]
    # Disables overworld random encounters (bosses excepted).
    slot["flOverworldMonstersDisabled"] = bool(r.read_bit())
    # Currently-selected spell in the overworld.
    slot["bSelectedOverworldSpell"] = r.read_bytes(1)[0]
    slot.update(decode_item_quantities(r))

    slot["partyStats"] = [decode_party_member(r) for _ in range(PARTY_MEMBER_COUNT)]
    slot["roomObjectState"] = decode_room_object_state(r)

    slot["abUnknown10"] = r.read_bytes(32).hex()
    # Ghidra: g_abQuestEventState (0x030027a0). Index 25 = bMainMenuObjectiveIndex
    # above. Persistent global state, not per-room (confirmed unchanged
    # across a real room-to-room crossing). Indices ~224-254 are
    # flags/counters that reset to 0 together at a specific story
    # checkpoint. See docs/formats/save.md for the per-index evidence.
    slot["abQuestEventState"] = list(r.read_bytes(256))

    monster_dex = []
    for _ in range(MONSTER_DEX_COUNT):
        b0 = r.read_bit()
        b1 = r.read_bit()
        b2 = r.read_bit()
        monster_dex.append(b0 | (b1 << 1) | (b2 << 2))
    # MonsterTable's first FOLIO_BRUTI_COUNT (53) rows are the real,
    # in-game-visible Folio Bruti bestiary entries; the remaining 16
    # (indices 53-68) are boss/story encounters that share the same
    # table but are never reachable through the bestiary UI (see
    # docs/formats/folio_bruti.md, "The grid boundary"). Each entry is
    # a 3-bit value.
    slot["a3FolioBrutiLevels"] = monster_dex[:FOLIO_BRUTI_COUNT]
    slot["a3BossMonsterLevels"] = monster_dex[FOLIO_BRUTI_COUNT:]

    # Folio Universitas (Harry's card collection) card counts (one
    # nibble per card; only cards received at least once are shown
    # in-game) and a parallel 51-bit unlocked/seen flag per card (7
    # bytes storage, LSB-first; all-unlocked = ffffffffffff07).
    slot["anFolioUniversitasCounts"] = r.read_nibbles(0x33)
    slot["a1FolioUniversitasUnlocked"] = bytes_to_bits(r.read_bytes(7), 51)
    slot["abUnknown14"] = r.read_bytes(7).hex()
    slot["anUnknown15"] = r.read_nibbles(4)
    slot["abUnknown16"] = r.read_bytes(3).hex()
    slot["abUnknown17"] = r.read_bytes(6).hex()
    slot["abUnknown18"] = r.read_bytes(2).hex()
    slot["abUnknown19"] = r.read_bytes(2).hex()

    stream_end = r.tell()
    # Bytes between the end of the known pack-call sequence and the
    # trailing checksum are never touched by any pack call -- whatever
    # was already in the heap slot buffer at save time (stale content
    # from a previous load). Captured verbatim for exact round-trip;
    # omitted when it's all zero (the common case), since encoding
    # defaults a missing tail to zero-fill.
    tail_padding = payload[stream_end:len(payload) - 2]
    if any(tail_padding):
        slot["abTailPadding"] = tail_padding.hex()
    if not checksum_ok(payload):
        slot["wChecksum"] = struct.unpack_from("<H", payload, len(payload) - 2)[0]

    return slot


def encode_slot_stream(slot: dict) -> bytes:
    w = SaveWriter()

    w.write_bytes(struct.pack("<I", slot["dwMoney"]))
    w.write_bytes(bytes([slot["bPlaytimeHours"]]))
    w.write_bytes(bytes([slot["bPlaytimeMinutes"]]))
    w.write_bytes(bytes([slot["bPlaytimeSeconds"]]))
    w.write_bytes(bytes([slot["bPlaytimeFrames"]]))
    w.write_bytes(bytes([slot["bUnknown2"]]))
    w.write_bytes(bytes([slot["bSaveFlags"]]))
    w.write_bytes(bytes([slot["bMainMenuObjectiveIndex"]]))
    w.write_bytes(bytes([slot["bPartyLeaderDisplayLevel"]]))
    w.write_bytes(bytes([slot["bOverworldSprite0"]]))
    w.write_bytes(bytes([slot["bOverworldSprite1"]]))
    w.write_bytes(bytes([slot["bOverworldSprite2"]]))
    w.write_bit(int(slot["flOverworldMonstersDisabled"]))
    w.write_bytes(bytes([slot["bSelectedOverworldSpell"]]))
    encode_item_quantities(w, slot)

    for member in slot["partyStats"]:
        encode_party_member(w, member)

    encode_room_object_state(w, slot["roomObjectState"])

    w.write_bytes(bytes.fromhex(slot["abUnknown10"]))
    w.write_bytes(bytes(slot["abQuestEventState"]))

    for level in slot["a3FolioBrutiLevels"] + slot["a3BossMonsterLevels"]:
        w.write_bit(level & 1)
        w.write_bit((level >> 1) & 1)
        w.write_bit((level >> 2) & 1)

    w.write_nibbles(slot["anFolioUniversitasCounts"])
    w.write_bytes(bits_to_bytes(slot["a1FolioUniversitasUnlocked"], 7))
    w.write_bytes(bytes.fromhex(slot["abUnknown14"]))
    w.write_nibbles(slot["anUnknown15"])
    w.write_bytes(bytes.fromhex(slot["abUnknown16"]))
    w.write_bytes(bytes.fromhex(slot["abUnknown17"]))
    w.write_bytes(bytes.fromhex(slot["abUnknown18"]))
    w.write_bytes(bytes.fromhex(slot["abUnknown19"]))

    payload = bytearray(w.buf)
    if "abTailPadding" in slot:
        payload.extend(bytes.fromhex(slot["abTailPadding"]))
    else:
        payload.extend(b"\x00" * (SLOT_BYTES - 2 - len(payload)))
    if len(payload) != SLOT_BYTES - 2:
        raise ValueError(
            f"encoded slot body is {len(payload)} bytes, expected {SLOT_BYTES - 2}"
        )
    payload.extend(b"\x00\x00")  # checksum placeholder
    struct.pack_into("<H", payload, SLOT_BYTES - 2, (-sum16(bytes(payload))) & 0xFFFF)
    return bytes(payload)


def parse_slot(raw: bytes, slot_index: int) -> dict:
    start = SLOT_START_BLOCKS[slot_index]
    data = logical_bytes(raw, start, SLOT_BLOCKS)
    if not checksum_ok(data):
        # An invalid slot (e.g. erased/all-0xFF EEPROM) has no reason to
        # follow the field-length assumptions the structured decode makes
        # (record counts, etc.) -- same as the game's own ValidateSaveSlot,
        # which never trusts a slot's content past its checksum. Keep the
        # raw bytes so the file can still round-trip exactly.
        return {
            "wChecksum": struct.unpack_from("<H", data, len(data) - 2)[0],
            "abRaw": data.hex(),
        }
    return decode_slot_stream(data)


# --------------------------------------------------------------------------
# Whole-file parse / encode
# --------------------------------------------------------------------------

def parse(raw: bytes) -> dict:
    if len(raw) != TOTAL_BLOCKS * BLOCK_SIZE:
        raise ValueError(
            f"expected {TOTAL_BLOCKS * BLOCK_SIZE}-byte 8KB EEPROM save, "
            f"got {len(raw)} bytes"
        )
    return {
        "header": parse_header(raw),
        "options": parse_options(raw),
        "slots": [parse_slot(raw, i) for i in range(3)],
    }


def encode(save: dict) -> bytes:
    raw = bytearray(TOTAL_BLOCKS * BLOCK_SIZE)

    def place(start_block, block_count, logical_data):
        phys = physical_bytes(logical_data)
        off = start_block * BLOCK_SIZE
        raw[off:off + len(phys)] = phys

    place(*HEADER_BLOCKS, encode_header(save["header"]))
    place(*OPTIONS_BLOCKS, encode_options(save["options"]))
    for i, slot in enumerate(save["slots"]):
        if "abRaw" in slot:
            place(SLOT_START_BLOCKS[i], SLOT_BLOCKS, bytes.fromhex(slot["abRaw"]))
        else:
            place(SLOT_START_BLOCKS[i], SLOT_BLOCKS, encode_slot_stream(slot))

    return bytes(raw)


# --------------------------------------------------------------------------
# CLI
# --------------------------------------------------------------------------

def _status_line(label, region):
    bad = "wChecksum" in region
    return f"{label}: {'BAD (checksum 0x%04x)' % region['wChecksum'] if bad else 'OK'}"


def cmd_decode(args):
    with open(args.sav_path, "rb") as f:
        raw = f.read()
    result = parse(raw)

    text = json.dumps(result, indent=2)
    if args.json_path:
        with open(args.json_path, "w") as f:
            f.write(text)
        print(f"wrote {args.json_path}", file=sys.stderr)
    else:
        sys.stdout.write(text + "\n")

    print(_status_line("header", result["header"]), file=sys.stderr)
    print(_status_line("options", result["options"]), file=sys.stderr)
    ok = "wChecksum" not in result["header"] and "wChecksum" not in result["options"]
    for i, s in enumerate(result["slots"]):
        print(_status_line(f"slot {i}", s), file=sys.stderr)
        ok = ok and "wChecksum" not in s
    if not ok:
        sys.exit(1)


def cmd_encode(args):
    if args.json_path:
        with open(args.json_path) as f:
            save = json.load(f)
    else:
        save = json.load(sys.stdin)
    raw = encode(save)
    with open(args.sav_path, "wb") as f:
        f.write(raw)
    print(f"wrote {args.sav_path} ({len(raw)} bytes)", file=sys.stderr)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                  formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)

    p_decode = sub.add_parser("decode", help="parse a .sav into JSON")
    p_decode.add_argument("sav_path")
    p_decode.add_argument("json_path", nargs="?", default=None,
                           help="default: write JSON to stdout")
    p_decode.set_defaults(func=cmd_decode)

    p_encode = sub.add_parser("encode", help="re-encode JSON into a .sav")
    p_encode.add_argument("json_path", nargs="?", default=None,
                           help="default: read JSON from stdin")
    p_encode.add_argument("sav_path")
    p_encode.set_defaults(func=cmd_encode)

    args = ap.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
