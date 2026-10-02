# Room script bytecode

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

Status: **STRUCTURAL MATCH** for the interpreter, the state machine, and
the byte format (read directly from disassembly and cross-checked
between the two entry points below); 91 of 93 opcodes named
(`0x02` and `0x2A` are not). This is the VM [`rooms.md`](rooms.md) calls "room
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
to a `u32`-aligned 96 bytes; C in `src/room/room_script_opcode_lengths.c`,
opcode enum and `RS_*` record macros in `include/overworld/room_script_bytecode.h`): gives each opcode's *total* record length
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

## Opcodes

Each opcode's operand layout is its `RS_*` macro in
`include/overworld/room_script_bytecode.h` (`enum RoomScriptOpcode` gives the
names and numbers), and its behavior is the handler in
`src/room/opcodes/room_script_op_*.c`, dispatched through
`g_apRoomScriptOpcodeHandlers`. Behavior notes live as comments next to those
handlers. Opcode `0x10` (`QueueTileObjectMove`, US `0x0801BF58`) is still
assembly; its camera effect is described in
[`../memory-map/frame_systems.md`](../memory-map/frame_systems.md).

### The row gate (`ShouldRunRoomScriptRow_candidate`)

**PROVEN**, worked out with a truth table rather than by inspection
(the boolean expression reads deceptively like "`n == 0` is the normal
case"). `ShouldRunRoomScriptRow_candidate(n)` (US `0x08005B44`) is:

| `n` | Result |
|---|---|
| `0` | always `false` |
| `1` | `true` only if `g_wRoomResourceFlags_candidate` (`DAT_03001DDC`) bit `0` is clear |
| `>= 2` | always `true` |

Every real script's `InvokeChainIfEnabled` (`0x40`) passes `n = 0` for
this gate, so its `RespawnRoomObjectsInRow_candidate` call (US
`0x0800539C`) is dead in every shipped instance -- see `RoomScriptOpInvokeChainIfEnabled`
above.
`GotoIfQuestStateCompare`/`GotoIfStoryStageCompare` pass real,
often-nonzero row values here instead, so the same gate is genuinely
exercised for those two. This gate is **unrelated** to
`InitializeOverworld`'s own chain-`0`/chain-`1` room-load logic
(`WalkRoomSwitchStateChain_candidate(0, 0)` unconditionally, chain `1`
only if `DAT_03001DDC` bit `0` is *set*) -- that code never calls
`ShouldRunRoomScriptRow_candidate` at all; it's a separate, direct code path that happens
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
off; the decoded `@ "..."` comments above `ShowRoomDialog` records in
`asm/room/blobs/` come from the two-level lookup above, not a direct
`decode_dialog_text(426)` call).

A second table at `0x08FAAF10` (same 8-byte stride, but indexed by the
resolved per-line string id -- `DAT_03002ED8` above -- not the block
id) is read by `FUN_0801F96C` into `DAT_03002EDC` on every line;
candidate: a per-message portrait pointer list, since `ShowRoomDialog`'s
own trailing operand bytes are unused padding (see the `ShowRoomDialog` macro in `asm/room_script.inc`), leaving this as the only other portrait-shaped candidate found
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

## Chains in C

**PROVEN** the on-ROM chain format is byte-identical to the RAM format
above: `sub_08005E84` (US `0x08005E84`, the copier
`BuildRoomSwitchStateObjectTable_candidate` calls per chain, up to and
including the opcode-0 terminator) is a
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

**PROVEN** (`BuildRoomSwitchStateObjectTable_candidate`): the runtime table
`g_pRoomSwitchStateObjectTable` is `{u16 count, u16 offsets[count]}` followed
by the chains. Sub-block flags bit 0 (set in every shipped sub-block) makes
the builder put the *default* sub-block's (entry 0's) chain 0 first and
shift the variant's chains up by one: `count = chainCount + 1`, runtime
chain 0 is the default's chain 0, and runtime chain `i + 1` is the variant's
chain `i`. The chain indices scripts use (`WalkRoomSwitchStateChain_candidate`,
`goto` operands) are runtime indices. The C chain names below use the
variant's own index `N`, one lower than the runtime index. Blob layout and extent proof:
[`rooms.md`](rooms.md).

**PROVEN** (`just compare us`/`jp` pass). Every chain of every variant of all
55 rooms (127 switch tables, 1685 unique chains) is assembly in the room's blob
source, `asm/room/blobs/<room_name>.s`, with room names from the string table:

- One `asm-file` row per room (`Room<RR>Blob`) covers the whole blob, see
  [`rooms.md`](rooms.md). A chain is a label (`Room<RR>V<V>Chain<N>`, or
  `Room<RR><Name>` for the curated names such as `Room25TalkMalfoy`) followed by
  one macro line per record, in the macros of `asm/room_script.inc` (one per
  opcode, taking named operands). `V` is the variant entry (0 = default) and
  `N` the chain's index in that table. Decoded dialog lines are `@` comments
  above `ShowRoomDialog`.
- `g_abRoomScriptOpcodeLengths` is in `src/room/room_script_opcode_lengths.c`.

Scripts are byte-identical between US and JP except five chains: room 7
variant 2, room 15 variant 1, room 22 variant 1, room 23 variant 1 and room 47
variant 1 (one chain each), which differ by a few records and use
`.ifdef VERSION_JP`. JP's room table is `0x08063C18`, with the same blob
layout as US.

## Further work

- Decode and extract the `0x08FAAF10` per-line portrait table -- not
  urgent, but a natural follow-on once dialog blocks are otherwise
  understood.

- Identify the remaining 2 opcodes (`0x02` and `0x2A`, see "Opcodes"
  above) -- no systematic pass made yet, only the ones reached
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
