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
          {u32, u32} records[wRecordCount]
pSub      = blob + wSize            stage index
  +0x00   u8  variantCount
  +0x01   u8  stageToVariant[33]    indexed by g_abQuestEventState[0]; every value < variantCount
  +0x22   FF FF
  +0x24   variantCount * 8-byte entries: u16 sub-block offset from blob start, then 6 zero bytes
sub-block
  +0x00   u16 warp table offset     from the sub-block
  +0x02   u16 switch table offset   from the sub-block
  +0x04   u16 flags                 bit 0 is stored to g_wRoomResourceFlags_candidate; set in all 127 sub-blocks
  +0x06   u16 unknown               varies per sub-block, looks like an offset; no consumer found
  +0x08   object table (inline)
table     u8 count, u8 pad (0), u16 offsets[count]; offsets are from the table start
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
     returns the buffer plus `wSize`, the start of the object table. Purpose
     of the records is **UNCONFIRMED**; no consumer is known. Its second
     parameter is unused.
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
`SetObjectActionState` shape) for other placed-sprite
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
