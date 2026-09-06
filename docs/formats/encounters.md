# Encounter roster tables

PROVEN. Read by `SetupBattleRoster` (`0x0800EDD8` US) to populate the enemy
half of the battle roster. Committed as hand-written C in `src/data/` via
`c-file` manifest rows (`random_encounters.c`, `scripted_encounters.c`,
`include/encounters.h`); `just compare` proves byte-exactness for both
versions.

## Layouts

`EncounterSlots` (4 bytes): one monster id per enemy slot
(`bSlot0MonsterId`..`bSlot3MonsterId`), `0xFF` = empty slot. Monster ids
index `MonsterTable` (0-68; see `folio_bruti.md`).

Scripted fights: `EncounterSlots[15]` -- one row per fight, indexed
`[fightId * 4 + slot]` where `fightId` is `g_dwCurrentGameModeArg1`.
Used when `g_dwCurrentGameModeArg3 == 0xFF`. No row is fully empty.

| ROM | Address | Extent |
| --- | --- | --- |
| US | `0x0805120C` | 60 bytes, ends at a pointer table |
| JP | `0x08051138` | 60 bytes, same adjacency |
Random encounters: `RandomEncounter[30]` (48 bytes each) -- 3 kinds x 4
random variants x 4 slots. Indexed
`[slot + variant * 4 + kind * 0x10 + id * 0x30]` where `variant` is a
pre-battle random pick (see Readers), kind/id are
`g_dwCurrentGameModeArg3`/`g_dwCurrentGameModeArg1`:

```
RandomEncounter  { RandomEncounterKind aKinds[3]; }   // 48 B, stride 0x30
RandomEncounterKind { EncounterSlots aVariants[4]; }  // 16 B, stride 0x10
```

| ROM | Address | Extent |
| --- | --- | --- |
| US | `0x08050C6C` | 1440 bytes, ends exactly where the scripted table begins |
| JP | `0x08050B98` | 1440 bytes, same adjacency (`+1440 = 0x08051138`) |

## Readers

Three code paths read the random table; together they define what each
axis means:

- `SpawnOverworldMonsterEncounters` (`0x0802B21C`, room load): loops the
  3 kinds, spawning each kind's count (level-table record offsets
  `0x74`-`0x76`; see `levels.md`). Per spawn it picks a variant with
  `Mt19937RandMax(3)`, takes the weighted pick of that variant's slots
  0-2 (`FUN_0802BAD0`), and stores id/variant/kind on the
  wandering-monster object.
- Touching the monster pushes Battle mode with `(id, variant, kind)`
  (`FUN_0802B58C`); `SetupBattleRoster` reads exactly that cell's 4
  slots as the enemy roster. The variant axis is a pre-battle random
  pick, not a room index.
- `SpawnWanderingMonsterObject` (`0x0802B41C`) renders unanalyzed
  (`g_abMonsterDocLevel <= 2`) monsters as "?" silhouettes.
- Each kind also selects its spawn-terrain collision type
  (`FUN_0802BA0C`, table `0x08065828`).

## Occurrence

- Scripted fights 0-11 trigger from quest-stage-0 room scripts
  (`StartBattle`, opcode `0x2B`); fights 12-13 trigger at later stages
  (fight 12: room 5 Hogwarts Express Baggage Car, stage 2; fight 13:
  room 6 Passenger Car, stage 3). All quest stages 0-34 were scanned in
  every room; decode failures are uniform per-room padding (2 slots),
  not missed data.
- Fight 14 has no room-script trigger in any stage -- its 4-byte
  `StartBattle` pattern (`2B 00 00 00 0E`) occurs nowhere in the ROM,
  so it fires through another path or is unused.
- Random id 27's only user is room 50 (Diagon Alley Test Map 1, a debug
  map); ids 16/23/24/26 are unreferenced by any room. Variant value 30
  means "no encounters": all such rooms have `(0, 0, 0)` counts so the
  table is never indexed.
- Slot 3 is `0xFF` in all 375 rows (360 random + 15 scripted), so
  battles field at most 3 enemies. The code supports 4
  (`SetupBattleRoster` loops all 4 slots; the overworld weighted pick
  scans slots 0-2), but no data uses the fourth slot.

## Notes

- Content is byte-identical between US and JP; only addresses differ.
- Every byte of both spans is a valid monster id or `0xFF` (max id 68 =
  69 species - 1); both spans end at non-table data, fixing the row
  counts (15 / 30) structurally, not by heuristic.
- When `g_dwCurrentGameModeArg3 == 0xFF` and
  `g_dwCurrentGameModeArg1 == 3`, `SetupBattleRoster` bypasses the
  scripted row and hard-codes the Buckbeak/Harry/Hermione trio, so
  scripted row 3 is unreachable through that path.
- First sighting of a rostered monster sets its
  `g_abMonsterDocLevel` byte to 2 (Folio Bruti "seen").
