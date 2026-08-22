"""Shared record layout for the 3 per-character level-up stat tables
(Harry/Hermione/Ron). See docs/memory-map/battle.md's "Turn order" ->
level-up writeup for how the table and each field were identified.

12 bytes per record, no padding between fields -- (name, struct format
char) pairs in on-disk order, one record per level (index 0-99; index 0
is unused -- level 1 is a fresh character's starting stats, never read
back out of the table). LevelUpFighter_candidate (0x080151B0) indexes
these 0-based, so displayed "Level N" is table row N-1.
"""
import struct

# (json field name, struct format char)
FIELDS: list[tuple[str, str]] = [
    ("hp_max", "H"),                      # 0x00 u16 -- PROVEN, copied into wHp_max/wHp on level-up
    ("mp_max", "H"),                      # 0x02 u16 -- PROVEN, copied into wMp_max/wMp on level-up
    ("xp_delta", "H"),                    # 0x04 u16 -- PROVEN. LevelUpFighter_candidate overwrites
                                           #   BattleFighter.wRewardXp with this raw value on level-up, and
                                           #   real in-game "XP to next level" displays match the CUMULATIVE
                                           #   sum of this field across rows 0..level, not any single row's
                                           #   value (verified exactly against 3 real characters/levels --
                                           #   see docs/memory-map/battle.md). So this is a per-level delta;
                                           #   whatever sums it into the displayed threshold isn't traced.
    ("speed", "B"),                       # 0x06 u8  -- PROVEN. BattleFighter.bStat_speed (turn-order byte,
                                           #   lower = earlier turn) is set directly from this on level-up.
                                           #   Displayed "agility" = 255 - this value (verified exactly
                                           #   against 3 real characters/levels).
    ("accuracy", "B"),                    # 0x07 u8  -- boundary PROVEN, semantics STRUCTURAL MATCH (copied
                                           #   into BattleFighter.bAccuracy, the same field ResolveMeleeAttack
                                           #   reads as hit chance for monsters).
    ("defense_unused", "B"),              # 0x08 u8  -- PROVEN unused. Copied into
                                           #   bDefenseFactorPercent_notFromMonsterTable by LevelUpFighter_candidate,
                                           #   but immediately overwritten back to 100 by
                                           #   RecomputeBaseStatsFromLevel_candidate (called via
                                           #   ApplyEquipmentStatModifiers_candidate at the end of the same
                                           #   LevelUpFighter_candidate call) -- so this column never actually
                                           #   takes effect; verified against real in-game data (displayed
                                           #   defense is always 100-100=0 pre-equipment, not 100-this).
    ("magic_defense_unused", "B"),        # 0x09 u8  -- same unused-column story as defense_unused, for
                                           #   BattleFighter.bUnk_0x2F.
]
# 0x0A u16: always 0 in every sampled record (0-99), not read by
# LevelUpFighter_candidate at all -- trailing padding, not a real field,
# so it's not stored in JSON at all (see pack_record/unpack_record).

FIELD_STRUCT_FORMAT = "<" + "".join(fmt for _, fmt in FIELDS)
FIELD_SIZE = struct.calcsize(FIELD_STRUCT_FORMAT)
assert FIELD_SIZE == 10

RECORD_SIZE = 12  # on-disk stride; last 2 bytes are the always-0 padding above

LEVEL_COUNT = 100

# Table order in ROM (US): Harry, Ron, Hermione are contiguous, in that
# order -- each table is exactly LEVEL_COUNT * RECORD_SIZE = 1200 bytes,
# confirmed by their addresses landing back-to-back with no gap.
TABLE_ADDR = {
    "Harry": 0x0804FE50,
    "Ron": 0x08050300,
    "Hermione": 0x080507B0,
}


def unpack_record(data: bytes) -> dict:
    assert len(data) == RECORD_SIZE
    pad = data[FIELD_SIZE:]
    assert pad == b"\x00\x00", f"unexpected nonzero level-table padding: {pad!r}"
    values = struct.unpack(FIELD_STRUCT_FORMAT, data[:FIELD_SIZE])
    return {name: value for (name, _fmt), value in zip(FIELDS, values)}


def pack_record(record: dict) -> bytes:
    values = [record[name] for name, _fmt in FIELDS]
    return struct.pack(FIELD_STRUCT_FORMAT, *values) + b"\x00\x00"
