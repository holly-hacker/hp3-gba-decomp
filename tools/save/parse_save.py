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
    fl  1-bit flag (JSON bool or 0/1 int)
    sz  fixed-length ASCII string
    ab  byte array/blob, size given by its JSON length (hex string or
        list of ints, depending on the field)
    an  nibble array (each element 0-15), size given by list length
    a3  array of 3-bit values (each element 0-7), size given by list
        length

Struct-shaped fields (`partyStats`, `inventoryQuestData`, `tables`) carry
no prefix -- a single type/size doesn't describe them. Fields whose real
meaning isn't identified are named `<prefix>UnknownN`, where N is that
field's 0-based index among its immediate siblings (not a global
counter) -- e.g. the inventory sub-tables nested inside
`inventoryQuestData` are indexed separately from the top-level slot
fields. Each slot's fields are plain named keys on the slot object, in
their on-disk order (JSON object order is preserved end to end); there
is no separate index/name wrapper.

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

def parse_header(raw: bytes) -> dict:
    data = logical_bytes(raw, *HEADER_BLOCKS)
    magic = data[0:8]
    lang_byte = data[8]
    result = {
        "szMagic": magic.decode("ascii", errors="replace"),
        "flLanguageConfigured": bool(lang_byte & 0x80),
        "bLanguageIndex": lang_byte & 0x7F,
        "abUnknown0": data[9:14].hex(),
    }
    if not checksum_ok(data):
        result["wChecksum"] = struct.unpack_from("<H", data, 14)[0]
    return result


def encode_header(h: dict) -> bytes:
    data = bytearray(16)
    data[0:8] = h["szMagic"].encode("ascii")
    data[8] = (0x80 if h["flLanguageConfigured"] else 0) | (h["bLanguageIndex"] & 0x7F)
    data[9:14] = bytes.fromhex(h["abUnknown0"])
    struct.pack_into("<H", data, 14, 0)
    struct.pack_into("<H", data, 14, (-sum16(bytes(data))) & 0xFFFF)
    return bytes(data)


def parse_options(raw: bytes) -> dict:
    data = logical_bytes(raw, *OPTIONS_BLOCKS)
    result = {"abUnknown0": data[0:38].hex()}
    if not checksum_ok(data):
        result["wChecksum"] = struct.unpack_from("<H", data, 38)[0]
    return result


def encode_options(o: dict) -> bytes:
    data = bytearray(40)
    data[0:38] = bytes.fromhex(o["abUnknown0"])
    struct.pack_into("<H", data, 38, 0)
    struct.pack_into("<H", data, 38, (-sum16(bytes(data))) & 0xFFFF)
    return bytes(data)


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
# Save slot: inventory/quest data (0x0802A570)
#
# Fixed 17-byte header (packed in this exact, non-sequential field order),
# then 7 variable-length record tables, one per count in the header
# (index 0's own count byte is packed but not used to drive a table).
# --------------------------------------------------------------------------

INVENTORY_TABLES = [
    # (count_key, record_size)
    ("bCount1", 0x6C),
    ("bCount2", 0x0C),
    ("bCount3", 0x34),
    ("bCount4", 0x0C),
    ("bCount6", 0x04),
    ("bCount7", 0x04),
    ("bCount5", 0x04),
]


def decode_inventory(r: SaveReader) -> dict:
    field_c = r.read_bytes(4).hex()
    field_10 = r.read_bytes(4).hex()
    count0 = r.read_bytes(1)[0]
    count1 = r.read_bytes(1)[0]
    count2 = r.read_bytes(1)[0]
    count3 = r.read_bytes(1)[0]
    count4 = r.read_bytes(1)[0]
    count6 = r.read_bytes(1)[0]
    count7 = r.read_bytes(1)[0]
    count5 = r.read_bytes(1)[0]
    field_9 = r.read_bytes(1)[0]

    counts = {
        "bCount1": count1, "bCount2": count2, "bCount3": count3,
        "bCount4": count4, "bCount6": count6, "bCount7": count7,
        "bCount5": count5,
    }

    tables = {}
    for i, (count_key, rec_size) in enumerate(INVENTORY_TABLES):
        n = counts[count_key]
        entries = [r.read_bytes(rec_size).hex() for _ in range(n)]
        tables[f"unknown{i}"] = {
            "controlledBy": count_key,
            "bRecordSize": rec_size,
            "entries": entries,
        }

    return {
        "abUnknown0": field_c,
        "abUnknown1": field_10,
        "bCount0": count0,
        "bCount1": count1,
        "bCount2": count2,
        "bCount3": count3,
        "bCount4": count4,
        "bCount6": count6,
        "bCount7": count7,
        "bCount5": count5,
        "bUnknown2": field_9,
        "tables": tables,
    }


def encode_inventory(w: SaveWriter, inv: dict):
    w.write_bytes(bytes.fromhex(inv["abUnknown0"]))
    w.write_bytes(bytes.fromhex(inv["abUnknown1"]))
    w.write_bytes(bytes([inv["bCount0"]]))
    w.write_bytes(bytes([inv["bCount1"]]))
    w.write_bytes(bytes([inv["bCount2"]]))
    w.write_bytes(bytes([inv["bCount3"]]))
    w.write_bytes(bytes([inv["bCount4"]]))
    w.write_bytes(bytes([inv["bCount6"]]))
    w.write_bytes(bytes([inv["bCount7"]]))
    w.write_bytes(bytes([inv["bCount5"]]))
    w.write_bytes(bytes([inv["bUnknown2"]]))
    for i in range(len(INVENTORY_TABLES)):
        table = inv["tables"][f"unknown{i}"]
        for entry in table["entries"]:
            w.write_bytes(bytes.fromhex(entry))


# --------------------------------------------------------------------------
# Save slot: full field sequence (SerializeGameStateToSaveBuffer, 0x08021498)
# --------------------------------------------------------------------------

def decode_slot_stream(payload: bytes) -> dict:
    r = SaveReader(payload)
    slot = {}

    slot["dwMoney"] = struct.unpack("<I", r.read_bytes(4))[0]
    slot["abUnknown1"] = r.read_bytes(4).hex()
    slot["bUnknown2"] = r.read_bytes(1)[0]
    slot["bUnknown3"] = r.read_bytes(1)[0]
    slot["bUnknown4"] = r.read_bytes(1)[0]
    slot["bPartyLeaderDisplayLevel"] = r.read_bytes(1)[0]
    slot["bUnknown5"] = r.read_bytes(1)[0]
    slot["bUnknown6"] = r.read_bytes(1)[0]
    slot["bUnknown7"] = r.read_bytes(1)[0]
    slot["flUnknown0"] = bool(r.read_bit())
    slot["bUnknown8"] = r.read_bytes(1)[0]
    slot["abUnknown9"] = r.read_bytes(152).hex()

    slot["partyStats"] = [decode_party_member(r) for _ in range(PARTY_MEMBER_COUNT)]
    slot["inventoryQuestData"] = decode_inventory(r)

    slot["abUnknown10"] = r.read_bytes(32).hex()
    slot["abUnknown11"] = r.read_bytes(256).hex()

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

    slot["anUnknown12"] = r.read_nibbles(0x33)
    slot["abUnknown13"] = r.read_bytes(7).hex()
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
    w.write_bytes(bytes.fromhex(slot["abUnknown1"]))
    w.write_bytes(bytes([slot["bUnknown2"]]))
    w.write_bytes(bytes([slot["bUnknown3"]]))
    w.write_bytes(bytes([slot["bUnknown4"]]))
    w.write_bytes(bytes([slot["bPartyLeaderDisplayLevel"]]))
    w.write_bytes(bytes([slot["bUnknown5"]]))
    w.write_bytes(bytes([slot["bUnknown6"]]))
    w.write_bytes(bytes([slot["bUnknown7"]]))
    w.write_bit(int(slot["flUnknown0"]))
    w.write_bytes(bytes([slot["bUnknown8"]]))
    w.write_bytes(bytes.fromhex(slot["abUnknown9"]))  # 152 bytes (38 x 4)

    for member in slot["partyStats"]:
        encode_party_member(w, member)

    encode_inventory(w, slot["inventoryQuestData"])

    w.write_bytes(bytes.fromhex(slot["abUnknown10"]))
    w.write_bytes(bytes.fromhex(slot["abUnknown11"]))

    for level in slot["a3FolioBrutiLevels"] + slot["a3BossMonsterLevels"]:
        w.write_bit(level & 1)
        w.write_bit((level >> 1) & 1)
        w.write_bit((level >> 2) & 1)

    w.write_nibbles(slot["anUnknown12"])
    w.write_bytes(bytes.fromhex(slot["abUnknown13"]))
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
