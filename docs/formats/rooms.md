# Per-room object placement, warp triggers, and switch state

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

This document covers where a room's *default* object/chest/NPC layout
comes from (distinct from the runtime save snapshot of a room already
documented in [`save.md`](save.md)'s "Room-object state") and the
adjacent warp-trigger and switch-state systems parsed from the same
per-room resource blob.

## The room resource blob

**PROVEN**, from disassembly and a scan of all 55 rooms (US). The level
table's offset-`0x50` field (`docs/formats/levels.md`) points to a per-room
blob, parsed by `ParseRoomResourceBlob_candidate` (`0x08005A78`) into a
0x2200-byte RAM buffer (`g_pRoomTableBuffer`, zeroed at the start of every
room load). Types: `include/overworld/room_blob.h`.

```
blob      u16 wSize                 offset of the stage index (= 4 + 8 * wRecordCount, all rooms)
          u16 wRecordCount
          {s16 x, s16 y, u16 entryId, u8 facing, FF} playerEntryPoints[wRecordCount]
pSub      = blob + wSize            stage index
  +0x00   u8  variantCount
  +0x01   u8  stageToVariant[33]    indexed by g_abQuestEventState[0]; every value < variantCount
  +0x22   FF FF
  +0x24   variantCount * 8-byte entries: u16 sub-block offset from blob start, then 6 zero bytes
sub-block
  +0x00   u16 warp table offset     from the sub-block
  +0x02   u16 switch table offset   from the sub-block
  +0x04   u16 flags                 bit 0 is stored to g_wRoomResourceFlags_candidate; set in all 127 sub-blocks
  +0x06   u16 size                  offset of the sub-block's 4-byte trailer (00 00 FF FF)
  +0x08   object table (inline)
table     u8 count, u8 pad (0), u16 offsets[count]; offsets are from the table start;
          padded with FF to (count + 1) slots rounded up to even
```

Entry 0 is the default sub-block; entry `stageToVariant[g_abQuestEventState[0]]`
is the variant sub-block. **Extent proof:** in every room the lowest
sub-block offset equals `wSize + 0x24 + 8 * variantCount`, so the stage
index is followed immediately by the first sub-block.

`ParseRoomResourceBlob_candidate` runs four builders in sequence. Each writes
into the buffer at its cursor; the address it returns is the next builder's
cursor. Runtime tables start with a `u16` count and `u16` offsets from the
table start.

  1. `CopyRoomBlobHeaderRecords_candidate` (`0x08005DD0`) copies the header
     (`wSize`, `wRecordCount`, the 8-byte records) to the buffer start and
     returns the buffer plus `wSize`, the start of the object table. The
     records are the player entry points, see "Player entry points". Its
     second parameter is unused.
  2. `BuildRoomObjectTable_candidate` (`0x0800572C`) builds
     `g_pRoomObjectTable` (`0x03001DF4`) from the sub-block's inline table,
     one column at a time through `BuildRoomObjectColumn_candidate`
     (`0x08005808`). Each column lists its rows; a row is an 8-byte zeroed
     runtime prefix followed by the static record (see "Static per-tile
     object table").
  3. `BuildRoomWarpTriggerTable_candidate` (`0x0800588C`) builds
     `g_pRoomWarpTriggerTable` (`0x03001DF8`), read by the accessors in
     "Warp/trigger tiles". Each column is `{u32 count; 8-byte records}`
     copied by `sub_08005E40`.
  4. `BuildRoomSwitchStateObjectTable_candidate` (`0x08005968`) builds
     `g_pRoomSwitchStateObjectTable` (`0x03001DFC`); chains are copied by
     `sub_08005E84`, see "Room switch-state chains".

**Default prepend.** With flags bit 0 set (always, in the shipped data) the
tables combine both sub-blocks: the object and switch tables get the default
sub-block's entry 0 first, so `count` is the variant's count plus 1 and every
variant index shifts up by one (runtime chain `i + 1` is variant chain `i`;
runtime chain 0 is the default's chain 0). The warp table takes all of the
default's columns first, then the variant's. Without the bit the runtime
tables hold only the variant's entries.

## Object groups and records

**STRUCTURAL MATCH**, confirmed field-by-field via `GetRoomObjectRecordPtr_candidate`'s
consumers. `g_pRoomObjectTable` (RAM `0x03001DF4`) is a two-level offset
table: `table[2+g*2]` (`u16`) gives group `g`'s member table; that table's
`[2+m*2]` gives member `m`'s record offset. A group is a set of objects that
is spawned together; scripts and objects address an object as
`(group, member)`. The code's names for these indices are `(column, row)` and,
in script opcodes, `(tileX, tileY)`; they are not positions.
`RespawnRoomObjectsInRow_candidate(g)` spawns every member of group `g`, and
`RespawnRowAndRunChain(group, chain)` spawns a group and then runs a chain.
Room entry spawns group 0 and, with flags bit 0 set, group 1. Runtime group 0
is the default sub-block's only group; variant group `i` is runtime group
`i + 1`. Groups range from 0 to 47 members. `RespawnRoomObjectAtTile`
(`0x08005B70`) and `GetRoomObjectRecordPtr_candidate` (`0x08005C38`) both do this lookup;
the latter is called by every object-type constructor to fetch its own
record.

A tile record is `{u32 objectPtr; u16 objType; ...static fields...}` --
`objectPtr` (offset `+0`) is written by `RespawnRoomObjectAtTile` after
construction (`SetRoomObjectRecordPtr_candidate` performs the same
write from other call sites); `objType` (offset `+8`, i.e.
`GetRoomObjectRecordPtr_candidate`'s return value) selects a
constructor from `g_apRoomObjectConstructors` (`src/room/room_object_constructors.c`,
US `0x0804C054`, JP `0x0804BF80`; constructors take `(column, row)` and return
the new `Object *`; a 14-entry
function-pointer array, indices 0-13 -- entries beyond 13 fail to parse
as valid pointers, so 14 is the full object-type count). The static
fields after `objType` vary in layout per object type; for type 9 (see
below) they run `+4/+6` (i16 x/y), `+8` (u16 script PC), `+0xa` (kind 0-3;
kind 2 despawns once triggered), `+0xb`-`+0xd` (bytes copied into the object) -- other types read a different, shorter subset of the
same base pointer, so the record's on-disk length varies by which
constructor consumes it (only the objType index at `+8` has a
type-independent meaning).

### Record layouts (blob side, from the record start)

Every record starts with a `u32` object type (1-13; indexes
`g_apRoomObjectConstructors`), then `s16 x`, `s16 y` in pixels. Fields after
that, with the constructors under `src/room/objects/` and the callbacks that
read them. `(respawn_group, chain)` is the operand pair of
`RespawnRowAndRunChain`; a pair of zeros runs nothing. Trailing bytes of `FF`
are padding. Each type has an assembler macro in `asm/room_blob.inc` that takes
these field names: `TileAnimation` (1), `Door` (2), `Switch` (3),
`TriggerZone` (4), `Prop` (5), `Npc` (6), `TriggerRect` (7), `Breakable` (8),
`Chest` (9), `MovePlayer` (10), `TimedHazard` (11), `ContactTrigger` (12) and
`DoorAlt` (13). The field names written `arg_XX`/`unk_XX` are placeholders
where the role is not established. The constructors are named after the roles
below (`SpawnDoorObject`, ..., `SpawnPortraitDoorObject`; see
`g_apRoomObjectConstructors`).

| Type | Size | Role | Fields (offset) |
|---|---|---|---|
| 1 | 12 | room tile animation | `anim_id` (8), `flag` (9) |
| 2, 13 | 16 | door: moves the player to another room through game mode 8. Type 13 is a portrait door, linking each floor with `portrait_room` (31): it enters `portrait_room_passage` (32) first, with the destination as the next game mode argument, and from there leaves directly | `half_width` (8), `half_height` (9) collision box; `exit_param` (A) is the destination's entry id; `destination_room` (B); `chain` (C) runs instead of leaving when nonzero; `require_a_press` (D) |
| 3 | 20 | two-state switch | `variant` (9) selects sprite and trigger kind; `rearm_delay` (A, u16, x30 ticks); `initial_frame` (C); pairs at E/F and 10/11 run on the first and second activation (`on_activate_*`, `on_deactivate_*`) |
| 4 | 20 | trigger zone | `half_width`, `half_height` (8, 9); `rearm_delay` (A, u16, x30 ticks); `trigger_kind` (C): 0 fires once on touch, other values re-arm after `rearm_delay`, 3-5 fire when hit by overworld spell effect 2, 3 or 4 (object type `0xF`, spell index in `wCharacterId`), 2 reacts to type 5 objects; `require_a_press` (D); pair at F/10 |
| 5 | 24 | scripted prop; `kind` (C, 0-82) selects sprite and behavior | `facing` (D); `chain` (14) runs when a spell hits it; others unresolved |
| 6 | 16 | NPC | `sprite` (8, index into `g_aObjectTypeAssets`); `facing` (9, stored halved); `interact_cooldown` (A, u16, x30 ticks); `interact_mode` (C): 0 interactable once, 1 repeatable after the cooldown; pair at D/E runs on interaction (both zero: not interactable) |
| 7 | 20 | trigger zone with explicit edges | `left`, `top`, `right`, `bottom` (8-B); `rearm_delay` (C, u16); `trigger_kind` (E); `require_a_press` (F); pair at 11/12 |
| 8 | 28 | push puzzle reset button: any overworld spell effect (object type `0xF`) presses variant 0, and when the press animation ends the targets are respawned at their record positions. Every use targets pushable props (kind 1 blocks, kind 81 book stacks) | `variant` (8); eight `(group, member)` targets (9-0x18) that are freed and respawned |
| 9 | 16 | chest, see "Chests" below | `flag_id` (8, u16); `kind` (A, 0-3); `reward_id` (B); `chain` (C), `respawn_group` (D) |
| 10 | 16 | Spongify pad: overworld spell effect 5 arms it, then touching it launches the player and followers to the target point | `target_x`, `target_y` (8, A, s16); `variant` (C) |
| 11 | 16 | flame jet that alternates on and off; contact runs the pair | `variant` (C); pair at D/E; off and on periods at 8 and A |
| 12 | 12 | raising platform: the party gathers on it, it lifts them, then runs the pair | pair at 8/9; nonzero `arg_0a` (A) starts it inactive until overworld spell effect 2 hits it |

### Chests

**PROVEN** from `SpawnChestObject`, its touch handler `HandleChestTouch` and
its tick `TickChestObject`.

- `flag_id` is the chest's bit in `g_abOpenedChestFlags` (256 bits, saved with
  the game; see [`save.md`](save.md)). Flag ids are global: a chest that appears
  in several sub-blocks of a room uses the same id in each. A chest whose bit is
  set spawns open (kind 2: hidden) and cannot be opened again. Opening it sets
  the bit.
- `reward_id` uses the reward numbering in `include/game/rewards.h` (items,
  Folio Universitas cards, `0x83` Sickles). When the open animation ends, an id
  up to `0x83` goes to `PlayerReceiveReward`, which plays the receive-item
  action and calls `GrantReward` with a count of 1 (30-60 for Sickles). A
  higher id grants nothing and runs the `(respawn_group, chain)` pair.
- `kind` selects how the chest opens. All kinds use the `Chest` sprite sheet.
  Kind 0 (81 chests) opens when the player presses A against it. Kind 1
  (unused) is chained: overworld spell effect 3 plays its unchaining animation
  and turns it into kind 0. Kind 3 is a Wizard Card Collectors Club
  chest: `(reward_id + 0x79) & 0xFF` is a Folio Universitas page group, and the
  chest opens on A only while that group is unlocked and its
  `g_abQuestEventState[0x14 + group]` flag is clear, otherwise A runs the
  pair. Kind 2 (two chests, both in default group 0) spawns hidden with
  collision off; its animations make it appear from and vanish into sparkles.
  It opens on A, with extra conditions on `g_dwPendingCameraFocusFlag` and the
  player's `bFighterIndex`. **UNCONFIRMED:** what makes it visible; no code or
  script that reveals it has been found.

## Source files

Each room's blob is one assembly source, `asm/room/blobs/<room_name>.s`
(names are the room script directory names), built by one `asm-file` row
(`Room<RR>Blob`) per version. The macros in `asm/room_blob.inc` write the header,
stage index, offset tables and object records; the assembler computes every
offset, count and padding byte, and the sub-block size word. Switch-state
chains are labelled blocks of the `asm/room_script.inc` opcode macros. Every group, route and chain label defines a `<label>_id`
symbol with its runtime number (position in its table, plus 1 for a variant's
groups and chains because the default sub-block's entry 0 comes first), and
operands that name a chain, group or route use it, for example
`GotoIfStoryStageCompare 0, 20, Room10V1Chain3_id, 0, 0, 0`; the opcode macros
call a tile object's operands `group` and `member`. Zero stays literal where it
means "none". Where the US and JP blobs differ, the source uses
`.ifdef VERSION_JP`. The opcode numbers are repeated in `asm/room_script.inc`
from `enum RoomScriptOpcode`.

The type 4 and 7 callbacks and the door callbacks were checked against all
127 sub-blocks: all 117 door records name a valid room and an entry id that
exists in it, and every `(respawn_group, chain)` pair and type 8 target
refers to a group, member and chain that exist.

## Player entry points

**PROVEN** for the lookup. The blob header's records are the room's player
spawn points. `SpawnPlayerObject_candidate` finds the record whose `entryId`
equals `g_abRoomScriptExitParams_candidate[0]` (`sub_08005BE4`) and places the
player at `(x, y)` facing `facing`; with no match it uses a default record
table at US `0x0804C08C`. Doors set the exit parameter before the room
change.

## Waypoint routes

**STRUCTURAL MATCH.** The "warp trigger" table (`g_pRoomWarpTriggerTable`) is a
set of walking routes for NPC objects. A route is a list of
`{s16 x, s16 y, u8 chain}` waypoints (8 bytes each: four padding bytes after
the chain byte, which are `FF`). A route's group counts here are separate from
object groups: the default sub-block has none, and variant route `i` is runtime
route `i`.

- `GetRoomWarpTriggerByte_candidate` (`0x08005CE8`): waypoint count.
- `GetRoomWarpTriggerOffset_candidate` (`0x08005D00`): waypoint `(x, y)`.
- `ApplyRoomWarpTrigger_candidate` (`0x08005D30`): runs the waypoint's chain.

An NPC (type 6) follows a route when a script puts it into an animation
sequence (`StartObjectAnimSequence`): its operands `bArg64` and `bArg65` are
stored in Object `+0x64` (route) and `+0x65` (current waypoint). The sequence
selector picks the walking mode: `sub_08004500` loops through the waypoints,
`sub_08004688` ping-pongs, and `sub_0800483C` walks once and stops. Each runs
the waypoint's chain on arrival and waits the script's delay between waypoints.
All 694 `StartObjectAnimSequence` uses in the variant chains name a route and
waypoint that exist. The ROOM_OBJECT records do not choose a route.

## Room switch-state chains

**STRUCTURAL MATCH, and a second bytecode VM distinct from
`InterpretObjectScript`.** `g_pRoomSwitchStateObjectTable` holds, per
switch-state index, a chain walked by `WalkRoomSwitchStateChain_candidate`
(`0x08005410`) and `ResumeRoomSwitchStateChain_candidate` (`0x080055C0`).
This is the room-script bytecode VM: the interpreter, its byte format,
its opcode table, and the known opcodes (tile-object flag bits, dialog
boxes, music control, chained calls between chains) are documented in
full in [`room_scripts.md`](room_scripts.md) -- not duplicated here.
That VM is reached far more broadly than just switch-state/warp tiles
(room load itself runs chains `0`/`1`), so "switch-state chain" names
where a chain index is *found* here, while `room_scripts.md` owns the
VM that *runs* it.

## Relationship to the object-script bytecode VM

**RESOLVED: separate systems, meeting only incidentally.** Neither the
per-tile object table nor the warp-trigger table stores a pointer into
`InterpretObjectScript`'s opcode format. A chest keeps its flag id in the
Object's `wScriptPc` slot, but no object script runs it. The
room-script VM ([`room_scripts.md`](room_scripts.md)) uses its own,
separate bytecode format. "Scripts that run in each area" is better
described by these two room-local systems than by the per-`Object` VM.

## Further work

- Type 5 fields other than `kind`, `facing` and `chain`, and the meaning of
  each `kind`; type 3's remaining variants; type 10 and 11 fields marked
  without a role above.
- `StartObjectAnimSequence` selectors that share a walking mode (7/10, 8/11,
  9/12, 13) differ in `sub_08003A80` pre-checks that are not documented.
- Cross-check against a live mGBA session for any of the above.

## Bounding boxes / walkable-area limits

Camera scroll limit: the level table's scroll-bound fields (`levels.md`
offsets `0x6C`-`0x72`). *Walkable-area* collision -- the tile-type
geometry, slope table, and the per-type meanings including several
user-verified via live gameplay (Lumos crossings, ice, stairs, etc.) --
is a separate, finer system with its own writeup: see
[`collision.md`](collision.md).
