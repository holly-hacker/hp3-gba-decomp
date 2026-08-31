# Level/room table

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED).

Status: the per-room table's location, entry count, stride, and the map
name lookup are **PROVEN**. Most of the 124-byte record is identified
field-by-field. The BG-layer fields (`+0x00`-`+0x3c`, `+0x54`, `+0x5c`)
are **PROVEN**: a two-level block-index-map/block-contents tilemap
format plus a raw uncompressed palette (`+0x58`) were used together to
render real rooms and confirmed tile-for-tile against actual gameplay --
see [`graphics.md`](graphics.md)'s "On-demand per-tile BG streaming"
section for the full format and which level-table layer maps to which
hardware BG register. A Ghidra structure type, `RoomTableEntry`, is
applied as `g_pRoomTable[55]` at the table's address with every field
named and commented per the layout below.

## The table

Table base is US `0x08063C8C` (`g_pRoomTable`), 55 entries, 0x7C (124)
bytes/entry, PROVEN two ways: (1) ground-truth `build/us/full_disasm.s`
shows the literal `=0x08063C8C` loaded from 5 separate literal-pool
slots inside `InitializeOverworld`, so the base and per-entry `*0x7C`
indexing are real, not a decompiler artifact; (2) the record at index
55 lands exactly on a second, independently-known table
(`g_pRoomQuestMusicOverride`, the quest-override music table below),
which only happens if the stride and count are both right. Indexed by
the current room/map index, i.e. `g_bCurrentRoomId` (the same value
`InitializeOverworld`/`InitializeRoomMode` read out of
`g_bCurrentGameModeArg2`, RAM `0x03003EFC` -- the current game mode's
second argument slot, mirroring `g_dwPendingGameModeArg2`
(`docs/memory-map/game_modes.md`); for `Overworld`/`RoomMode` that
argument is the room index, but the slot's meaning is mode-dependent in
general, so it is not itself a room-id symbol). Consumed by
`InitializeOverworld` (`0x080297A0`) and `InitializeRoomMode`
(`0x08029848`, near-duplicate tail of the same setup).

`0x08063C8C` sits in ordinary ROM rodata, not shared/scratch RAM --
GBA `0x08xxxxxx` is cartridge ROM throughout, and this exact address is
directly and repeatedly used as a fixed literal, not computed from a
runtime base. The bytes immediately before it (`~0x0806307C`-
`0x08063C88`) hold a large, distinct run of 8-byte `(tag, value)` pairs
in tag-constant sub-blocks (tags observed: 1, 2, 4); no code anywhere in
`full_disasm.s` loads a literal address inside that range, so it is not
itself a table walked by an index loop with a fixed base -- most likely
raw/intermediate data belonging to another already-packed resource
whose consumer is unidentified. `0x08063064`-`0x08063070`
immediately before *that* (`g_pBgControlWords`) is real and identified
(see `dwBgControlOverrideA`/`B` below).

## A second, structurally-identical table exists for one cutscene

`docs/formats/graphics.md`'s "Level-table entry layout" section
documents a **separate** 124-byte-stride room table at `0x0806BE38`
(`g_pTimeTurnerCutsceneRoomTable`), reached via a completely different
function, `InitTimeTurnerCutsceneRoom_candidate` (`0x08043114`, ground-
truth-confirmed via its own distinct `=0x0806BE38` literal pool
entries). The two tables are not the same data and not aliases of each
other -- confirmed by identical call-graph shape: `InitTimeTurnerCutsceneRoom_candidate`
calls the exact same field-consumer functions
(`LoadRoomBgTilemap0-3_candidate`, `SetupRoomBgControlAndWindows_candidate`,
`LoadRoomSharedTileset_candidate`, `LoadRoomBgLayer0-3Extra_candidate`)
against `0x0806BE38 + index*0x7C` instead of `0x08063C8C +
index*0x7C`, which is why both were independently described as "the
124-byte level table" by separate investigations.

`InitTimeTurnerCutsceneRoom_candidate` is only ever called with index 0
(scene start) and 1 (the cutscene's mid-point transition) from
`InitializeHarryHermionePortInTimeCutscene`/
`UpdateHarryHermionePortInTimeCutscene` (`0x08042F08`/`0x08042FC0`) --
the Harry/Hermione Time-Turner sequence. So `g_pTimeTurnerCutsceneRoomTable`
is a compact, purpose-built **2-entry** instance of the same
`RoomTableEntry` layout, holding just the two static background
snapshots that cutscene needs, entirely independent of the 55-entry
room index space. It is immediately followed (`+0xF8` = `2*0x7C`) by a
small stride-8 coordinate pair table and, at `+0x78` per entry (matching
`bDefaultMusicModule` below), the cutscene's own two background-music
selections -- the same field layout, reused at small scale.

## Room names, PROVEN

The bottom-of-screen popup shown on entering a room is
**`ShowMapNamePopup`** (US `0x080238D8`), called from the tail of
`InitializeOverworld`/`InitializeRoomMode` whenever `_g_bCurrentRoomId
!= DebugMenuLevelAndQuestSelect`. It computes `stringId =
_g_bCurrentRoomId + 0x54A`, decodes it via `GetDialogText` (see
[`text.md`](text.md)), and spawns a text object at screen position
(0x78, 0x98) -- bottom-center.

The debug map-select menu (`InitializeDebugMapSelectMenu` `0x0800AED8` /
`FUN_0800B120` `0x0800B120`) independently draws all 55 names by looping
`GetDialogText(i + 0x54A)` for `i` in `0..0x36`, confirming both the
`0x54A` base and the exact 55-entry count from a second, independent
code path.

Names are per-`baserom.<ver>.gba` and not committed content (hard rule
2), so they aren't tabulated here -- room `i`'s name is dialog string ID
`0x54A + i` (55 rooms, IDs `0x54A`-`0x580`), decodable with
`decode_dialog_text.py us 0 <id>` (see [`text.md`](text.md)) or via
`tools/collision/dump_collision.py`'s room-name lookup (`just
dump-collision`), which uses the same IDs for its output filenames.

Two things worth recording since they aren't obvious from the IDs alone:
rooms 34/35 both decode to the literal string "Library" (not a decode
error -- two distinct room indices, same displayed name); rooms 50-54
decode to "Diagon Alley Test Map 1"-"5", internal/debug-only names still
present in the shipped string table.

## Record layout (`RoomTableEntry`, offsets within the 124-byte stride)

Field names below match the Ghidra struct applied at `g_pRoomTable`.
Each BG layer (0-3) gets two resource pointers 16 bytes apart, followed
by 8 bytes unread by the traced consumer (`dwUnusedN_8`/`dwUnusedN_c`) --
confirmed by direct disassembly of the consumer function bodies, not
guessed from zero-valued samples.

| Offset | Field | Meaning | Confidence |
|---|---|---|---|
| 0x00/0x10/0x20/0x30 | `dwBgTilemapN` | BG layer N **block-index map**: a `width:u16, height:u16` header (in 4-tile block units) followed by `width*height` block-index entries, decoded via the shared dispatcher (`sub_0801DD88`/`sub_0801DD90`) by `LoadRoomBgTilemapN_candidate`. Each entry selects a block from `dwBgLayerNExtra`, not a final tile -- see [`graphics.md`](graphics.md)'s "On-demand per-tile BG streaming" section for the full two-level format and layer-to-hardware-BG mapping | PROVEN (rendered and confirmed against real gameplay for 4 rooms, all 4 layers) |
| 0x04/0x14/0x24/0x34 | `dwBgLayerNExtra` | BG layer N **block contents**: a `blockCount:u32` header, then `blockCount*32` bytes of 4x4 tile-ID entries (`u16` each) and `blockCount*16` bytes of per-tile palette/flip bytes, decoded by `LoadRoomBgLayerNExtra_candidate`. Tile IDs index into `dwBgTilesetA`/`B` (`+0x54`/`+0x5c`); the palette byte packs `bit0`=hflip, `bit1`=vflip, `bits2-5`=palette bank | PROVEN |
| 0x08-0x0c / 0x18-0x1c / 0x28-0x2c / 0x38-0x3c | `dwUnusedN_8`/`dwUnusedN_c` | Passed to `LoadRoomBgLayerNExtra_candidate` but not read by it | UNCONFIRMED |
| 0x40 | `dwCollisionBehaviorTable` | Collision behavior-table pointer (NOT graphics, despite `LoadRoomSharedTileset_candidate`'s name; decodes into `g_pRoomCollisionBehaviorTable`), see [`collision.md`](collision.md) | PROVEN |
| 0x44 | `dwCollisionTilemap` | Collision tilemap pointer (same caveat), decodes into `g_pRoomCollisionTilemap`; its first u16 is read back as a pattern count into `DAT_03003FB8` | PROVEN |
| 0x48/0x4c | `dwUnused_48`/`dwUnused_4c` | Not read by any traced consumer | UNCONFIRMED |
| 0x50 | `dwRoomResourceBlob` | ROM pointer to a per-room resource blob, parsed by `ParseRoomResourceBlob_candidate` (`0x08005A78`) into the room's default object/chest layout, incl. a quest-stage-gated variant sub-table indexed by `g_abQuestEventState[0]` -- see [`rooms.md`](rooms.md) | STRUCTURAL MATCH |
| 0x54 | `dwBgTilesetA` | BG tileset resource pointer, consumed by `DecodeBgTilesetOffsetTable_candidate` (`0x0803EBA8`). Shared by BG layers 0 and 3 (level-table layer index, see `graphics.md`) | PROVEN |
| 0x58 | `dwPaletteData` | Raw, uncompressed 256-color (16 banks x 16, BGR555) BG palette array, copied verbatim by `SetupRoomBgControlAndWindows_candidate` -- confirmed byte-exact against a live mGBA memory dump. Index 0 is force-overwritten to black (backdrop color) by a second, separate 1-color copy right after | PROVEN |
| 0x5c | `dwBgTilesetB` | Second BG tileset resource pointer, same mechanism. Shared by BG layers 1 and 2 | PROVEN |
| 0x60 | `dwUnused_60` | Passed to `DecodeBgTilesetOffsetTable_candidate` as an argument but never read inside it -- dead | UNCONFIRMED |
| 0x64 | `dwBgControlOverrideA` | Pointer to a byte selector (0-3) consumed by `ApplyRoomBgControlOverride_candidate` (`0x0802B174`) to pick a BG-control-word override; for room ids 5-7 with `g_abQuestEventState[0x1d]==1` it substitutes `g_pBgControlWords` instead. Not a graphics/tileset pointer (corrects an earlier "seasonal overlay" guess: the fallback targets are plain BG-control constants, `0x1d03`/`0x1e09`/`0x1f0a`/`0x1c02`, not compressed resources) | STRUCTURAL MATCH |
| 0x68 | `dwBgControlOverrideB` | Second selector, same mechanism | STRUCTURAL MATCH |
| 0x6c | `wScrollBoundMinX` | Camera/scroll clamp min X. `SetRoomScrollBounds`/`GetRoomScrollBounds` (`0x0800A4E8`/`0x0800A4A4`) read/write offsets 0x6c-0x72 as `(minX,minY)`/`(maxX,maxY)`, falling back to `(0,0)`/`(defaultW,defaultH)` when all four are zero. This is the per-room bounding box | PROVEN |
| 0x6e | `wScrollBoundMinY` | See above | PROVEN |
| 0x70 | `wScrollBoundMaxX` | See above | PROVEN |
| 0x72 | `wScrollBoundMaxY` | See above | PROVEN |
| 0x74 | `bEncounterCountA` | Overworld wandering-monster spawn count, species slot A, passed to `SpawnOverworldMonsterEncounters` (`0x0802B21C`) | STRUCTURAL MATCH |
| 0x75 | `bEncounterCountB` | Species slot B | STRUCTURAL MATCH |
| 0x76 | `bEncounterCountC` | Species slot C | STRUCTURAL MATCH |
| 0x77 | `bEncounterVariant` | Season/variant selector indexing the encounter-species table at `0x08050C6C` inside `SpawnWanderingMonsterObject` (`0x0802B41C`) | STRUCTURAL MATCH |
| 0x78 | `bDefaultMusicModule` | Default Krawall module index for this room, `PlayMusicModule(*(byte*)(...+0x78))`. Answers "which track plays on each map by default" | PROVEN |
| 0x79-0x7b | `bUnused_79`/`7a`/`7b` | Not read by any traced consumer | UNCONFIRMED |

## Quest-state music override table

`g_pRoomQuestMusicOverride`, 55 entries x 4 bytes, immediately following
`g_pRoomTable` (its start address is exactly `g_pRoomTable + 55*0x7C`,
which is how the 55-entry count was cross-checked). Used instead of
`bDefaultMusicModule` when `g_abQuestEventState[0x1a] != 0`:
`PlayMusicModule(g_pRoomQuestMusicOverride[_g_bCurrentRoomId])` (low byte
of each 4-byte entry). The other 3 bytes of each entry are unconfirmed
(could be padding, or unread fields). STRUCTURAL MATCH for the override
mechanism itself, field layout beyond the module-index byte
UNCONFIRMED.

## Room-object / chest state (adjacent system, not part of this table)

Chest/pickup/switch state per room and the default per-room object
layout are documented in [`rooms.md`](rooms.md) -- `ParseRoomResourceBlob_candidate`
(reached from `dwRoomResourceBlob` above) plus the save-state cluster
(`InitializeRoomMode`, `CaptureRoomObjectState`/`RestoreRoomObjectState`/
etc.) This is the "chests spawn" / per-room switch-state half of the
original task; it isn't a field of this 124-byte table.

## Object behavior scripts per room

Per-room scripted behavior (quest triggers, NPC scripts) runs through
the generic object bytecode VM documented in
[`battle_scripts.md`](battle_scripts.md) -- `InterpretObjectScript`
(`0x08018CC0`) driven by each `Object`'s `pfnTick`. Nothing in this
table links a script pointer directly into a room record; script
assignment is per-`Object` (placed by room setup code), not a per-room
table field. See [`rooms.md`](rooms.md) for what is and isn't confirmed
about how room content is placed.

## Not yet located

- No `regions.us.txt` rows are ready for this table yet: several field
  offsets (BG tileset pointers, BG-control-override targets) aren't
  fully walked to genuine termination -- the BG tileset codec
  (`BgTileCodec_candidate`, `0x08006300`) and its per-tile offset-table
  packing aren't decoded yet, see graphics.md -- and multiple `Unused`
  byte ranges aren't confirmed padding vs. simply unread by the traced
  call sites (CLAUDE.md hard rule on region-extent confirmation).
- The `(tag, value)` byte run immediately preceding `g_pRoomTable`
  (`~0x0806307C`-`0x08063C88`) has no identified consumer; worth a
  dynamic (mGBA watchpoint) pass rather than further static guessing.
- JP-ROM table address not yet located or confirmed byte-identical;
  everything above is US-only.
