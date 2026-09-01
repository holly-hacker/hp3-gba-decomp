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

**PROVEN**, from ground-truth disassembly (not just decompiler output).
The level table's offset-`0x50` field (`docs/formats/levels.md`) points
to a per-room blob, parsed by `ParseRoomResourceBlob_candidate`
(`0x08005A78`) into a shared 0x2200-byte RAM scratch buffer (zeroed at
the start of every room load):

- `u16` at blob+0 is a self-relative offset to a sub-header (`pSub`).
- `pSub+1` starts a per-quest-stage array of variant-index bytes,
  indexed by `g_abQuestEventState[0]` (the story-stage byte, see
  [`save.md`](save.md)).
- `pSub` itself is an array of 8-byte variant entries; entry N's `+0x24`
  field is a `u16` self-relative offset (from the blob base) to that
  variant's resolved sub-block. Entry 0 (`pSub+0x24`) is always the
  "default" sub-block; the quest-stage-selected entry is the "variant"
  sub-block.
- Four builders run in sequence, each writing into the *same* scratch
  buffer via bump allocation -- the pointer one builder returns is the
  next builder's write cursor:
  1. `CopyRoomBlobHeaderRecords_candidate` (`0x08005DD0`) copies a
     count-prefixed array of 8-byte `{u32,u32}` records straight from
     the blob's own header region. Purpose of these records is
     **UNCONFIRMED** -- no consumer is known.
  2. `BuildRoomWarpTriggerTable_candidate` (`0x0800572C`) builds
     `g_pRoomWarpTriggerTable` (RAM `0x03001DF8`) -- see "Warp/trigger
     tiles" below.
  3. A third builder (`0x0800588C`) builds a table that is **never
     read** anywhere in the ROM (no xrefs to its output) -- dead code
     or an unused feature; not pursued further.
  4. `BuildRoomSwitchStateObjectTable_candidate` (`0x08005968`) builds
     `g_pRoomSwitchStateObjectTable` (RAM `0x03001DFC`) -- see "Room
     switch-state chains" below.

## Static per-tile object table

**STRUCTURAL MATCH**, confirmed field-by-field via `GetRoomObjectRecordPtr_candidate`'s
consumers. `g_pRoomObjectTable` (RAM `0x03001DF4`) is a 2D
column-then-row offset table: `table[2+x*2]` (`u16`) gives a column's
row-table offset; that column's `[2+y*2]` gives the tile's record
offset. `RespawnRoomObjectAtTile` (`0x08005B70`) and
`GetRoomObjectRecordPtr_candidate` (`0x08005C38`) both do this lookup;
the latter is called by every object-type constructor to fetch its own
record.

A tile record is `{u32 objectPtr; u16 objType; ...static fields...}` --
`objectPtr` (offset `+0`) is written by `RespawnRoomObjectAtTile` after
construction (`SetRoomObjectRecordPtr_candidate` performs the same
write from other call sites); `objType` (offset `+8`, i.e.
`GetRoomObjectRecordPtr_candidate`'s return value) selects a
constructor from `g_apRoomObjectConstructors` (`0x0804C054`, a 14-entry
function-pointer array, indices 0-13 -- entries beyond 13 fail to parse
as valid pointers, so 14 is the full object-type count). The static
fields after `objType` vary in layout per object type; for type 9 (see
below) they run `+4/+6` (i16 x/y), `+8` (u16 script PC), `+0xa`-`+0xd`
(assorted bytes) -- other types read a different, shorter subset of the
same base pointer, so the record's on-disk length varies by which
constructor consumes it (only the objType index at `+8` has a
type-independent meaning).

**Object type 9 = `SpawnScriptedOneTimeObject`** (`0x0800BC6C`). This is
the chest/one-time-pickup pattern: it sets `Object.wScriptPC` from the
record's static data and checks `g_abTriggeredScriptFlags` (a
persistent bitmap) to detect whether this tile's object was already
triggered/consumed, matching what "already opened" state should look
like. Its tick handler is a distinct function at `0x0800BDCC`, function-
boundaried but not yet cleanly decompilable -- needs a proper
re-analysis pass. Types 2/4/6 (`0x0802BB00`/`0x08026414`/`0x08026348`)
are structurally similar constructors (same `SnapObjectPosition`/
`SetFighterAttackAnimState_candidate` shape) for other placed-sprite
kinds, not differentiated by content. Types 0-1, 3, 5, 7-8, 10-13 are
undecompiled.

## Warp/trigger tiles

**STRUCTURAL MATCH.** `g_pRoomWarpTriggerTable`, read by three small
accessors:

- `GetRoomWarpTriggerByte_candidate` (`0x08005CE8`): one byte per
  column (no row index) -- purpose beyond "per-column byte" not
  determined.
- `GetRoomWarpTriggerOffset_candidate` (`0x08005D00`): per-tile `(dx,
  dy)` as two `i16`s at record offset `+4`/`+6`.
- `ApplyRoomWarpTrigger_candidate` (`0x08005D30`): reads a `u8` at
  record offset `+8`, then calls `WalkRoomSwitchStateChain_candidate`
  with it -- this byte is a **switch-state chain index**, tying a warp
  tile to the room-switch-state system below.

Row stride is at least 9 bytes (fields observed at `+4` through `+8`);
exact stride and the meaning of offsets `+0`-`+3` are **UNCONFIRMED**.

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
`InterpretObjectScript`'s opcode format. The one concrete script-like
field found (`SpawnScriptedOneTimeObject`'s `wScriptPC`) feeds a custom
tick handler (`0x0800BDCC`), not `InterpretObjectScript` directly. The
room-script VM ([`room_scripts.md`](room_scripts.md)) uses its own,
separate bytecode format. "Scripts that run in each area" is better
described by these two room-local systems than by the per-`Object` VM.

## Further work

- Decode the `CopyRoomBlobHeaderRecords_candidate` records' purpose (no
  consumer found).
- Decode `g_apRoomObjectConstructors` entries 0-1, 3, 5, 7-8, 10-13, and
  differentiate types 2/4/6 by actual in-game content.
- Decode `0x0800BDCC` (type-9 tick handler). See
  [`room_scripts.md`](room_scripts.md)'s own "Further work" for the
  room-script opcode table's open items.
- Confirm `g_pRoomWarpTriggerTable`'s full row stride and offsets
  `+0`-`+3`.
- Cross-check against a live mGBA session for any of the above --
  static tracing alone left several field boundaries inferred rather
  than directly observed.

## Bounding boxes / walkable-area limits

Camera scroll limit: the level table's scroll-bound fields (`levels.md`
offsets `0x6C`-`0x72`). *Walkable-area* collision -- the tile-type
geometry, slope table, and the per-type meanings including several
user-verified via live gameplay (Lumos crossings, ice, stairs, etc.) --
is a separate, finer system with its own writeup: see
[`collision.md`](collision.md).
