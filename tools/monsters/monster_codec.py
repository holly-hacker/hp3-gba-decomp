"""Shared record layout for the Folio Bruti monster stat table. See
docs/formats/folio_bruti.md for how each field was identified/confirmed.

24 bytes per record -- (name, struct format char) pairs in on-disk
order, followed by 2 bytes of always-0 trailing padding (not stored in
JSON, see pack_record/unpack_record). Fields whose meaning isn't
confirmed are named unk_<offset>_<type> per the project convention;
offsets are into the 24-byte record.
"""
import struct

# (json field name, struct format char)
FIELDS: list[tuple[str, str]] = [
    ("hp", "H"),                          # 0x00 u16 -- PROVEN, copied into battle HP fields
    ("level", "B"),                       # 0x02 u8  -- PROVEN. BattleFighter+0xE (bLevel): LevelUpFighter_candidate
                                           #   (0x080151B0) increments it (capped 99) and uses it to index a
                                           #   per-character level-up table (g_pHarryLevelTable_candidate etc.),
                                           #   and ResolveSpellAttack (0x08017C24) reads it as the caster's
                                           #   spell power scale term and spell crit-chance term. No monster
                                           #   ever reaches either code path as the acting fighter (every
                                           #   monster's Object is hardwired to the melee-only tick callback,
                                           #   and ResolveMeleeAttack doesn't read this offset), so there's no
                                           #   traced code reader for a monster's own value here -- but it's
                                           #   the same field, at the same offset, filled in the same way as
                                           #   every other confirmed field in this table. See
                                           #   docs/memory-map/battle.md.
    ("speed", "B"),                       # 0x03 u8  -- PROVEN. Turn-order/initiative value, lower = earlier
                                           #   turn. BattleFighter+0x2A (bStat_speed): JitterEnemyTurnOrder_candidate
                                           #   (0x0800E5B8) adds +/-16 random jitter to it (Enemy fighters
                                           #   only, clamped [5,251]); BuildTurnOrder_candidate (0x0800E62C)
                                           #   sorts all fighters ascending by it into the turn queue;
                                           #   AdvanceTurnQueue_candidate (0x0800E890) re-sorts the remaining
                                           #   queue by it each time a fighter's turn resolves, using 0xff as
                                           #   an "already acted this round" sentinel. See
                                           #   docs/memory-map/battle.md. Most common monsters have values
                                           #   clustered near the u8 max (178-254, act late), while fast/
                                           #   dangerous ones (Lupin Werewolf, Draco) have low values and
                                           #   act early.
    ("accuracy", "B"),                    # 0x04 u8  -- PROVEN (both boundary and semantics). Read by
                                           #   ResolveMeleeAttack (0x08017E44) as the attacker's hit-chance
                                           #   stat in a Mt19937RandMax(99) roll -- see
                                           #   docs/memory-map/battle.md.
    ("crit_chance", "B"),                 # 0x05 u8  -- PROVEN. ResolveMeleeAttack (0x08017E44): crit fires
                                           #   when Mt19937RandMax(100) > 100-this (probability this/101),
                                           #   doubling damage and adding the +999 sentinel that
                                           #   ShowBattleMessage's case 5 displays as "Critical hit!" -- see
                                           #   docs/memory-map/battle.md. Monster-only in practice:
                                           #   InitPlayerBattleActor_candidate never populates this field for
                                           #   players, and ResolveMeleeAttack only ever fires with an Enemy
                                           #   attacker anyway. Observed values: 3, 5, 10.
    ("damage_min", "H"),                  # 0x06 u16 -- PROVEN (both boundary and semantics). Fed directly
                                           #   into Mt19937RandRange as the attacker's base damage roll in
                                           #   ResolveMeleeAttack -- see docs/memory-map/battle.md.
    ("damage_max", "H"),                  # 0x08 u16 -- PROVEN, same evidence as 0x06.
    ("effectiveness_flipendo", "B"),      # 0x0A u8  -- PROVEN (sub_0801890C case 0)
    ("effectiveness_incendio", "B"),      # 0x0B u8  -- PROVEN (case 2)
    ("effectiveness_verdimillious", "B"), # 0x0C u8  -- PROVEN (case 1)
    ("effectiveness_wingardium_leviosa", "B"),  # 0x0D u8 -- PROVEN (case 4)
    ("effectiveness_glacius", "B"),       # 0x0E u8  -- PROVEN (case 7)
    ("effectiveness_diffindo", "B"),      # 0x0F u8  -- PROVEN (case 6)
    ("reward_xp", "H"),                   # 0x10 u16 -- PROVEN. ApplyDamageToFighter (0x08017F98) adds
                                           #   this field into g_nXpAccum on a fighter fainting. Live
                                           #   in-game confirmation: 2 Brown Recluse Spiders (index 16,
                                           #   reward_xp=8) awarded exactly 16 XP.
    ("reward_gold", "H"),                 # 0x12 u16 -- PROVEN, same mechanism as reward_xp, into
                                           #   g_nGoldAccum. Live in-game confirmation: 2 Brown Recluse
                                           #   Spiders (reward_gold=42) awarded 105 sickles with Ron's
                                           #   Special Move Wizard Cracker active (a 25% gold-drop
                                           #   multiplier, see docs/memory-map/battle.md) --
                                           #   42*2*1.25 = 105 exactly.
    ("special_effect_chance", "B"),       # 0x14 u8  -- PROVEN. RollMonsterSpecialEffect_candidate
                                           #   (0x08015020), called from TickFighterAttackAnimState_candidate
                                           #   after a monster's normal melee attack (always if this is 100,
                                           #   else only when the attack hits): rolls this% chance
                                           #   (Mt19937RandMax(99) < this, or unconditional at 100) to also
                                           #   fire TriggerBattleEffect(special_effect_id, ...) -- the same
                                           #   effect-script mechanism as player spells/cards. See
                                           #   docs/memory-map/battle.md.
    ("special_effect_id", "B"),           # 0x15 u8  -- PROVEN. Effect script id passed directly to
                                           #   TriggerBattleEffect when special_effect_chance's roll
                                           #   succeeds -- confirmed real entries in
                                           #   tools/battle_scripts/script_names.json's effect table (e.g. id 27
                                           #   = SpecialMonsterPoisonBite, id 60 = SpecialMonsterParalyzingBlow).
                                           #   Small integer (0-61) that clusters by monster family/group,
                                           #   matching shared effects across variants (all Fire Crabs share
                                           #   id 0, all Suits of Armor + Lupin Werewolf share id 60/Paralyze,
                                           #   every venomous spider/snake/toad shares id 27/Poison).
]
# 0x16 u16: always 0 in every real record, not read by battle-init at
# all -- trailing padding, not a real field, so it's not stored in JSON
# (see pack_record/unpack_record).

# Petrificus Totalus and Spongius aren't stored per-monster at all --
# sub_0801890C hardcodes both to always return 100. Not part of this
# record layout; see docs/formats/folio_bruti.md.

FIELD_STRUCT_FORMAT = "<" + "".join(fmt for _, fmt in FIELDS)
FIELD_SIZE = struct.calcsize(FIELD_STRUCT_FORMAT)
assert FIELD_SIZE == 22

RECORD_SIZE = 24  # on-disk stride; last 2 bytes are the always-0 padding above

MONSTER_TABLE_ADDR = 0x0804F410
MONSTER_COUNT = 69

# Only indices 0..FOLIO_BRUTI_COUNT-1 are real, navigable Folio Bruti
# bestiary entries -- PROVEN live via mGBA (see docs/formats/folio_bruti.md
# "The grid boundary"): the D-pad cursor handler explicitly skips index 53
# ("Flesh-eating Slug", itself a boundary marker, not a real monster) and
# nothing past it is reachable through the grid at all. Indices 53..68 are
# MonsterTable rows used for boss/story battle participants (via
# InitMonsterBattleActor) that were never wired into the bestiary.
FOLIO_BRUTI_COUNT = 53

# Dialog string IDs for monster i's Folio Bruti name/description =
# NAME_STRING_ID_BASE/DESC_STRING_ID_BASE + i (see
# DrawFolioBrutiMonsterPanel, sub_08036D60, and docs/formats/folio_bruti.md
# -- the same function's two GetDialogText calls). Used only to fill the
# human-readable "_name"/"_description" JSON annotations below -- not
# themselves part of the 24-byte record, and not written back by pack_record.
NAME_STRING_ID_BASE = 0x4A2
DESC_STRING_ID_BASE = 0x4E6


def unpack_record(data: bytes) -> dict:
    assert len(data) == RECORD_SIZE
    pad = data[FIELD_SIZE:]
    assert pad == b"\x00\x00", f"unexpected nonzero monster-table padding: {pad!r}"
    values = struct.unpack(FIELD_STRUCT_FORMAT, data[:FIELD_SIZE])
    return {name: value for (name, _fmt), value in zip(FIELDS, values)}


def pack_record(record: dict) -> bytes:
    values = [record[name] for name, _fmt in FIELDS]
    return struct.pack(FIELD_STRUCT_FORMAT, *values) + b"\x00\x00"
