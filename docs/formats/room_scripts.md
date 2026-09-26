# Room script bytecode

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

Status: **STRUCTURAL MATCH** for the interpreter, the state machine, and
the byte format (read directly from disassembly and cross-checked
between the two entry points below); 90 of 93 opcodes semantically
identified. This is the VM [`rooms.md`](rooms.md) calls "room
switch-state chains" -- that document owns the per-room resource-blob
layout and how a chain index is reached from a warp tile or the
switch-state object table; this document owns the interpreter and
opcode format itself.

## What this is

A second bytecode VM, entirely separate from
[`battle_scripts.md`](battle_scripts.md)'s `InterpretObjectScript` (no
shared tables, no shared entry points). It drives room-local scripted
sequences: setting flag bits on a tile's spawned `Object`, opening
dialog boxes, pausing/resuming/switching the Krawall music module, and
invoking other chains conditionally. It is reached far more broadly
than just warp tiles: `InitializeOverworld` runs chain `0` (and
conditionally chain `1`) when a room is entered fresh, and again after an
object-state restore that finds the saved state stale; several other
functions (`FUN_0800483c`, `FUN_08003be4`, `FUN_08004fde`, `FUN_08004d58`,
`FUN_0800a03c`, `FUN_08004c48`) trigger it too --
consistent with "the scripted sequence that runs when this room is
entered/re-entered", not a lever-specific mechanism.

## The interpreter

Two entry points share one opcode loop:

- **`WalkRoomSwitchStateChain_candidate`** (US `0x08005410`) starts a
  chain fresh, given a chain index (`param_1`) and a `resumeFromSaved`
  flag (`param_2`).
- **`ResumeRoomSwitchStateChain_candidate`** (US `0x080055C0`) resumes
  whatever chain was left paused (see "Pause/resume" below) with no
  arguments of its own.

Both walk the same record-by-record loop:

1. Read a `u32` opcode at the current record pointer.
2. Opcode `0` terminates the chain (see "The byte format" below) --
   no handler is called for it.
3. Otherwise, call the opcode's handler through
   `g_apRoomScriptOpcodeHandlers[opcode]` (via `ThumbInterworkVeneer`,
   `_call_via_r1`), passing the record pointer itself as the one
   argument.
4. Advance the record pointer by `g_abRoomScriptOpcodeLengths[opcode]`
   bytes and loop, unless the handler set the pause flag (see below).

## The byte format

Unlike `InterpretObjectScript`'s script (a `u8` opcode + operand
bytes), a room-script record's opcode is a full **`u32`** at record
offset `0` -- confirmed by the interpreter reading `*(int *)pObject`
and the length table's smallest entry being `4` (an opcode with no
operands still occupies a whole word). Record layout:

```
opcode : u32
operand_bytes : u8[N]   -- N = g_abRoomScriptOpcodeLengths[opcode] - 4
```

**`g_abRoomScriptOpcodeLengths`** (US `0x0805EB34`, `byte[93]`, padded
to a `u32`-aligned 96 bytes): gives each opcode's *total* record length
(opcode word included), always a multiple of 4. Index `0`'s entry (`4`)
is never actually consulted for advancing past a real instruction,
since opcode `0` terminates the walk before the handler dispatch.

**`g_apRoomScriptOpcodeHandlers`** (US `0x0805BA8C`, `void*[93]`):
index `0` is a null entry (opcode `0` has no handler, matching its
role as terminator); indices `1`-`92` are real Thumb handler addresses.
93 is the real length -- the entry immediately past index `92`
(`0x0805BC00`) is not a valid code pointer, and it lines up with where
`g_abRoomScriptOpcodeLengths`'s own real data ends (both tables were
read directly from ROM to confirm this boundary, not inferred from one
alone).

None of these 93 handler addresses were found as `gbadisasm`-seeded
functions -- like `InterpretObjectScript`'s `Wait`-family handlers (see
`battle_scripts.md`), they sit in a region `gbadisasm` didn't
recognize as code on its own; every address cited below was confirmed
with `disassemble_bytes` directly.

## Known opcodes

Addresses are US-ROM-specific, cited in prose only (see
`battle_scripts.md`'s "Why no addresses in opcodes.json" for why: this
project's convention is to keep bytecode-format knowledge free of
per-build addresses once it's committed to a machine-readable table --
`tools/room_scripts/opcodes.json` already follows this).

Several opcodes below take a tile `(x, y)` pair resolved through
`GetRoomObjectField_candidate` (US `0x08005C60`, not otherwise
documented -- see `rooms.md`'s "Static per-tile object table" for the
sibling accessor `GetRoomObjectRecordPtr_candidate` this one parallels).
`GetRoomObjectField_candidate` has its own special case for
`x == 0 && y >= 0xFE`: instead of the normal 2D tile lookup, it reads a
small fixed global array at `0x03003358` (`(0xFF - y) * 4`-indexed).
Every real script that targets a tile object uses exactly `(x=0,
y=255)` -- i.e. **every observed use of this pair selects that special
slot (index `0`), never an actual tile** -- so `x`/`y` are still named
for what the handler's argument order is, not because real content
ever varies them this way.

| Opcode | Name | Operand bytes | Meaning |
|---|---|---|---|
| `0` | `End` | 0 | Terminates the chain. No handler; the interpreter checks for it directly. |
| `1` | `DespawnTileObject` | 4 (x, y, ...) | Looks up the live `Object*` at tile `(x, y)` via `GetRoomObjectField_candidate` (US `0x08005C60`), then ORs `0x82` into *both* that object's `Object+0xc` flags dword and the running chain's own "current object" pointer's (`chainRecord+0xa4`) `+0xc` flags dword, if each is non-null. Handler at US `0x0801C5CC`. |
| `2` | `opcode_2` | 4 | Looks up the tile `(x, y)` object as above; if its `+8` halfword is `0`, computes `operand[+6] (i16) * 5 << 14`, else `operand[+6] (i16) << 16`, storing the result into the object's `+0x28` field (a fixed-point value, scale depending on a length/state field), then sets bit `0x08` of the object's `+0x90` byte. Handler at US `0x0801C5FC`. Not confidently named -- reads like configuring an animation/movement speed with a special-cased default. |
| `3` | `SetTileObjectFlagBit` | 4 (x, y, bit index) | `Object+0xc \|= 1 << bitIndex` on the tile `(x, y)`'s live object (via `GetRoomObjectField_candidate`). Handler at US `0x0801C634`. Complementary pair with `4` below. |
| `4` | `ClearTileObjectFlagBit` | 4 (x, y, bit index) | `Object+0xc &= ~(1 << bitIndex)` -- the complement of `3`. Handler at US `0x0801C654`. |
| `5` | `ShowRoomDialog` | 4 (dialog block id u16, 2 padding bytes) | Pushes the `Dialogue` game mode (`FUN_0801FB54`, US `0x0801FB54`: sets `g_dwGameModeFlags \|= 1`, stores the block id into `DAT_03002E94`, calls `PushGameMode(Dialogue)`), plays a fixed sound (`PlaySoundById(0x24)` if the block id is exactly `0x270`, else `PlaySoundById(5)` -- a distinct "special/other" open-dialog sound), and stashes its last 2 operand bytes into `DAT_03002EA4`/`DAT_03002EA5` -- always `0` across every real call site, so these are padding, not a used field. Also transitions the chain's own pause state from `1` to `2` if currently `1` (see "State machine" below). Handler at US `0x0801C674`; tail-dispatches through an unrecovered indirect jump table Ghidra couldn't statically resolve (multi-branch, not traced further). This is the concrete link between room scripts and story/NPC dialog. **The block id is not a `GetDialogText` string id directly** -- see "The dialog-block indirection" below. |
| `6` | `PauseMusic` | 0 | `krawall::krapPause(0)` (only if not already paused; latches `DAT_03005AC1`). Handler at US `0x0801C6BC`. |
| `7` | `ResumeMusic` | 0 | `krawall::krapUnpause()` (only if `PauseMusic` had paused it). Handler at US `0x0801C6C8`. Complementary pair with `6`. |
| `8` | `PlayMusicModuleAndFlagIfChain1` | 4 (moduleId, unused, unused, unused) | If `DAT_03001DDE` (the chain index the interpreter is *currently walking* -- latched at the top of every `WalkRoomSwitchStateChain_candidate` loop pass, see "State machine" below) equals `1`, ORs bit `0x1000000` into `g_dwGameModeFlags` (US `0x03003B44`) first; unconditionally after that, calls `PlayMusicModule` (US `0x0803FEB4`) with `moduleId`, switching the current Krawall module (a no-op if it's already playing). `InitializeOverworld` clears that bit and skips its room-music selection when it was set, so the bit means "the room's music is already chosen" (**PROVEN**, both sites read from the disassembly). Handler at US `0x0801C6D4`. |
| `9` | `PlayRoomSoundEffect` | 1 (sound id) | ORs `g_dwGameModeFlags` bit `0x1000000` if `g_bRoomScriptCurrentRow == 1`, then plays the id via `PlaySoundEffect_candidate` (US `0x0803FF70`). Handler at US `0x0801C700`. |
| `0xA` (10) | `PlaySoundById` | 1 (sound id) | Plays the id via `PlaySoundById` (US `0x0803FC68`) -- the same function `ShowRoomDialog` (opcode `5`) uses for its own open-dialog sound. Handler at US `0x0801C72C`. |
| `0xB` (11) | `SetRoomMusicVolume` | 1 (volume) | Calls `SetMusicVolume(volume, 1)` (US `0x0803FE88`). Handler at US `0x0801C738`. |
| `0xC` (12) | `SetSoundEffectVolume` | 1 (volume) | Calls `FUN_0803FE78`, which clamps the byte to `0xFF` and stores it in a write-only-observed global (`DAT_03000091`) -- shaped like a sound-effect-volume setter paired with `SetRoomMusicVolume` (`0xB`), by shape and address proximity; no confirmed reader found. Handler at US `0x0801C748`. |
| `0xD` (13) | `SetCameraPanSpeedOrRunRowChain` | 4 (speed u16, row, chainRow) | If `speed` is `0`, calls `RespawnRowAndRunChain_candidate` (US `0x08005B00`, shared with opcode `0x46`) on `(row, chainRow)` instead. Otherwise arms the yield flag (if `DAT_03001DE4` is set), spawns a script-effect object (`SpawnScriptEffectObject_candidate(1)`, US `0x0802018C`, `Object` type `0xE`) and writes `speed * 30` into its `+0x80` field and `row`/`chainRow` into `+0x6C`/`+0x6D` -- shaped like a camera-pan-speed request, not independently confirmed against real content. Handler at US `0x0801C754`. |
| `0xE` (14) | `SetStoryStage` | 1 (value) | `g_abQuestEventState[0] = value` -- writes the persistent story-stage index directly (index `0` of the same array `SetQuestState`/opcode `0x1F` writes generically, and `GotoIfStoryStageCompare`/opcode `0x36` reads). Complementary write-side counterpart to that read. Handler at US `0x0801C7B0`. |
| `0xF` (15) | `SetTileObjectAnimState` | 4 (x, y, unused, unused) | Resolves the tile `(x, y)` object, then calls `SetObjectActionState` (US `0x08001E7C`, `Object.bActionState`) with a **hardcoded `4`** -- not read from the operand. `SetObjectActionState` is a generic per-`Object` setter (also used by battle fighters, dialogue, loading-screen transitions, and wandering monsters -- see `battle-ui.md`), not something specific to this opcode's tile object. Handler at US `0x0801C7BC`. |
| `0x10` (16) | `QueueTileObjectMove` | 5 (x, y, facing, unk, speed u16) | Resolves the tile object and writes it into one slot (index `DAT_03003379`) of a shared "queued object move" array (parallel `DAT_030020xx` arrays, count `DAT_03003378`, see `SetAllQueuedMoveParams`/`ClearAllQueuedMoves`), copying the currently-active slot's velocity (`Object+0x3c`/`+0x40`) onto the new slot and zeroing that source object's velocity. Arms the yield flag first. Handler at US `0x0801BF58`. **Camera behavior**: the record is a `CameraEffect` (`include/overworld.h`) ticked by `TickCameraFocus_candidate`; state 1 pans the camera focus to the object, then runs the row/chain operands, so the opcode name describes the operand, not the effect; see [`../memory-map/frame_systems.md`](../memory-map/frame_systems.md). |
| `0x11` (17) | `ReturnToOverworld` | 2 (exitId, param) | Fills the same 2-entry `DAT_0300337D` table `CloseRoomDialog` (opcode `0x16`) does, then `PushGameMode_2(Overworld, 0, exitId)`. Handler at US `0x0801C7D4`. |
| `0x12` (18) | `SetAllQueuedMoveParams` | 6 (speed u16, posX u16, byte, byte) | Broadcasts the same parameters (position from `posX`, speed*30, state=3, plus two operand bytes) to every active slot (`0..DAT_03003378`) of the queued-object-move array `QueueTileObjectMove` (opcode `0x10`) populates. Handler at US `0x0801C04C`. **Camera behavior**: state 3 is a camera shake (`posX << 16` is the amplitude, `speed * 30` the frame count); see [`../memory-map/frame_systems.md`](../memory-map/frame_systems.md). |
| `0x13` (19) | `ClearAllQueuedMoves` | 0 | Zeroes the state field for every active slot (`0..DAT_03003378`) of the queued-object-move array -- clears what `SetAllQueuedMoveParams`/`QueueTileObjectMove` set. Handler at US `0x0801C810`. |
| `0x14` (20) | `SetTileObjectPosition` | 6 (posX i16, posY i16, tileX, tileY, facing/state byte) | Resolves the tile `(tileX, tileY)` object via `GetRoomObjectField_candidate`, writes its absolute `nX`/`nY` (16.16 fixed point, from `posX`/`posY` shifted left 16) and `field_0x12`, then sets `field_0x90` bit `0x10`. Handler at US `0x0801C84C`. A direct teleport/placement opcode, distinct from `StartObjectAnimSequence`'s (`0x18`) animated move. |
| `0x15` (21) | `PlayCutscene` | 3 (cutsceneId, pendingRow, pendingChain) | Latches `pendingRow`/`pendingChain` into `g_bPendingRoomScriptRow`/`g_bPendingRoomScriptChain`, then pushes the `GameMode` for `cutsceneId` (`0`-`0xF`): `ClockSkipCutscene`, `HogwartsUpNightCutscene`, `CoolTrainCutscene` (ids `2` and `3` both), `Intro`, `HarryArrivedAtHogwartsCutscene`, `UnusedChristmasArrivedCutscene`, `SiriusBlackCutscene`, `PeterPettigrewCutscene`, `RonSleepingCutscene`, `TimeTurnerPermissionCutscene`, `HippogriffFliesIntoAirCutscene`, `LupinPotionCutscene`, `HarryPatronusCutscene` (ids `0xD` and `0xE`, both also call `PlayMusicModule(0x31)` first), `HarryHermionePortInTimeCutscene`. Handler at US `0x0801C87C`. The concrete link between room scripts and the game's cutscene mode list -- all 15 names come straight from Ghidra's existing `GameMode` enum. |
| `0x16` (22) | `CloseRoomDialog` | 2 (unused -- fills a small 2-entry table, purpose not traced) | Clears `g_dwGameModeFlags` bit `0x1` if set -- the same bit `ShowRoomDialogBox_candidate` (the mode `ShowRoomDialog`/opcode `5` pushes) sets, so this closes/cancels an already-open room dialog box. Handler at US `0x0801C974`. |
| `0x17` (23) | `SetTileObjectShadow` | 7 (x, y, shadowX, shadowY, useShadowTile bool, field_0x65, field_0x68) | Resolves the tile object and sets its `pShadowObject` to either the default special-object slot `0` or a second resolved tile object (`shadowX`, `shadowY`) if `useShadowTile` is set, then sets `field_0x65`/`field_0x68` and action state `0x12`. Handler at US `0x0801C9B0`. |
| `0x18` (24) | `StartObjectAnimSequence` | 12 (x, y, effectId, localA, localB, unk, animStateSelector, stateByte0x60, flagsA, flagsB, unused, unused) | Restores any pending camera focus (`RestorePendingCameraFocus_candidate`, US `0x0802E6FC`, also called by `0x11` and `CancelObjectAnimSequence`/`0x21`), arms the pause state (`1`->`2`) like `ShowRoomDialog`, resolves the tile `(x, y)` object, then writes `Object+0x62/0x63/0x64/0x65` (`bScriptEffectId`/`bScriptLocalA`/`bScriptLocalB`/one more byte) and `Object+0x60` (`u16`) directly from operand bytes -- **the exact same fields `battle_scripts.md`'s `InterpretObjectScript` VM owns** (`bScriptEffectId`, `bScriptLocalA`/`B`, and the `opcode_30`-tracked `Object+0x60` state byte). Also sets `Object+0x6A`/`0x6B` from two more operand bytes, calls `SetObjectActionState` (US `0x08001E7C`, see `0xF`'s row above) with one of 7 fixed state values (`7`-`13`, selected by an operand byte `0`-`6`; value `6`/state `13` additionally clears `Object+0xc` bit `0x10`), calls `FUN_08001E58(obj, 0)` (not traced), and sets `Object+0xc` bit `0x8`. Handler at US `0x0801C0E8`, tail-dispatches through an unrecovered jump table. Concretely: **a room script can drop a canned animation/effect sequence onto an arbitrary tile object** by writing the same `Object` fields the battle-script VM uses for its own effect playback -- the two VMs don't share bytecode, but they share the fields that drive that one animation subsystem. |
| `0x19` (25) | `StartTileObjectScript` | 12 (scriptPC u16, effectId+localA packed u16, unk65, unk66, unused x6) | Resolves the tile object, arms the yield flag (`Object+0xc` bit `0x8000000`) like `ShowRoomDialog`/`StartObjectAnimSequence`, restores any pending camera focus, then writes `Object->wScriptPC` directly from the operand -- launching that object's own `InterpretObjectScript`-driven behavior (`battle_scripts.md`) at an arbitrary bytecode offset, distinct from `StartObjectAnimSequence` (0x18)'s fixed animation-state dispatch. Also sets `bScriptEffectId`/`bScriptLocalA`/`field_0x65`/`field_0x66` and calls `SetObjectActionState(obj, 0xf)`. Handler at US `0x0801C1D8`. The concrete bridge letting a room script hand an object off to the object-script VM. |
| `0x1A` (26) | `PlayTileObjectAnimation` | 4 (x, y, animId u16) | Resolves the tile object, arms the yield flag, then calls `FUN_0802fe04` (US `0x0802FE04`, `SetObjectAnimData` with an anim-table id, `field_0x18 = animId`, action state `0x16`) and sets `Object+0xc` bit `0x10`. Handler at US `0x0801CA08`. |
| `0x1B` (27) | `OpenMainMenu` | 0 | `PushGameMode(MainMenu)`; ORs `g_dwGameModeFlags` bit `0x80000000`. Handler at US `0x0801CA4C`. |
| `0x1C` (28) | `ArmChainYield` | 4 (bool, 3 unused) | `DAT_0300279C = (operand[0] != 0) ? 1 : 0`. Handler at US `0x0801CA68`. This writes one byte; whether anything actually yields depends entirely on the *next* opcode's own handler separately checking for state `1` and bumping it to `2` -- only `ShowRoomDialog` and `StartObjectAnimSequence` currently do that. Real scripts bracket one of those two opcodes with it: `ArmChainYield 1` immediately before, `ArmChainYield 0` immediately after. See "State machine" below for what state `2` actually does and how the chain resumes. |
| `0x1D` (29) | `GotoIfQuestStateCompare` | 8 (questStateIndex, cmpOp, compareValue, trueChain, falseChain, trueRespawnRow, falseRespawnRow, unused) | Compares `g_abQuestEventState[questStateIndex]` against `compareValue` using `cmpOp` (`0`=`==`, `1`=`!=`, `2`=`>`, `3`=`>=`, `4`=`<`, `5`=`<=`), via the shared comparator `FUN_0801D390` (US `0x0801D390`, also used by `GotoIfStoryStageCompare` below). On the branch taken, sets the pending-jump field `DAT_030028A0` to that branch's chain id (`trueChain`/`falseChain`; `falseChain = 0` means "no jump", not chain `0`) and calls `FUN_0800539C` on that branch's respawn-row operand -- the same object-respawn primitive `InvokeChainIfEnabled` (`0x40`) uses. Handler at US `0x0801CA88`. A real conditional-branch-plus-respawn opcode, structurally the room-script VM's answer to `battle_scripts.md`'s `GotoIfLocalA*` family. |
| `0x1E` (30) | `GotoIfQuestStatePairCompare` | 8 (indexA, cmpOp, indexB, trueChain, falseChain, trueRespawnRow, falseRespawnRow, unused) | Same comparator (`CompareAndBranchRoomScript_candidate`, US `0x0801D390`) and branch/respawn mechanics as `GotoIfQuestStateCompare`/`GotoIfStoryStageCompare`, but compares `g_abQuestEventState[indexA]` against `g_abQuestEventState[indexB]` -- two variable slots -- instead of one slot against a literal constant. Handler at US `0x0801CAB8`. |
| `0x1F` (31) | `SetQuestState` | 4 (value, index, 2 unused) | `g_abQuestEventState[index] = value` (`0x030027A0` is `g_abQuestEventState`'s own base address, confirmed against [`save.md`](save.md) -- **not** a scene-local scratch variable; this opcode writes the same persistent, save-serialized 256-byte array `GotoIfQuestStateCompare` reads). Handler at US `0x0801CAEC`. Paired with `GotoIfStoryStageCompare` (`0x36`) below, which reads index `0` of the same array. |
| `0x20` (32) | `CopyQuestState` | 4 (srcIndex, unused, unused, dstIndex) | `g_abQuestEventState[dstIndex] = g_abQuestEventState[srcIndex]`. Handler at US `0x0801CAFC`. |
| `0x21` (33) | `CancelObjectAnimSequence` | 4 (x, y, unused, unused) | Resolves the tile `(x, y)` object; if non-null, calls `CancelObjectMove_candidate` on it (US `0x08001A78`, zeroes `Object+0x3C`/`0x40`/`0x44`/`0x48` -- clearing the velocity fields `battle_scripts.md`'s `TickObjectMove` drives) and clears `Object+0xD8`, also clearing the same byte on a linked object at `Object+0xA4` if set; if a pending camera-focus flag is set, calls `RestorePendingCameraFocus_candidate` (the same function `0x11`/`0x18` call); resets the object's action state to `0` (`SetObjectActionState`); and **unconditionally** resets `g_pPlayerObject`'s own sub-state to `0` (`SetObjectAnimSubState_candidate`), regardless of which tile object was targeted. Handler at US `0x0801CB10`. The natural counterpart to `StartObjectAnimSequence` (`0x18`) -- cancels the move/anim state that opcode starts. |
| `0x22` (34) | `SetTileObjectAnimStateWithSpeed` | 4 (x, y, unused, unused) | Resolves the tile `(x, y)` object; if non-null, calls `SetObjectActionState(obj, 33)` and a second, unnamed one-byte setter (US `0x08001EA0`, writes `Object+0x8E`) with the same hardcoded `33`, then writes a fixed-point constant (`0xA0 << 10`) into `Object+0x28` -- the same field `opcode_02` configures with variable operand data (candidate: an animation speed/duration). Handler at US `0x0801CB70`. |
| `0x23` (35) | `PatchRoomBackgroundTile` | 8 (x u16, y u16, tileId u16, layer byte) | Calls `FUN_0803dd7c` (US `0x0803DD7C`), which decompresses/writes a background tile into VRAM at a screen-block position derived from `x`/`y` (each `>>5`, i.e. 32px granularity) -- a room-local background tile patch. Handler at US `0x0801CB9C`. Field roles are structurally clear from the callee but not cross-checked against real script content yet. |
| `0x24` (36) | `ShowLoadingScreenTransition` | 4 (3 bytes forwarded to `PushGameMode_3`, unused) | Arms the yield state, ORs `g_dwGameModeFlags` bit `0x1` (the same "dialog open" bit `ShowRoomDialogBox_candidate` sets), then `PushGameMode_3(LoadingScreen, ...)`. Handler at US `0x0801CBB4`. |
| `0x25` (37) | `PlayScreenTransitionOut` | 0 | Calls `PlayScreenTransitionOutByIndex` (US `0x0803D3E8`) with `(0x3f, 2)`, the exit-side counterpart of opcode `0x26`. That dispatcher sets `g_dwGameModeFlags` bits `0xC00`, dispatches through the parallel effect table at `0x0806B880` by its second argument, then clears them. Game modes call it from their exit handlers, and the entry-side dispatcher from their init handlers (about 50 call sites each). Which effect index `2` draws is not decoded. Handler at US `0x0801CBE8`. |
| `0x26` (38) | `PlayScreenTransitionIn` | 0 | Takes no operand -- calls `PlayScreenTransitionInByIndex(63, 2)` with both arguments hardcoded. `PlayScreenTransitionInByIndex` (US `0x0803D3B0`) sets `g_dwGameModeFlags` bit `0x800` ("transition in progress"), dispatches through the effect table at `0x0806B844` (at least 14 entries) by its second argument, then clears the bit; entry `2` (`0x0803C450`) is a real blocking full-screen palette-fade routine -- it snapshots palette RAM, computes fade curves (`FUN_0800D5DC`, called with distinct curve-type arguments `1` and `5`), then runs a `DAT_0300563C`-frame loop that still pumps the normal per-frame tick (particle emitters, the overworld tick, etc.) while fading. The other table entries are not decoded. Handler at US `0x0801CBF8`. |
| `0x27` (39) | `RecruitPartyFollower` | 1 (characterId) | Calls `SyncFollowerLevelToLeader_candidate(characterId)` unconditionally (catches the new follower's level up to the party leader's, within a few levels, adjusting reward XP), then assigns the follower object into whichever slot is currently empty (`AssignPartyFollowerSlotA_candidate` if `DAT_03003384 == 0`, else `AssignPartyFollowerSlotB_candidate`) -- the slot choice is automatic, not operand-controlled -- and copies a fighter-type field from the newly assigned object. Reads as "recruit/add a following party member" -- distinct from `SpawnPartyFollowerAtTile` (opcode `0x29`), which places an already-recruited follower object on a specific tile. Handler at US `0x0801CC08`. |
| `0x28` (40) | `RemovePartyFollower` | 4 (characterId, unused, unused, unused) | Calls `FUN_080236dc` (US `0x080236DC`), which removes/despawns whichever of the two active party-follower slots (`DAT_03003384`/`DAT_03003388`) currently holds that character id, unhooking it from `g_pPlayerObject`. Handler at US `0x0801CC50`. Complementary pair with `SpawnPartyFollowerAtTile` (`0x29`). |
| `0x29` (41) | `SpawnPartyFollowerAtTile` | 4 (characterId, x, y, unused) | Calls `FUN_0802f6c0` (US `0x0802F6C0`) to allocate and configure a new party-follower `Object` (type `6`) positioned at the current leader/companion's location, calls the same `FUN_080236dc` opcode `0x28` uses to clear out any existing follower with that id first, then places the new object into the room's tile table at `(x, y)` via `SetRoomObjectRecordPtr_candidate`. Handler at US `0x0801CC5C`. |
| `0x2B` (43) | `StartBattle` | 4 (battleId, pendingRow, pendingChain, unused) | Resets `g_bRoomScriptCallStackDepth` to `0`, latches `g_bPendingRoomScriptRow`/`g_bPendingRoomScriptChain` (the chain to resume after the battle), plays a fixed sound (id `6`), then `PushGameMode_3(Battle, battleId, 0, 0xff)`. Handler at US `0x0801CC8C`. |
| `0x2C` (44) | `SetTileObjectAnimStateValue` | 4 (x, y, animState, unused) | Resolves the tile `(x, y)` object and calls `SetObjectActionState(obj, animState)` with the state taken directly from the operand -- the non-hardcoded sibling of `0xF`/`0x22` (`SetTileObjectAnimState`/`SetTileObjectAnimStateWithSpeed`), which pass fixed state constants. Handler at US `0x0801CCC8`. |
| `0x2D` (45) | `GrantRoomReward` | 2 (rewardId, variant byte) | Puts `g_pPlayerObject` into its "receive item" animation state (action state `0x17`, `field_0x92 = rewardId`) and calls the already-identified `GrantReward(rewardId, count)` (count is a random 30-60 roll only for `rewardId 0x83`, else `1`) directly from a room script rather than a battle outcome. The `variant` byte selects whether `field_0x80` is additionally set to `0x42` afterward. Handler at US `0x0801CCEC`. |
| `0x2E` (46) | `SetBackgroundBlendLayers` | 4 (bit flags) | Packs the 4 operand bytes into a 4-bit mask and writes `BLDCNT = mask \| 0x40 \| (0x1f << 8)` -- enables alpha blending with all 5 background/OBJ target-2 layers, selecting target-1 layers by the operand bits. Handler at US `0x0801CD08`. |
| `0x2F` (47) | `ShowBackgroundLayer` | 1 (layer index) | Calls `SetDispcntFlag` to enable the DISPCNT display bit for the given BG/OBJ layer index. Complementary pair with `HideBackgroundLayer` (opcode `0x30`). Handler at US `0x0801CD30`. |
| `0x30` (48) | `HideBackgroundLayer` | 1 (layer index) | Calls `FUN_08007434` (US `0x08007434`: `DISPCNT &= ~param_1`, a direct DISPCNT-bit clear) with the same bit shift `ShowBackgroundLayer` uses -- the disable counterpart to opcode `0x2f`. Handler at US `0x0801CD3C`. |
| `0x31` (49) | `SetBackgroundPriority` | 2 (bg, priority) | Thin wrapper over the already-named `SetBgPriority(bg, priority)`. Handler at US `0x0801CD48`. |
| `0x33` (51) | `PlaySpecialSceneEffect` | 1 (mode 0-5) | Multi-mode scene-effect dispatcher: modes `0`/`1` install a BG control override (`InstallBgControlOverride_candidate`) and set `g_abQuestEventState[0x1d]`; mode `2` removes the override and clears that state; mode `3` runs a full fade-to-white/module-9-swap/fade-back sequence and sets `g_abQuestEventState[0x1a]`; modes `4`/`5` set the player object's facing (`field_0x12`) and a hardcoded velocity (`field_0x3c`/`0x40`). The narrative context tying these modes to a specific story beat is not identified. Handler at US `0x0801C280`. |
| `0x34` (52) | `SetCameraPanSpeedOrRunRowChainAlt` | 4 (speed u16, row, chainRow) | Identical logic to `SetCameraPanSpeedOrRunRowChain` (opcode `0x0d`) -- a separate table entry for the same behavior, not a distinct mechanism. Handler at US `0x0801CD74`. |
| `0x35` (53) | `SetTileObjectAndLinkedVisible` | 3 (x, y, bool) | Resolves the tile object and sets/clears `Object+0xc` bit `0x1` per the `bool` operand, propagating the same set/clear to its linked object's (`field_0xa4`) `Object+0xc` bit `0x1` if present. Handler at US `0x0801CDCC`. |
| `0x36` (54) | `GotoIfStoryStageCompare` | 8 (cmpOp, compareValue, trueChain, falseChain, trueRespawnRow, falseRespawnRow, unused x2) | Same comparator (`FUN_0801D390`) and branch/respawn mechanics as `GotoIfQuestStateCompare` above, but with `questStateIndex` hardcoded to `0` -- `g_abQuestEventState[0]`, the story-stage index `save.md` already documents as PROVEN. Functionally `GotoIfQuestStateCompare 0 ...`, not a separate mechanism or a separate variable; kept as its own opcode number regardless. Handler at US `0x0801CE18`. |
| `0x37` (55) | `SetRandomQuestState` | 3 (min i16, max i16, index) | `g_abQuestEventState[index] = Mt19937RandRange(min, max)`. Handler at US `0x0801CE44`. |
| `0x38` (56) | `NoOp` | 4 (unread) | No-op -- the handler body is empty, never touching its operand bytes despite `g_abRoomScriptOpcodeLengths` reserving 4 for it. Handler at US `0x0801CE68`. |
| `0x39` (57) | `SetScreenWindow` | 12 (windowId, x0 i16, y0 i16, x1 i16, y1 i16, winIn, winOut) | Calls `FUN_08045838(windowId, winIn, winOut)` -- sets the GBA hardware window's WININ/WINOUT layer masks and enables its DISPCNT bit -- then `FUN_080458a8(windowId, x0, y0, x1, y1)` (all coords shifted to 16.16 fixed point) to set its rectangle bounds. Complementary pair with `HideScreenWindow` (opcode `0x3a`). Handler at US `0x0801CE6C`. |
| `0x3A` (58) | `HideScreenWindow` | 1 (windowId) | Calls `FUN_08045808(windowId)`, which disables that GBA hardware window's DISPCNT bit via the same `FUN_08007434` `HideBackgroundLayer` (opcode `0x30`) uses. Handler at US `0x0801CEA4`. |
| `0x3B` (59) | `SetTileObjectFacing` | 3 (x, y, facing byte) | Resolves the tile object, sets action state `3` (idle), and writes `Object->field_0x12` (facing, halved if `Object+0xc` bit `0x100000` is set). Handler at US `0x0801CEB0`. |
| `0x3C` (60) | `AddQuestState` | 2 (delta i8, index) | `g_abQuestEventState[index] += delta`. Handler at US `0x0801CEE0`. |
| `0x3D` (61) | `SubtractQuestState` | 2 (delta i8, index) | `g_abQuestEventState[index] -= delta`. Handler at US `0x0801CEF4`. |
| `0x3E` (62) | `ClearQuestStateUpperHalf` | 0 | Zeroes `g_abQuestEventState[0x80..0xff]`. Handler at US `0x0801CF08`. |
| `0x3F` (63) | `NoOpAlt` | 4 (unread) | No-op -- the handler body is empty, a second distinct instance of the same do-nothing shape as opcode `0x38`, also with a reserved-but-untouched 4-byte operand. Handler at US `0x0801CF24`. |
| `0x40` (64) | `InvokeChainIfEnabled` | 4 (respawnRow, targetChain, unused, unused) | Sets the pending-jump field `DAT_030028A0` to `targetChain` (operand `+5`) unconditionally, then calls the gate `FUN_08005B44(respawnRow)` (operand `+4`) and, only if it passes, calls `FUN_0800539C(respawnRow)` -- `FUN_0800539C` respawns every not-yet-spawned static object in that row/column of `g_pRoomObjectTable` (the same 2D table `rooms.md`'s "Static per-tile object table" documents). `FUN_08005B44(n)` is `false` for `n == 0` unconditionally, `true` for `n >= 2` unconditionally, and conditional on `DAT_03001DDC` bit `0` only for `n == 1` (worked out truth-table-style, not by inspection -- see "The `FUN_08005B44` gate" below). Every real script's `respawnRow` for this opcode is `0`, so **the respawn call never actually fires in any currently-known content** -- the opcode's only observed real-world effect is the `targetChain` jump, making it behave like an unconditional `Goto` in practice even though the respawn path is real, reachable code. Handler at US `0x0801CF28`. This is the one opcode the interpreter's own bookkeeping special-cases (`if (*pObject != 0x40)`, see "State machine" below) -- it manages the pause/call state itself instead of letting the generic nested-chain-call logic do it. |
| `0x41` (65) | `GrantPartyExperience` | 1 (xpAmount u16) | Grants `xpAmount` experience to `g_pPlayerObject` plus every active party-follower slot (`DAT_0300338c`/`d`/`e`, the same globals `FUN_080236dc` manages for opcodes `0x28`/`0x29`), via `GrantFighterExperience_candidate` (US `0x080148F4`), which deducts it from each fighter's `wRewardXp` counter and repeatedly calls `LevelUpFighter` while that goes to or below zero. For each character, shows a floating text popup: dialog `0x52d` if no level-up occurred this call, or sound `0x1b` + dialog `0x52e` if it did. A separate per-character byte is also decremented by `5` (floored at `4`) before this -- a follower-slot/icon index unrelated to XP, feeding a sprite-selection table. Handler at US `0x0801CF4C`. |
| `0x42` (66) | `SetBattleDefeatState` | 1 (value) | `g_abQuestEventState[0x10] = value` -- see [`save.md`](save.md)'s battle-defeat-state note (index `0x10` is also touched by `CheckBattleDefeat`). Handler at US `0x0801CF58`. |
| `0x43` (67) | `SetTileObjectDrawLayer` | 3 (x, y, layer 2-bit value) | Resolves the tile object and writes the low two bits of the operand into `Object.oam.priority` (byte `0xD5` bits 2-3, same field `SetObjectDrawLayer` writes). Handler at US `0x0801CF64`. |
| `0x44` (68) | `EnterFredAndGeorgesShop` | 4 (modeArg2, respawnRow, targetChain, unused) | Writes `respawnRow`/`targetChain` (operand `+5`/`+6`) into `DAT_0300260D`/`DAT_0300260C` -- the exact two globals `InitializeOverworld` reads at its own tail (`WalkRoomSwitchStateChain_candidate(DAT_0300260C, 0)` then `FUN_0800539C(DAT_0300260D)`, gated on `DAT_03003EF8 == 3`), i.e. this opcode is what schedules "which chain/respawn-row to run once the next room load happens" -- then calls `PushGameMode_3(46, 0, operand[+4], 0)`. `46` is `GameMode.FredAndGeorgesShop` (Ghidra's `GameMode` enum, confirmed by name), not an operand -- the only real script that uses this opcode lives in room 36, "Fred and George's Shop". Handler at US `0x0801CF94`. |
| `0x45` (69) | `FullHealParty` | 0 | Restores all 3 party members' HP/MP to max, setting `g_abQuestEventState[0xFF]` to `1` if any member wasn't already fully healed (`0` if the party was already full). Handler at US `0x0801C3EC`. |
| `0x46` (70) | `RespawnRowAndRunChain` | 2 (respawnRow, chainRow) | Thin wrapper over `RespawnRowAndRunChain_candidate(respawnRow, chainRow)` (US `0x08005B00`, shared with opcode `0xD`'s zero-speed branch). Handler at US `0x0801CFBC`. |
| `0x47` (71) | `StartMinigame` | 5 (minigameId, param, showHelp, pendingRow, pendingChain) | Latches `g_bPendingRoomScriptRow`/`g_bPendingRoomScriptChain`, then dispatches by `minigameId` (`0`=`WizardCrackerPopItMinigame`, `1`=`HippogriffGlideMinigame`, `2`=`RiddikulusMinigame`, `4`=`HarryVsDementorsMinigame`): if `showHelp` is set, pushes the shared `HelpTopicScreen` mode with `(6, minigameId, param)` instead of the minigame itself; otherwise pushes that minigame's own `GameMode` with `(6, 0, param)`, after setting a per-minigame "unlocked/seen" flag global (`DAT_03005228`/`DAT_03002040`/`DAT_03002E10` or `g_dwHippogriffForceOverworldExit`). Handler at US `0x0801C440`. |
| `0x48` (72) | `DespawnRoomRowObjects` | 1 (row) | If `ShouldRunRoomScriptRow_candidate(row)` passes, loops every column in that row's tile-object table (`FUN_08005bcc(row)` columns) and ORs `0x82` into both the object's own `Object+0xc` flags and its linked object's (`field_0xa4`) `Object+0xc` flags -- the row-batch version of `SetTileObjectFlagsPair` (opcode `1`), which does the same to a single tile. Handler at US `0x0801CFCC`. |
| `0x49` (73) | `GrantPartySpell` | 1 (characterId) | Resolves the party-stats slot via `FUN_08024aec(characterId)` and increments its `bKnownSpellCount` (capped at `7`), with a special case that skips the "+1 before the cap check" step for slot `1`. Handler at US `0x0801D020`. |
| `0x4A` (74) | `SetOverworldMonstersDisabled` | 0 | `g_dwOverworldMonstersDisabled = 1` -- the save-serialized flag [`save.md`](save.md) documents as `flOverworldMonstersDisabled`. `InitializeOverworld` only calls `SpawnOverworldMonsterEncounters` on room load when this flag is `0` (confirmed from its decompilation: the flag's zero-branch is the only one that reaches that call); setting it disables overworld random encounters on every subsequent room load until cleared. Handler at US `0x0801D04C`. |
| `0x4B` (75) | `ClearOverworldMonstersDisabled` | 0 | `g_dwOverworldMonstersDisabled = 0` -- clears the flag `SetOverworldMonstersDisabled` (opcode `0x4A`) sets, re-enabling `InitializeOverworld`'s `SpawnOverworldMonsterEncounters` call on the next room load. Handler at US `0x0801D058`. |
| `0x4C` (76) | `SetTileObjectFacingAndScriptPage` | 4 (x, y, facing byte, scriptPageHigh byte) | Resolves the tile object, sets action state `0x1B`, then writes `Object->field_0x12` (facing, halved if `Object+0xc` bit `0x100000` is set -- the same halving quirk `StartTileObjectScript`'s `bScriptLocalB` uses) and the high byte of `Object->wScriptPC`. Handler at US `0x0801D064`. |
| `0x4D` (77) | `SetTileObjectSpecialFlag` | 3 (x, y, bool) | Resolves the tile object; if `bool` is set, ORs `Object->field_0x94` bit `0x4`. Role of that field bit not established elsewhere. Handler at US `0x0801D0A4`. |
| `0x4E` (78) | `UnlockMinigame` | 1 (index 0-4) | ORs one of 5 bits (`0x2`, `0x4`, `0x8`, `0x10`, `0x20`, selected by `index`) into `g_bHeaderFlags`; any other index is a no-op. Handler at US `0x0801D0C8`. |
| `0x4F` (79) | `ShowRewardPickupMessage` | 4 (id, padding, padding, unused) | Arms the yield flag, plays a fixed sound (`0x1A`), resolves `id` to dialog text (`FUN_08026b8c` + `GetDialogText`, into `@1`/`@3` via `SetTextMacro1String`/`SetTextMacro3String`), then opens dialog block `0x28D` (string 972, **"@3 has been added to your Inventory."**) if `id < 0x4F`, else block `0x295` (string 979, **"@3 has been added to your Folio Universitas."**) -- decoded from the real string table, not inferred from the block shape. A generic reward-pickup announcement (item vs. Folio card), matching `GrantReward`'s own item-vs-card threshold. Handler at US `0x0801D138`. |
| `0x50` (80) | `ShowItemRemovedMessage` | 4 (id, padding, padding, unused) | Same shape as `ShowRewardPickupMessage` (`0x4f`): resolves `id` via `FUN_08026b8c` + `GetDialogText`, opens block `0x28E` -- string 973, **"@3 has been removed from your Inventory."** An item-removal announcement. Handler at US `0x0801D1A0`. |
| `0x51` (81) | `ShowSpellLearnedMessage` | 4 (id, gate bool, padding, padding) | Only runs if `gate` is `0` or `SaveGameHeaderBits` bit `0x4` is clear; then arms the yield flag, plays sound `0x1a`, looks up dialog text at a fixed `+0xac2` string-table offset from `id`, and opens dialog block `0x28F` -- string 974, **"You've learned a new spell: @3."** Pairs with `GrantPartySpell` (opcode `0x49`). Handler at US `0x0801D1F0`. |
| `0x52` (82) | `SetPauseMenuLocked` | 1 (value) | `DAT_03003b60 = value` -- gates the overworld Start/Select menu-open check (`HandleOverworldPauseMenuInput`): non-zero blocks opening the Options/InGameMenu mode and plays a "denied" sound instead. Handler at US `0x0801D25C`. |
| `0x53` (83) | `GotoIfFolioPageGroupComplete` | 5 (pageGroupId, rowIfTrue, chainIfTrue, rowIfFalse, chainAlways) | Checks `IsFolioPageGroupUnlocked_candidate(pageGroupId)` -- whether all 10 bits of that Folio Universitas page group (`g_abFolioUniversitasUnlocked`) are set -- and branches: on true, sets `g_bRoomScriptPendingChain` to `chainIfTrue` and conditionally respawns `rowIfTrue`; on false, conditionally respawns `rowIfFalse`. `chainAlways` is latched into `g_bRoomScriptPendingChain` first (defaulting to `-1` if `0`) and can be overwritten by the true branch. Structurally the Folio-completion sibling of `GotoIfQuestStateCompare`. Handler at US `0x0801C50C`. |
| `0x54` (84) | `ShowFolioCategoryStatusMessage` | 4 (id, bool, padding, padding) | Looks up dialog text at a fixed `+0x405` string-table offset from `id` (a Folio Universitas category name), and opens block `0x290` -- string 975, **"You don't have all the cards from the @3 collector's cards category."** -- if `bool` is `0`, or block `0x291` -- string 976, **"Congratulations! You collected all the cards from the @3 collector's cards category."** -- if `bool` is `1`. The genuine Folio-completion status announcement, natural UI pairing with `GotoIfFolioPageGroupComplete` (opcode `0x53`). Handler at US `0x0801D268`. |
| `0x55` (85) | `ShowMinigameUnlockedMessage` | 4 (id, 2 dialog-state bytes, unused) | `id == 3` opens block `0x299` -- string 934, **"Tea Leaf Divination can now be accessed from the Mini-Games menu found on the Title Screen."**; otherwise sets both macro strings to minigame name `id + 0xa4a` and opens block `0x292` -- string 977, **"You've unlocked: @3."** Bytes 1-2 go to `DAT_03002EA4`/`EA5`, as in `ShowRoomDialog`. Handler at US `0x0801BEF8`. |
| `0x56` (86) | `ShowPartyLevelUpMessage` | 4 (id, padding, padding, unused) | Sets `@1`/`@3` to `id` as a number (no `GetDialogText` lookup -- `id` is not a name-table index here), then opens fixed dialog block `0x293` -- string 978, **"All members of your party level up by @3!"** -- `id` is the level-up count. Pairs with `GrantPartyLevelUps` (opcode `0x57`). Handler at US `0x0801D2C8`. |
| `0x57` (87) | `GrantPartyLevelUps` | 4 (levelCount, unused, unused, unused) | Calls `GrantPartyLevelUps` (US `0x0801D308`, already identified from the battle side, see [`../memory-map/battle.md`](../memory-map/battle.md)'s "Leveling") directly, with the handler's `param_1` being the raw chain-record pointer like every other opcode -- `GrantPartyLevelUps` itself reads `*(byte*)(param_1+4)` as `levelCount` and calls `LevelUpFighter_candidate(0)`/`(1)`/`(2)` that many times, leveling up all 3 party members together. This is the previously-unlocated caller `save.md`/`battle.md` needed: a room script triggers party level-ups explicitly (e.g. a story event awarding levels), not an automatic threshold check against accumulated XP. No dedicated handler wrapper exists -- the room-script table's entry `87` points straight at this already-named battle-side function. |
| `0x58` (88) | `UnmuteAllMusicChannels` | 0 | Calls `UnmuteAllKrawallChannels_candidate` (US `0x08046FF0`), which scans all 32 Krawall channels and clears the mute flag on any channel that's both active and muted. Handler at US `0x0801D330`. |
| `0x59` (89) | `ConsumeRoomItem` | 1 (itemId) | Thin wrapper over the already-named `ConsumeBattleItemSlot(itemId, 1)`. Handler at US `0x0801D33C`. |
| `0x5A` (90) | `ResetPartyLeaderSelection` | 0 | Calls `CyclePartyLeaderSelection_candidate(g_pPlayerObject, 2)` -- direction `2` resets the leader/follower selection cursor rather than cycling it. Handler at US `0x0801D34C`. |
| `0x5B` (91) | `GotoIfAllQuestFlagsSet` | 4 (chainIfTrue, rowIfTrue, rowIfFalse, chainAlways) | Checks whether `g_abQuestEventState[0x14..0x18]` (5 slots) are all non-zero and branches like `GotoIfQuestStateCompare` -- the hardcoded-range sibling of that family, analogous to how `GotoIfStoryStageCompare` hardcodes index `0`. Handler at US `0x0801C564`. |
| `0x5C` (92) | `SetPendingChainFromExitParam` | 2 (chainIfExit1, chainIfExit0) | Reads `DAT_0300337D` (the 2-entry table `ReturnToOverworld`/`CloseRoomDialog` fill) and sets `g_bRoomScriptPendingChain` to `chainIfExit0` or `chainIfExit1` depending on its value -- selects a follow-up chain based on which overworld exit path was taken. Handler at US `0x0801D360`. |

Only 3 opcodes remain unidentified: `0x2`, `0x2A`, `0x32` (93 total,
0-indexed to `0x5C`; computed from `opcodes.json` directly, not
hand-counted). `0x2A` occurs 6 times in the extracted (quest-stage-0)
scripts; `0x32` occurs in none of the 1603 chains of any room and
quest-stage variant (scanned read-only from the ROM, variant blocks 0-16
per room), so it is unused content. Both are confirmed from raw
disassembly to call a callee with argument registers that the handler
itself never assigns: `0x2A`'s handler
(`0x0801CC80`) sets only `r0` before calling `FUN_080237D0`, which
itself also reads `r7` without ever setting it -- so this opcode's real
behavior depends on two registers' worth of caller-context state (`r1`
`r3`, plus `FUN_080237D0`'s own unassigned `r7`); `0x32`'s handler
(`0x0801CD58`) similarly never assigns `r4`/`r5` before its call to
`FUN_0800A3AC` (`SetCameraFollowTarget_candidate`, whose offset
arguments are those two registers). The interpreter keeps the record
pointer and the next-record pointer in `r4`/`r5`, so `0x32` most likely
passes two record pointers as camera offsets, an original bug with no
effect since no script uses it (inference, not traced). Neither register chain has been traced into a stable,
opcode-independent value, so naming either opcode would be a guess
rather than a finding.

Opcodes with no occurrence in any chain of any room or quest-stage variant
(same scan, 1603 chains): `0xB`, `0xC`, `0x14`, `0x16`, `0x17`, `0x1B`, `0x1E`,
`0x20`, `0x23`, `0x29`, `0x2E`, `0x2F`, `0x31`, `0x32`, `0x35`, `0x37`-`0x3A`,
`0x43`, `0x4C`, `0x5C`. Their handlers are reachable only through the
table.

### The `FUN_08005B44` gate

**PROVEN**, worked out with a truth table rather than by inspection
(the boolean expression reads deceptively like "`n == 0` is the normal
case"). `FUN_08005B44(char n)` (US `0x08005B44`) is:

| `n` | Result |
|---|---|
| `0` | always `false` |
| `1` | `true` only if `DAT_03001DDC` bit `0` is clear |
| `>= 2` | always `true` |

Every real script's `InvokeChainIfEnabled` (`0x40`) passes `n = 0` for
this gate, so its `FUN_0800539C` respawn call is dead in every
currently-known instance -- see that opcode's row above.
`GotoIfQuestStateCompare`/`GotoIfStoryStageCompare` pass real,
often-nonzero row values here instead, so the same gate is genuinely
exercised for those two. This gate is **unrelated** to
`InitializeOverworld`'s own chain-`0`/chain-`1` room-load logic
(`WalkRoomSwitchStateChain_candidate(0, 0)` unconditionally, chain `1`
only if `DAT_03001DDC` bit `0` is *set*) -- that code never calls
`FUN_08005B44` at all; it's a separate, direct code path that happens
to test the same bit with the opposite sense.

## The dialog-block indirection

**PROVEN.** `ShowRoomDialog`'s operand is a *dialog block id*, not a
`GetDialogText` string id -- confirmed by tracing `DAT_03002E94` (the
value the opcode stores) forward into the `Dialogue` game mode's
per-line tick (`FUN_0801F96C`, US `0x0801F96C`) and its line-render
call (`FUN_0801FC28`, US `0x0801FC28`), which is the actual site that
calls `GetDialogText`.

`0x0805CB50` (US) is an 8-byte-stride table, indexed directly by the
block id (no bounds check found, same as the opcode itself):

```
linesPtr  : u32   @ blockId*8 + 0    -- ROM pointer to a u32[lineCount] array
lineCount : u32   @ blockId*8 + 4
```

`linesPtr[i]` (`i` in `0..lineCount-1`) is the real `GetDialogText`
string id for that block's `i`-th line, advanced one at a time as the
player pages through the dialog box (`FUN_0801FA18`, US `0x0801FA18`,
increments the line cursor `DAT_03002E96` and re-runs `FUN_0801F96C`
each time the current line finishes). Confirmed concretely: block id
`426` (a real `ShowRoomDialog 426 0 0` operand from the Potions
Classroom's chains) resolves to `{linesPtr=0x0805C5B4, lineCount=2}` ->
string ids `618`/`619` -> "Hermione, how did you write that up so
quickly?" / "Umm... like I said, I'd read the book before." --
Potions-classroom-appropriate content, unlike what decoding `426`
*directly* as a string id gives (a real but unrelated line from
elsewhere in the string table -- the bug this section exists to head
off; `extract_room_scripts.py`'s dialog resolver does the two-level
lookup above, not a direct `decode_dialog_text(426)` call).

A second table at `0x08FAAF10` (same 8-byte stride, but indexed by the
resolved per-line string id -- `DAT_03002ED8` above -- not the block
id) is read by `FUN_0801F96C` into `DAT_03002EDC` on every line;
candidate: a per-message portrait pointer list, since `ShowRoomDialog`'s
own trailing operand bytes are unused padding (see the opcode table
above), leaving this as the only other portrait-shaped candidate found
so far. Not decoded or extracted -- worth a pass once more of the VM is
identified.

## State machine (pause/resume/nesting)

**STRUCTURAL MATCH**, from decompiling both entry points side by side.
Global `DAT_0300279C` tracks the VM's run state:

- `4`: disabled -- both `WalkRoomSwitchStateChain_candidate` and
  `ResumeRoomSwitchStateChain_candidate` bail immediately if set. A
  re-entrancy guard (candidate: set while some other system, e.g. a
  cutscene, owns execution -- not traced to a writer here).
- `0`: idle/fresh walk.
- `1`: set at the top of `ResumeRoomSwitchStateChain_candidate` --
  "currently resuming a previously-paused chain".
- `2`: the walk genuinely stops here -- `WalkRoomSwitchStateChain_candidate`'s
  own loop checks state `2` after every handler call and `break`s,
  latching the *next* instruction's pointer into `DAT_03001DE0` before
  returning to its caller. Only `ShowRoomDialog` (opcode `5`) and
  `StartObjectAnimSequence` (opcode `0x18`) ever transition state
  `1` to `2` (see `ArmChainYield`, opcode `0x1C`, above) -- both also
  latch the currently-dispatching opcode number into `DAT_03001DE9`
  (only while state is exactly `1`, i.e. at the moment the transition
  happens). See "Resuming a yielded chain" below for the actual
  resume condition.
- `3`: set by `WalkRoomSwitchStateChain_candidate` only when entered
  while state was already `2`; transitions back to `2` once the walk
  it started finishes fully draining. Bridges a paused chain with a
  freshly-started one running concurrently (see nesting below).

`DAT_030028A0` (aliased `0xFF` = "no pending jump") holds either the
next chain index to jump to (written by opcode `0x40`) or the sentinel
`0xFF` once consumed each loop iteration -- the loop re-reads it every
pass (`goto LAB_0800544C` / `LAB_080055E8`) so a handler can redirect
execution to a different chain index mid-walk without returning to the
caller.

**Nested chain calls**: `DAT_03001DE8` is a small stack depth counter,
`DAT_03001E00`/`DAT_03001E04` (8-byte stride) hold saved
`{continuation pointer, chain index}` pairs. Any opcode other than
`0x40` that leaves a pending jump (`DAT_030028A0 != 0xFF`) gets its
*current* continuation point pushed onto this stack before the jump is
taken, and once the jumped-to chain itself terminates (`opcode 0` and
the stack is non-empty), the walk pops back and calls
`WalkRoomSwitchStateChain_candidate` again with the saved chain index
to resume it -- i.e. **one room-script chain can call into another and
return**, with `0x40` (`InvokeChainIfEnabled`) explicitly opting out of
this generic push/pop (it manages `DAT_030028A0` itself instead).

**Resuming a yielded chain**, from tracing every real caller of
`ResumeRoomSwitchStateChain_candidate`: it is not a generic "the dialog
box closed" callback. Three per-object tick handlers call it
(`0x0800483C`, `0x08003BE4`, `0x0800A03C`, each a per-object-type state
machine unrelated to room scripts otherwise), and each only does so
once its own object's animation/movement has reached a specific
internal state *and* `DAT_03001DE9` (the opcode number latched when the
chain yielded, see above) matches the one opcode that handler cares
about -- `0x0800483C` specifically checks for `0x18`
(`StartObjectAnimSequence`). `StartObjectAnimSequence`
itself sets `Object+0xC` bit `0x8000000` on its target object exactly
when it yields (state `2`); the tick handler clears that same bit right
before resuming. So a yielded chain resumes when **the specific object
`StartObjectAnimSequence`/`ShowRoomDialog` acted on reaches a
matching state in its own, unrelated per-object tick logic** -- a
rendezvous with that object finishing something, not a dialog-box
close notification as such (a dialog box closing may itself just be
one way that object-side state gets reached).

## Disassembly (`extract-room-scripts`/`pack-room-scripts`, not build input yet)

**PROVEN** the on-ROM chain format is byte-identical to the RAM format
above: `FUN_08005E84` (US `0x08005E84`, the copier
`BuildRoomSwitchStateObjectTable_candidate` calls per chain) is a
straight byte-for-byte copy loop driven by the same
`g_abRoomScriptOpcodeLengths` table, with no transformation -- so a
chain's bytes can be read and disassembled directly from the ROM
without emulating anything.

Unlike `battle_scripts.md`'s VM, there is no single global pointer
table -- each room's chains live inside that room's own resource blob
(`RoomTableEntry+0x50`, see [`levels.md`](levels.md)), reached through
the same header `ParseRoomResourceBlob_candidate` walks (see
[`rooms.md`](rooms.md)):

```
pSub          = blob + u16(blob + 0)
variantIndex  = u8(pSub + 1 + questStage)         -- questStage = g_abQuestEventState[0]
subBlock      = blob + u16(pSub + variantIndex*8 + 0x24)
switchTable   = subBlock + u16(subBlock + 2)
chainCount    = u8(switchTable + 0)
chain[i]      = switchTable + u16(switchTable + 2 + i*2)
```

`tools/room_scripts/extract_room_scripts.py` (`just extract-room-scripts
[ver]`) walks all 55 rooms' `questStage = 0` (story-start) variant this
way and disassembles every chain it finds -- confirmed against real
content: e.g. the Potions Classroom's `ShowRoomDialog 426 0 0` resolves,
through the dialog-block indirection above plus
[`text.md`](text.md)'s string decoder, to the real in-game exchange
"Hermione, how did you write that up so quickly?" / "Umm... like I
said, I'd read the book before." -- content that fits a Potions
classroom, unlike decoding `426` directly as a string id (a real but
unrelated sentence from elsewhere in the string table -- the failure
mode the dialog-block indirection above exists to document).

Output goes to `data/room_scripts/<ver>/<roomIdx>_<RoomName>/` (room
names from the same dialog-string IDs [`levels.md`](levels.md)
documents), one file per chain -- `chain<N>.txt` by default, or a name
from `tools/room_scripts/script_names.json` (nested `{roomIdx: {chainIdx:
{...}}}`, both as strings, same curated-identification role as
`battle_scripts/script_names.json`,
committed even though `data/room_scripts/` itself is gitignored) --
plus that room directory's own `index.json` (a JSON array of filenames,
position = chain index -- the authority on a chain's table index, so a
file can be renamed without disturbing chain order, mirroring
`data/battle_scripts/index.json`). A curated `script_names.json`
"description" entry is emitted as a leading comment, same round-trip
guarantee (stripped by `parse_chain_text` like any other comment).

Only quest stage `0` is extracted; a room's other quest-stage variants
(different `variantIndex`, a separate chain set live at other points in
the story) aren't enumerated yet -- see "Further work".

Instruction text is `<name> <value> <value> ...`, one instruction per
line, values grouped per opcode according to
`tools/room_scripts/opcodes.json`'s `operand_widths` (default: one
value per raw operand byte; `ShowRoomDialog`'s first two bytes group
into one `u16` dialog block id, matching how the interpreter actually
reads it).

For an opcode with `operand_names` (only the identified ones so far --
see "Known opcodes" above), each value renders as `name:value` instead
of a bare number, and a trailing run of values that match their
declared `operand_defaults` is dropped entirely (parsing fills them
back in) -- e.g. `SetQuestState value:1 index:245` rather than
`SetQuestState 1 245 255 255`. A default is only ever set on a byte
confirmed unread by the handler, or (for `ShowRoomDialog`'s trailing
pair) confirmed always `0` across every extracted script -- never for a
byte the handler reads that merely happens to be constant in the
content seen so far (`room_scripts_codec.py`'s module docstring has the
exact rule). Labels are positional, not just cosmetic: a labeled
token's name is checked against the opcode's real operand order, so a
transposed pair of values fails to parse instead of silently packing
wrong.

`ShowRoomDialog`'s block id also gets a decoded, read-only comment for
every line the block plays (see "The dialog-block indirection" above),
one line per `# "..."` comment immediately preceding the instruction
rather than one crammed trailing comment, e.g.:

```
# "Hermione, how did you write that up so quickly?"
# "Umm... like I said, I'd read the book before."
ShowRoomDialog blockId:426
```

-- generated by `opcodes.json`'s `comment_source` mechanism (currently
the only opcode that has one; `resolve_comment` returns a list of lines
rather than a single string, one per dialog line), ignored on any
future parse step the same way `battle_scripts.md`'s sub-case comments
are.

`tools/room_scripts/pack_room_scripts.py` (`just pack-room-scripts
[ver]`) reads `data/room_scripts/` back and confirms
`encode_chain(parse_chain_text(...))` reproduces the baserom's bytes
exactly for every chain -- a real round-trip check, but **not** a real
pack step yet: it re-derives each chain's address straight from the
baserom rather than emitting build assembly, since the room table isn't
a `regions.<ver>.txt` region yet (see `levels.md`'s "Not yet located")
and so has nowhere to place packed output. Confirmed passing for all
1448 extracted chains.

`tools/room_scripts/opcodes.json` and `room_scripts_codec.py` mirror
`tools/battle_scripts/`'s split exactly (opcode metadata carries no
addresses, same rationale as `battle_scripts.md`'s "Why no addresses in
opcodes.json") -- naming a new opcode means editing `opcodes.json` here,
not the extractor.

## Further work

- Dump each room's other quest-stage variants, not just stage `0` --
  requires enumerating the real quest-stage value range per room (the
  per-quest-stage variant-index array's length isn't confirmed, see
  `rooms.md`'s room-resource-blob section).
- Once the room table itself gets a `regions.<ver>.txt` row (see
  `levels.md`), turn this into a real extract/pack pair with a `data/`
  round-trip, following `battle_scripts.md`'s pipeline as the template.
- Decode and extract the `0x08FAAF10` per-line portrait table -- not
  urgent, but a natural follow-on once dialog blocks are otherwise
  understood.

- Identify the remaining 3 opcodes (see "Known opcodes" above for the
  exact list) -- no systematic pass made yet, only the ones reached
  while tracing the interpreter's own bookkeeping, the handlers
  immediately adjacent to it in memory, and the yield/resume path.
- Confirm `DAT_03001DDC`'s role gating chain `1` at room load (`rooms.md`
  and `InitializeOverworld` both treat it as "has this room's one-time
  chain 1 already run", not independently verified against save state).
- Decode opcode `2`'s `+0x28`/`+0x90` fields against a real object
  struct definition -- not cross-checked against `Object`'s known
  layout from `battle_scripts.md` beyond `+0xc` (shared with the
  battle-script `Object+0xc` flags field: bit `0x82` set by opcode `1`
  overlaps neither of that document's identified bits `0x1`/`0x2`/
  `0x40000`, so still open).
- No extraction pipeline exists for this VM's content yet (`data/`
  round-trip, chain-index-to-purpose table) -- an obvious next step
  once more opcodes are named, following `battle_scripts.md`'s
  pipeline as the template.
