# Object/spell behavior-script bytecode

Status: **PROVEN** for the interpreter, the byte format, and the
script/pointer-table layout (all confirmed live in Ghidra, matched
against `gbadisasm`'s own independent disassembly, plus a built,
byte-exact extraction/pack round-trip -- `just compare us` passes with
the pipeline below wired in). Opcode *semantics* are worked out for 23 of
the ~168 possible opcodes (`End`, `Label`, `StatusEffect` with 12 of its
own 29 sub-cases named, the 3-opcode `Wait` family, `MoveTo`, the
`GotoIfFighterRosterMatches` pair, plus 14 opcodes forming the
`Local`-prefixed family below -- see "The Wait family" and "The
script-local bytes"), 19 of which are actually exercised by the 65 real
scripts -- see "What's NOT yet known".

## What this is

A small, generic bytecode VM that drives per-`Object` behavior scripts.
It is not battle-specific: it's the same engine `TickObject_candidate`'s
callback dispatch reaches for any object whose tick callback happens to
be the script interpreter. Battle status effects
(`BattleFighter.bStatusFlags`, see `../memory-map/battle.md`) are just
one consumer of it, via opcode `0x97`.

## The interpreter

**`InterpretObjectScript`** (US `0x08018CC0`-`0x0801ADF9`, Thumb,
~6.9KB) is **one function**, reached via `Object+0x98` (field
`pfnTick`), a generic per-tick callback pointer set by `FUN_08018be0`
(US `0x08018BE0`) when it spawns a script object
(`Object+0x62 = effectId`, `Object+0x98 = InterpretObjectScript`).
`TickObject_candidate` calls that pointer every tick.

Before its first opcode fetch, the real entry (`0x08018CC0`) also sets up
two registers held for the rest of the call: `r8` and `sl` (`r10`), each
`*(0x030024E8)[4] + slotByte*72` -- i.e. an entry in what's structurally
a `BattleFighter fighters[]` array (72-byte stride), indexed by one of
two adjacent global bytes (`0x03002750+0x22` for `r8`, `+0x23` for `sl`).
Not otherwise documented in `../memory-map/battle.md`; which fighter role
(attacker/defender, caster/target) each corresponds to isn't confirmed,
just that they're two distinct fighter slots available throughout the
whole opcode dispatch. Consumed by at least two opcodes: `MoveTo`'s
per-generation offset loop reads `*(r8+4)` (that fighter's linked
`Object`), and `StartOrbitMotion_2` writes into `*(sl+4)+0x54` (a
*different* fighter's linked `Object`) -- see both in the opcode table
below.

There is no `bx`/return between `0x08018CC0` and `0x08018CF8` --
`0x08018CF8` is a `bl`-free fallthrough continuation of the same
routine, not a separate function, and `gbadisasm`'s own independent
disassembly agrees: with no seed forcing a split there, it doesn't
introduce one. `0x08018CF8` does still get its own `thumb_func_start`
label in `gbadisasm`'s output, but only because a *different* address
(`ContinueObjectScript`, see below) genuinely `bl`s into it as a second
entry point -- see "The tick-vs-continue split" below.

Per opcode:

1. Reads the opcode byte from `g_apEffectScripts[obj->bScriptEffectId]`
   at offset `obj->wScriptPC` (`Object` fields `0x62`/`0x60`).
2. Copies the opcode byte plus its operand bytes (count from
   `g_abScriptOpcodeLengths`, see below) into a stack buffer.
3. Advances `obj->wScriptPC` past the instruction.
4. Bounds-checks the opcode against `0xA7`; opcodes above that go to
   `ContinueObjectScript` (US `0x0801ADFA`).
5. Dispatches via `g_apScriptOpcodeCaseTable` (US `0x08018D64`, `code*[168]`,
   entries `0x00`-`0xA7`) -- a computed jump, **not** separate
   functions. All 168 targets are labels inside `InterpretObjectScript`
   itself, and `gbadisasm` confirms this independently: its output
   emits the table as real, labeled data (`_08018D64: @ jump table`,
   each entry commented `@ case N`), not raw undecoded bytes -- so there
   is no set of ~168 "handler functions" to mark individually the way
   e.g. Krawall's driver functions were.

### The tick-vs-continue split

**`ContinueObjectScript`** (US `0x0801ADFA`-`0x0801AE03`, 10 bytes) is a
genuinely separate function -- confirmed both by Ghidra's function
manager and by ~130 real `bl`/`b` case sites across
`InterpretObjectScript` that call into it, plus a couple of unused
opcodes (`0x14`/`0x15`) whose table entries point straight at it with no
other work. After a no-op `cmp`/`bne` (always false -- looks like dead
code left over from compilation, not consumed further), it tail-calls
`bl 0x08018CF8` -- **the middle of `InterpretObjectScript`**, right at
the opcode-fetch point, deliberately *skipping* the one-time per-call
setup (`push`/register spill and a `bl TickParticleEmitters`) done at the real
entry (`0x08018CC0`). Net effect: most case handlers don't return to
their caller after finishing -- they tail into `ContinueObjectScript`,
which loops straight back into the opcode fetch/dispatch. **A single
external call into `InterpretObjectScript` can therefore execute many
opcodes**, not necessarily just one -- it keeps going, opcode after
opcode, until some case actually returns (the `Wait` family -- see "The
Wait family" below) rather than tail-calling onward. This is the real reason
`0x08018CF8` shows up as its own `gbadisasm` label: not because it's a
distinct top-level function, but because it's a second, valid entry
point into the same one.

`FindScriptLabelOffset` (US `0x0801B710`) is the goto/branch-target
resolver: given a label id, it linearly scans the current script for an
`opcode 0x60` (`Label`) instruction whose operand byte matches, and
returns that instruction's offset. This is how a script implements
control flow (conditional/branch opcodes presumably call this and then
set `wScriptPC` to the result -- not traced further, out of scope here).

## The byte format

A script is a flat sequence of instructions with no length prefix and
no end-of-buffer marker beyond `End` (below) terminating control flow --
a script's total byte length is fixed externally, by where the next
script starts (see "The script/pointer table" below).

Each instruction is:

```
opcode : u8
operand_bytes : u8[N]     -- N = g_abScriptOpcodeLengths[opcode]
```

**`g_abScriptOpcodeLengths`** (US `0x08054F34`, `byte[256]`) gives the
*extra* operand-byte count per opcode; total instruction length
(including the opcode byte) is `table[opcode] + 1`. Only indices
`0x00`-`0xA7` are ever read (the interpreter's own bounds check); the
rest of the 256-entry table is unused leftover space. Confirmed by
walking every one of the 65 scripts end-to-end with this table and
finding every walk lands exactly on the next script's start address --
zero mismatches across all 65.

Across the 65 real scripts, **114 distinct opcodes appear** (out of the
168 the dispatch table has room for), and the highest opcode value used
is exactly `0xA7` -- consistent with (not just plausibly matching) the
interpreter's own bounds check.

## Known opcodes

Only a few of the ~168 possible opcodes are semantically identified so
far. Addresses below (`g_apScriptOpcodeCaseTable`'s literal jump
targets, read directly from ROM) are cited here in prose, for
US-ROM-specific reference only -- they are **not** stored anywhere in
`tools/objscript/opcodes.json` or `data/scripts/`, see "Why no addresses
in opcodes.json" below:

| Opcode | Name | Operand bytes | Meaning |
|---|---|---|---|
| `0x00` | `End` | 0 | Terminates the script. Every one of the 65 scripts' last instruction is `End`, and nothing after it is ever reached -- confirmed by the same walk that validated the length table. |
| `0x08` | `WaitFrames` | 1 (frame count) | Sets `Object+0x8a = frameCount` (u16 target), zeroes `Object+0x80` (u16 elapsed), points `Object.pfnTick` at `WaitFramesTick` (US `0x0801B650`, previously undissasembled by `gbadisasm` and unanalyzed in Ghidra -- created and named this session, see "The Wait family" below), and **returns from `InterpretObjectScript`** -- the first case confirmed to actually reach `InterpretObjectScript`'s real epilogue (`0x0801AE04`) instead of tail-calling `ContinueObjectScript`, resolving that open question. Handler dispatch at US `0x08019128`. |
| `0x09` | `WaitForCounter` | 0 | Waits for `Object+0xdc` (an externally-driven byte, not written by this opcode) to advance past its value at the moment this opcode ran, or for `Object+0xc` bit `0x40000` to be set (early abort) -- either condition restores `pfnTick` to `InterpretObjectScript`. Tick handler `WaitForCounterTick` (US `0x0801B684`). Handler dispatch at US `0x0801914C`. |
| `0x0A` | `WaitForFieldClear` | 0 | Waits while `Object+0x14` (u16) is nonzero (and at least one tick has elapsed), then restores `pfnTick` **and calls `InterpretObjectScript` immediately** (via `ThumbInterworkVeneer_bx_r1`, US `0x0804A2C4` -- see "The Wait family" below) -- unlike its two siblings, this resumes the script the same frame the wait ends. Tick handler `WaitForFieldClearTick` (US `0x0801B6D0`). Handler dispatch at US `0x08019168`. |
| `0x0C` | `MoveTo` | 5 | Computes a target position -- either from a per-fighter-slot table (`0x08053D2A`/`0x08053D38`, the same tables `opcode_1C` reads) or from `sub_0801B620`'s query (a small fallback returning one of 3 fixed screen-coordinate pairs, `(0xB0,0x72)`/`(0x30,0x50)`/`(0x40,0x50)`, keyed on global byte `DAT_03002771` -- candidate: a battle-phase/dialog-state indicator, not identified further), offset by two signed operand bytes -- optionally applies a repeated per-generation offset (`bScriptLocalA` iterations of `sub_08001AA8`, gated by operand 4, which forwards to `sub_08001F98(obj, *(r8+4)->animDescriptor+4, ...)` -- i.e. an offset drawn from `r8`'s linked `Object`'s current animation data, see "The interpreter" above for `r8`), then calls `StartObjectMove` (US `0x08001A84`, named this session) with the result and operand 2 as the duration. Handler at US `0x08019184`. `WaitForFieldClear` is how a script waits for this to finish -- see "The Wait family" above. |
| `0x20` | `SetLocal` | 2 (index, value) | `Object.bScriptLocal<index> = value` (see "The script-local bytes" below). Handler at US `0x080194E0`. Unconditional store, no bounds check on `index`. |
| `0x21` | `IncrementLocal` | 1 (index) | `Object.bScriptLocal<index> += 1`. Handler at US `0x080194F4`. **This is a same-object mutation** -- unlike the spawn-time copy (see below), this opcode changes the field on the object that's currently executing, proving the field can change across ticks of one persistent object, not just at spawn. |
| `0x24` | `GotoIfLocalAEqual` | 2 (compare value, label id) | `if (Object.bScriptLocalA == compareValue) goto Label(labelId)`, via the shared tail at `0x0801A3B2` (`FindScriptLabelOffset` + tail-call into `ContinueObjectScript`). Always reads index 0 specifically (offset `0x63` with no operand-driven add) -- unlike `SetLocal`/`IncrementLocal`, none of the 8 comparison opcodes below take an index operand. Handler at US `0x08019538`. |
| `0x26` | `GotoIfLocalANotEqual` | 2 (compare value, label id) | `if (Object.bScriptLocalA != compareValue) goto Label(labelId)` -- the complement of `GotoIfLocalAEqual`. Handler at US `0x08019570`. |
| `0x27` | `GotoIfFighterRosterMatches` | 1 (label id) | `if (r8's linked BattleFighter's roster index (offset 0x01, per battle.md) is 58 or 59) goto Label(labelId)` -- the only two comparison values come from a **fixed engine constant** (`0x08053D28`, 2 bytes: `0x3B`,`0x3A`), not from script data, unlike every `GotoIfLocalA*` opcode. Calls `FindScriptLabelOffset` directly (not via the shared `0x0801A3B2` tail the other 9 `Goto*` opcodes use). Which characters roster indices 58/59 are isn't identified. Handler at US `0x0801958A`. |
| `0x28` | `GotoIfLocalAEqual_2` | 2 | Byte-for-byte identical handler body to `GotoIfLocalAEqual` (`0x24`) -- confirmed by direct comparison, not just similar shape. Handler at US `0x080195B4`. No functional difference found; kept as a separate name only because it's a genuinely separate opcode number/table entry. |
| `0x2A` | `GotoIfLocalANotEqual_2` | 2 | Byte-for-byte identical handler body to `GotoIfLocalANotEqual` (`0x26`). Handler at US `0x080195EC`. |
| `0x2B` | `GotoIfFighterRosterMatches_2` | 1 (label id) | Byte-for-byte identical handler body to `GotoIfFighterRosterMatches` (`0x27`) (register allocation differs -- `r1` vs `r5` for the loop temp -- but the logic is identical). Never used by any of the 65 real scripts. Handler at US `0x08019606`. |
| `0x41` | `StartOrbitMotion` | 2 (index, angle tweak) | Copies a 3-dword `{angleX/Y, velX/Y, radiusX/Y}` row (into `Object+0x54`/`0x58`/`0x5c`) from a table at `0x08053C68` (12-byte stride, selected by operand 0) via `CopyOrbitParamsFromTable` (US `0x08003A20`, named this session, previously `FUN_08003a20`), then tweaks `angleX` (`Object+0x54`'s low 16 bits) by `Object.bScriptLocalA * operand1` (shifted left 8, 8.8 fixed point) -- staggering each spawned generation's starting angle, e.g. to arrange copies evenly around a ring. **Fully resolved this session** (previously `AddLocalScaledOffset`, then `SetVectorFromTable` after the table-copy correction): `ApplyObjectOrbitMotion` (US `0x08003980`, named this session, called every tick for every object by `TickObjectList_candidate`, independent of any opcode) advances `angleX`/`angleY` by `velX`/`velY`, looks up a sine table at `0x0806589C` (`angleX` read with a quarter-turn phase offset, i.e. cosine; `angleY` raw), scales by `radiusX`/`radiusY`, and adds the result into `Object+0x34`/`0x38` (`nXPrev`/`nYPrev`) -- i.e. this opcode **starts a 2D orbital motion** (circular or elliptical, per-axis-configurable) around the object's current position. Handler at US `0x0801990C`. |
| `0x45` | `StartOrbitMotion_2` | 2 | Same computation as `StartOrbitMotion`, but targets a *different* object -- `*(sl+4)+0x54`, i.e. `sl`'s linked `Object` rather than the running `Object` itself (see "The interpreter" above for `r8`/`sl`) -- which fighter role `sl` is isn't confirmed. Handler at US `0x080199E0`. |
| `0x60` | `Label` | 1 (label id) | A branch target marker, consumed by `FindScriptLabelOffset` -- not itself an executable effect. |
| `0x63` | `GotoLocalIndexedLabel` | 8 (index, then up to 7 embedded label ids) | Reads `Object.bScriptLocal<index>`, adds `2`, and uses that as a byte offset into *its own operand bytes* to pick one of several embedded label ids, then jumps to it via the same `0x0801A3B2` tail as the other `Goto*` opcodes. In effect a value-indexed jump table baked directly into the instruction's operands. Handler at US `0x08019DF6`. Real scripts always pass index `0`. |
| `0x86` | `GotoIfLocalAGreater` | 2 (compare value, label id) | `if (Object.bScriptLocalA > compareValue) goto Label(labelId)` (unsigned `bhi`). Handler at US `0x0801A344`. |
| `0x87` | `GotoIfLocalALess` | 2 (compare value, label id) | `if (Object.bScriptLocalA < compareValue) goto Label(labelId)` (unsigned `blo`). Handler at US `0x0801A35C`. |
| `0x88` | `GotoIfLocalAInRange` | 3 (low, high, label id) | `if (low < Object.bScriptLocalA < high) goto Label(labelId)` (both bounds exclusive). Handler at US `0x0801A374`, shares its final compare-and-jump tail with `0x89`. |
| `0x89` | `GotoIfLocalAOutOfRange` | 3 (low, high, label id) | `if (Object.bScriptLocalA <= low OR Object.bScriptLocalA >= high) goto Label(labelId)` -- the complement of `GotoIfLocalAInRange`. Handler at US `0x0801A394`. |
| `0x97` | `StatusEffect` | 3 | A sub-dispatch: the first operand byte selects one of 29 cases via `g_apScriptStatusEffectCaseTable` (US `0x0801A650`, `code*[29]`, sub-cases `0x00`-`0x1C`). This is the opcode battle status effects (`BattleFighter.bStatusFlags` bits, extra-XP tracking, etc.) run through -- **see `../memory-map/battle.md` for the full case-by-case writeup**, not duplicated here. It's the only opcode confirmed (so far) to build its own internal jump table -- see "Is `StatusEffect` unique?" below. |
| `0x99` | `opcode_99` | 0 | Reads global state at `0x03003EF4` (offsets `+0xc`/`+0x4`); if it matches a specific pattern, sets `Object.bScriptLocalA = 3`, otherwise sets it to `sub_080249FC()`'s return value. Handler at US `0x0801AB4A`. Not confidently named -- the global's meaning and `sub_080249FC` aren't identified yet, so this isn't folded into the `Local`-family naming despite writing the same field. |
| `0xA2` | `SetLocalRandom` | 2 (index, max) | `Object.bScriptLocal<index> = Mt19937RandMax(max)` -- `Mt19937RandMax` is a real, already-named Mersenne Twister RNG function. Handler at US `0x0801ADA0`/`0x0801ADA8` (a `sub_08018CF8`-style split: `0x0801ADA8` gets its own `thumb_func_start` in `gbadisasm`'s output only because `0x0801ADA0` falls through into it with no intervening branch, same fallthrough-labeling artifact documented for `InterpretObjectScript` itself above). |

`StatusEffect`'s sub-cases, matched against
`g_apScriptStatusEffectCaseTable`'s real entries (an address discrepancy
this cross-check found in `../memory-map/battle.md`'s `Poisoned` bullet,
`0x0801A856` vs. the real `0x0801A71C`, has been fixed there):

| Sub-case | Name | Notes |
|---|---|---|
| `3` | `GrantExtraXp` | `field_0x1480`, not `bStatusFlags` |
| `5` | `Poisoned` | |
| `6` | `AttackWeakened` | also ORs an unrelated `0x10` bit into a *different* byte first -- not `bStatusFlags`, not yet identified |
| `7` | `PoisonImmune` | |
| `8`, `9` | `Hidden`, `Hidden_2` | same bit, `ShowBattleMessage` arg differs |
| `0xA` | `Paralyze` | via `FUN_0801B430` |
| `0xB` | `DefenseBoost` | |
| `0x11`, `0x12` | `Paralyze_2`, `Paralyze_3` | also via `FUN_0801B430` |
| `0x13` | `SpellPowerBoost` | |
| `0x16` | `Paralyze_4` | also via `FUN_0801B430`, operand-driven duration (not a fixed constant like the others) |

Everything else -- both other top-level opcodes and `StatusEffect`'s
remaining 17 sub-cases -- is currently just `opcode_XX`/`sub_case_XX`
(its hex value) in the extracted data, with the exception of the 14
`Local`-prefixed opcodes documented below -- see "What's NOT yet known".

### The Wait family, and how `InterpretObjectScript` actually returns

`WaitFrames`/`WaitForCounter`/`WaitForFieldClear` (`0x08`-`0x0A`) are the only
three opcodes confirmed to reach `InterpretObjectScript`'s real epilogue
(`0x0801AE04`: pop registers, `bx lr`) instead of tail-calling
`ContinueObjectScript`. `ContinueObjectScript` itself can't reach that
epilogue in practice -- the `cmp`/`bne` guarding it is dead code (always
false, see "The tick-vs-continue split" above), so it unconditionally
loops back into dispatch. The only way out is to branch straight to
`0x0801AE04`, which is exactly what these three opcodes' handlers do.

Each swaps `Object.pfnTick` away from `InterpretObjectScript` to a small
dedicated tick handler, then returns -- deferring further script
execution to whenever `TickObject_candidate` next calls that handler and
it decides to swap `pfnTick` back. **None of these three handler
addresses (`0x0801B650`/`0x0801B684`/`0x0801B6D0`) were disassembled by
`gbadisasm`** (real code sitting in what looked like an unclaimed gap --
a genuine false negative, see the memory on disasm vs. Ghidra ground
truth) **and only two of the three had Ghidra function boundaries**
before this session; `WaitFramesTick` (`0x0801B650`) had none either.
Verified via `disassemble_bytes` (dry-run) before committing, then
created/named/plate-commented in Ghidra as `WaitFramesTick`,
`WaitForCounterTick`, `WaitForFieldClearTick`.

All three call `TickParticleEmitters` (US `0x08031748`, named this
session, previously `FUN_08031748`) on entry -- the same function
`InterpretObjectScript`'s own real entry point calls before its first
opcode fetch. Decompiled and confirmed unrelated to the calling object:
it walks a separate global linked list (`DAT_03005198`) of
struct-configured particle emitters and spawns particles via a large,
Mersenne-Twister-driven function (not itself decoded beyond confirming
its role) -- mandatory per-tick engine housekeeping that happens to be
invoked from these entry points, not something specific to script
objects or to waiting.

All three also unconditionally call `ProcessObjectFlagBehaviors` (US
`0x0801AF68`, named this session, previously `FUN_0801af68`) every tick
regardless of whether the wait condition is met. Decompiled and
confirmed: a bit-flag dispatcher on `Object+0x66` driving several
unrelated per-object behaviors (a jitter/wobble adjustment, two
counter-driven palette-cycle-style calls, a screen-shake-like camera
adjustment, and a counter-driven call into `FUN_08003A80`'s
per-"object kind" dispatch, see "The generation field" era investigation
above for why that dispatch was ruled out as `Object+0x14`'s writer) --
confirmed to have no connection to `Object.pfnTick` or script resumption
at all.

**Whether the wait resumes the script the same frame it completes is not
uniform across the family** -- confirmed by decompiling all three
handlers, correcting an earlier assumption in this doc:
- `WaitFrames` and `WaitForCounter` only ever call `ProcessObjectFlagBehaviors`;
  on completion they just restore `pfnTick` and return, so the script
  actually resumes on the object's *next* regular tick.
- `WaitForFieldClear` is different: on completion it makes an additional,
  explicit call straight into `InterpretObjectScript` (`0x08018CC1`),
  reached through `ThumbInterworkVeneer_bx_r1` (US `0x0804A2C4`, one of a
  family of generic ARMv4T/Thumb interworking trampolines already
  documented in `krawall.md` -- not a mysterious unidentified callback,
  as this doc previously described it; its "`param_2`" argument is simply
  the hardcoded `InterpretObjectScript` address). So **`WaitForFieldClear`
  does resume the script in the same frame its wait ends**, unlike its two
  siblings.

The three termination conditions:

- **`WaitFrames`**: `Object+0x80` (elapsed, reset to `0`) reaches
  `Object+0x8a` (target, set to the operand). A plain fixed-frame delay.
- **`WaitForCounter`**: `Object+0xdc` advances past the value it held
  when `WaitForCounter` ran (captured as `Object+0x8a` at setup time,
  reused as the same target field `WaitFrames` uses) -- or `Object+0xc` bit
  `0x40000` gets set, as an early abort. **Both fields' writer is found:
  `AdvanceAnimationCommand`** (US `0x080021F4`, named/commented this
  session -- previously `FUN_080021f4`), the sprite-animation
  command-stream player reached from the same `sub_080018D8`/
  `sub_0800187C` setup opcode `0x01`/`0x04` drive (`StartOrbitMotion`'s
  neighbors in opcode-number terms only, not otherwise related -- see the
  opcode table). It reads a command stream from
  `Object+0xe4`'s descriptor: bytes `0x00`-`0xEE` are plain "frame,
  duration" pairs, bytes `0xEF`-`0xFF` are 17 control commands via their
  own jump table. Control byte `0xFF`'s case writes the *next* stream
  byte into `Object+0xdc` -- i.e. `WaitForCounter` is concretely **"wait
  for the currently-playing animation's next `0xFF`-tagged event
  marker"**, a synchronization point animation data can place for a
  script to pick up on (e.g. an "impact frame"). Separately, whenever the
  frame-advance logic detects the animation has reached its last frame,
  it sets `Object+0xc`'s `0x40000` bit (**"AnimationDone"**) -- the same
  bit `WaitForCounter`'s early-abort checks, and the same bit several
  battle-code call sites (~`0x080168C0`, `0x08016F0E`, `0x0801780C`, not
  otherwise explored) check-and-clear after an attack, consistent with
  "wait for this object's animation to fully finish" being a shared idiom
  across both scripts and native code, not something scripts invented.
- **`WaitForFieldClear`**: `Object+0x14` (u16) reads as `0` (and at least
  one tick has elapsed), then resumes the script immediately (see above).
  **Writer found: `Object+0x14` is a move-duration counter.**
  `StartObjectMove` (US
  `0x08001A84`, named this session, previously `FUN_08001a84`) sets
  `Object+0x4c`/`0x50` = target X/Y and `Object+0x14` = duration `+ 1`;
  it's general-purpose, called from several battle/fighter-animation
  sites (`FUN_080149C4`, `FUN_080161FE`, `FUN_08032C20`,
  `InitMonsterBattleActor`, `TickFighterAttackAnimState_candidate`) as
  well as from `InterpretObjectScript` itself, via the new opcode
  `MoveTo` (`0x0C`, see the opcode table -- computes a target position
  from either a per-fighter-slot table or a position-query function,
  optionally offset per `bScriptLocalA` generation, then calls
  `StartObjectMove`). `TickObjectMove` (US `0x0800351C`, named this
  session, previously `FUN_0800351c`) is the counterpart that ticks it
  down: **called directly by `TickObject_candidate`**, the generic
  per-object tick loop -- independent of whatever `Object.pfnTick`
  currently is, confirming it keeps running while a script object is
  parked in a `Wait`-family handler. At `0`, it zeroes the velocity
  fields (`Object+0x3c`/`0x40`, the same pair `TickObjectMove`'s sibling
  `sub_080019C0` sets directly). So `WaitForFieldClear` is concretely
  **"wait for this object's current `MoveTo` to finish."**

### The script-local bytes (`Object.bScriptLocalA`/`bScriptLocalB`)

`SetLocal`/`IncrementLocal`/`SetLocalRandom`/`GotoLocalIndexedLabel`'s
`index` operand is `0` for `bScriptLocalA`, `1` for `bScriptLocalB` --
that's the only two values ever seen, see below.

**Two general-purpose per-object script variables, not a dedicated
"generation counter".** This was the working theory after first finding
`GotoIfLocalANotEqual` (then named `GotoIfGenerationNotEqual`) and its two
spawn-time producer sites, but reading the other 15 opcodes that touch the
same bytes overturned it -- see below. Confirmed in Ghidra's `Object`
struct (296 bytes total) as `bScriptLocalA`/`bScriptLocalB` at offsets
`0x63`/`0x64`, immediately after `bScriptEffectId` (`0x62`); previously
undefined bytes in a larger gap that also holds other, still-unidentified
fields (the struct has no field between `0x65` and `pfnTick` at `0x98`).

What's actually confirmed:

- **Only indices `0` and `1` are ever used**, across all opcodes that take
  an explicit index operand (`SetLocal`, `IncrementLocal`,
  `GotoLocalIndexedLabel`, `SetLocalRandom`) and across all 65 scripts --
  checked directly against the extracted script data, not just the
  interpreter code. So despite `SetLocal`'s handler doing no bounds
  check at all (any index byte would be accepted), real content only
  ever addresses these two bytes. That's why the `Object` struct gets two
  named byte fields, not an array.
- **Spawn-time behavior**: when a script spawns a child script-object
  (`FUN_08018BE0`, at 8 opcode sites: `0x0E`-`0x13`, `0x16`, `0x17`), both
  bytes are copied from parent to child, each incremented by one:
  `child.bScriptLocalA = parent.bScriptLocalA + 1`,
  `child.bScriptLocalB = parent.bScriptLocalB + 1`. This alone would make
  `bScriptLocalA` read like a spawn-depth/generation counter (0 for a
  script's root object, 1 for its first-generation spawned children, etc.)
  -- and several scripts do use it exactly that way (see below).
- **But it's also freely read/written by the running object itself**,
  independent of spawning: `SetLocal` stores an arbitrary operand value
  into either byte; `IncrementLocal` increments either byte **on the
  currently-executing object**, not a spawned child -- e.g. effect id 19's
  script (`data/scripts/Effect19.txt`, not committed, see "US only" note
  below) calls `IncrementLocal 0` twice in a row, twice, in its own body,
  well before any spawn happens. `SetLocalRandom` stores a Mersenne
  Twister roll into either byte.
- **`bScriptLocalA` is read back by 8 different comparison opcodes**
  (`GotoIfLocalAEqual`/`_2`, `GotoIfLocalANotEqual`/`_2`, `GotoIfLocalAGreater`,
  `GotoIfLocalALess`, `GotoIfLocalAInRange`, `GotoIfLocalAOutOfRange`) that
  all hardcode index `0` (no operand-driven index, unlike the writer
  opcodes). `bScriptLocalB`'s reader is outside the bytecode dispatch
  entirely -- see below.

Two real, distinct usage patterns for `bScriptLocalA`, both present in the
65 scripts:

1. **Root-only init guard**: `GotoIfLocalANotEqual 0, Label` (or the
   `_2` variant) placed right at the top of a script, comparing against
   `0`. Since only the spawn path increments the field, this reliably
   distinguishes "am I the original cast" from "am I a spawned copy of
   an earlier generation of this same effect" -- confirmed concretely at
   effect id 32: generation `0` falls through and applies `StatusEffect`'s
   `Hidden_2` sub-case (9, the message-announcing variant) after a small
   setup block, while a spawned copy jumps past it and applies plain
   `Hidden` (8, no announcement) instead.
2. **A genuine multi-way state dispatch, unrelated to spawning at all**:
   effect id 19's script opens with ten consecutive `GotoIfLocalAEqual`
   checks -- values `1`-`10` against only four distinct target labels
   (`45`,`46`,`47`,`48`, in a repeating cycle), i.e. `switch (localA) { case
   1: case 5: case 9: goto 45; case 2: case 6: case 10: goto 46; ... }`.
   None of those ten values are reachable through the spawn-increment path
   (that script never calls a spawn opcode with anywhere near that
   generation depth); instead, the default body (reached when `localA==0`,
   i.e. none of the ten match) calls `IncrementLocal 0` on itself
   repeatedly before finishing. This is a same-object tick/step counter
   driving a 4-state cycle -- a real state machine, not a spawn-depth
   check.

So "generation counter" was too narrow a name for the mechanism itself
(it's still an accurate description of *one* convention scripts build on
top of it), which is why the opcode names were revised from the
`Generation`-prefixed ones used earlier in this investigation to the more
neutral `Local`-prefixed names above -- the underlying byte is a general
per-object script variable; auto-incrementing it on spawn is just the one
piece of interpreter-provided behavior that makes the "root vs. spawned
copy" idiom convenient without an explicit `SetLocal` call.
`bScriptLocalB` is copied/incremented identically at every spawn site,
and no opcode inside `InterpretObjectScript` reads it back -- but
**`ProcessObjectFlagBehaviors`** (US `0x0801AF68`, see "The Wait family"
above) does, three separate ways, all gated by bits of `Object+0x66`
(not itself script-controlled -- no opcode was found writing it, so
presumably set by whatever native code puts an object into one of these
modes in the first place):

- bit `0x40`: passes `bScriptLocalB` straight to `ShowMessageById` (US
  `0x0803FC68`, named this session, previously `FUN_0803fc68` -- looks up
  a message/dialog config row, dispatching to a fixed or
  `Mt19937RandMax2`-randomized text variant).
- bit `0x04`: if `bScriptLocalB != 0`, calls `SetAlphaBlendCoefficients`
  (US `0x0803D350`, named this session, previously `FUN_0803d350` --
  writes the GBA's hardware `BLDALPHA` register directly, confirming the
  name) with `(bScriptLocalB, 0x10 - bScriptLocalB)`, then decrements it.
- bit `0x80`: compares `bScriptLocalB` against a threshold at
  `Object+0x6b`; while below it, walks a secondary counter at
  `Object+0x6d` down and calls the same `SetAlphaBlendCoefficients` with
  the operands swapped at each step, also decrementing `bScriptLocalB`.

So **`bScriptLocalB` is concretely a hardware alpha-blend fade step
counter** (`0`-`0x10`, matching `BLDALPHA`'s two coefficients summing to
that range) when the object is in one of these flag-gated modes -- a
fade in/out effect -- and separately a message-id when in the `0x40`
mode. Same pattern as `bScriptLocalA`: one interpreter-provided byte,
multiple context-dependent uses, none of them "generation" as a literal
description.

### Is `StatusEffect` unique?

**Yes -- the only opcode with a real nested sub-dispatch.** The dispatch
to `StatusEffect`'s own 29-entry sub-table is a computed jump (`mov pc,
rX`, preceded by a `lsl`/table-add/`ldr` sequence to compute the
target); that exact instruction sequence appears **exactly twice** in
the whole `InterpretObjectScript` function -- once for the main
168-opcode dispatch, once for `StatusEffect`'s sub-dispatch. No other
opcode builds a second internal jump table off one of its own operand
bytes.

Two opcodes come close but aren't the same pattern -- each re-reads one
of its own operand bytes and branches on it more than once, the same
shape a `cmp`/`beq` chain sub-dispatch would have, but always lands on
trivially similar code rather than distinct behavior:

- **Opcode `0x7F`** (handler `0x0801A158`) reads its 2nd operand byte
  and does a 4-way `cmp` chain (values `0`-`3`) -- but all four targets
  just pick a different string/data pointer before falling into one
  shared tail (`sub_0800A598`). It's a **value selector** (closer to "an
  operand with a 4-value enum domain"), not a dispatch to different
  behavior.
- **Opcode `0x8C`** (handler `0x0801A428`) reads its 1st operand byte
  twice for two `cmp #value` checks, each choosing which of two RAM
  globals (`0x03002775`/`0x03002776`) to store the *other* operand into.
  Same shape -- picking a destination, not branching to different logic.

No other handler re-branches on any operand byte more than once; the
rest use operand bytes purely as data (indices, coordinates, call
arguments, counts). `StatusEffect`'s own sub-dispatch (an operand byte
that's bounds-checked and fed to its own jump table, landing on 26-29
substantively different code bodies) has no equivalent elsewhere --
`0x7F`/`0x8C`'s small value-selector branches are a different, much
shallower pattern that fits better as an enumerated-value note on the
opcode than as an `opcodes.json` `sub_dispatch` entry (not yet added).

### Why no addresses in opcodes.json

Addresses are ROM-build-specific: they differ between the US and JP
ROMs (not confirmed to even share this table's content at all), and a
future shiftable/moddable build (see CLAUDE.md's "Moddability roadmap")
is explicitly meant to relocate code freely -- a fixed address baked
into what's supposed to be portable bytecode format knowledge would
silently break both. `opcodes.json` carries only opcode number, name,
operand length, and (for `StatusEffect`) named sub-cases -- nothing that
a different ROM build could invalidate. Addresses belong only in
Ghidra's database and in this doc's own prose (both already scoped,
like every other doc in this project, as US-ROM-specific facts, not
build inputs).

## The script/pointer table

**`g_apEffectScripts`** (US `0x0805B978`, `void*[65]`): 65 pointers, one
per "effect id", each pointing at one script's first instruction.
Effect id `0`-`64` are all populated and point into a single contiguous
block running from `0x0805994C` up to `g_apEffectScripts` itself, in
ascending order with **zero gaps or padding** between scripts (each
script's end address is exactly the next script's start address, and
the last script's end is exactly `0x0805B978`, the table's own start).
Entries past index `64` diverge wildly (pointers into an unrelated
`0x08A3xxxx` region) and index `64`'s bounds are corroborated by a
`cmp r1, #0x41` (`0x41` = 65) found elsewhere in the disassembly --
consistent with a hard `effectId < 65` bounds check somewhere in the
effect-dispatch path (not traced to a specific call site).

An effect id is resolved to a script via `FUN_08018B70(effectId, ...)`
-> `FUN_08018BE0(effectId, ...)` (see `../memory-map/battle.md`'s "How
the effect-id -> script trace works" for the full spell/card -> effect
id -> script chain).

## The extraction pipeline, built and build-integrated

**PROVEN** (round-trips byte-exact, `just compare us` passes). Mirrors
the Krawall/monster-table pipelines, with one difference from both:
the curated source is one plain-text file per script, not a single
JSON blob, and opcode naming lives in its own small JSON file (ISA-level
format knowledge, not game content, so it's committed rather than
gitignored):

- `tools/objscript/opcodes.json` -- **the** opcode table: for each of
  the 168 opcodes, its current `name` (`opcode_XX` until identified) and
  `operand_length`; opcode `0x97` additionally carries a `sub_dispatch`
  object (`{"operand_index": 0, "cases": {sub-case value: name}}`)
  naming `StatusEffect`'s own sub-cases. **Deliberately carries no
  addresses** -- see "Why no addresses in opcodes.json" above. **To name
  a new opcode (or `StatusEffect` sub-case), edit this file.**
- `tools/objscript/objscript_codec.py` -- loads `opcodes.json` and
  exposes `decode_script`/`encode_script` (raw bytes <-> `(opcode,
  operand_bytes)` pairs) and `format_script_text`/`parse_script_text`
  (that <-> the curated text format, one instruction per line:
  `<name> [operand operand ...]`, decimal operands, e.g.
  `StatusEffect 7 8 0`). `parse_script_text` accepts either a curated
  name or the raw `opcode_XX` form for any opcode, named or not, same as
  a real assembler accepts a raw opcode alongside a mnemonic.
  `format_script_text` also appends a trailing `# <sub-case name>`
  comment on a `StatusEffect` line when its `opcodes.json` sub-case is
  named (e.g. `StatusEffect 7 8 0  # PoisonImmune`) -- purely a
  readability aid; `parse_script_text` strips any trailing `#...` before
  parsing, so hand-written comments round-trip fine too.
- `tools/objscript/objscript_migrate.py` (`just migrate-objscript`) --
  one-time bootstrap, reads `baserom.us.gba`, writes one text file per
  effect id (default name `EffectN.txt`) plus `data/scripts/index.json`
  (a JSON array of 65 filenames, position = effect id -- see "Renaming a
  script" below). Gitignored, same footing as the baserom, per hard rule
  2 -- not regenerated by `just build`, meant to be user-editable.
  Re-running it after naming an opcode in `opcodes.json` refreshes every
  script's text to use the new name (and overwrites the whole directory,
  including any file renames -- re-run against a clean extraction, not
  hand-edited content, same caveat as `monster_migrate.py`).
- `tools/objscript/pack_objscript.py` (`just pack-objscript`, wired into
  `just build`) -- reads `data/scripts/index.json` plus the
  `objscript-table` row in `regions.<ver>.txt`, re-encodes each script
  (in `index.json`'s order) with `encode_script`, and emits
  `build/<ver>/objscript/*.s`. Naming an opcode is purely
  cosmetic/annotation -- `parse_script_text` resolves either the curated
  name or the raw `opcode_XX` form to the same opcode number, so it
  never changes `encode_script`'s output and can't affect the build's
  byte-exactness. The pointer table itself is **not** stored in
  `data/scripts/` -- it's fully determined by script order and size, so
  the packer computes and emits it directly, labeled `g_apEffectScripts`
  to match the ROM.
- `regions.us.txt`'s `objscript-table` row (`0x0805994C`-`0x0805BA7C`)
  and `tools/gen_rom_s.py`'s `objscript-table` directive wire the packed
  output into the stitched build the same way `monster-table` does.

### Renaming a script

A script's file can be renamed to anything once its purpose is
identified (e.g. `Effect18.txt` -> `PoisonImmunityCard.txt`) -- update
its entry in `data/scripts/index.json` to match at the same time. Order
comes from `index.json`'s array position, not from the filename or from
sorting a directory listing, so a rename never reshuffles which script
lands at which effect id in the packed `g_apEffectScripts` table.
`pack_objscript.py` also uses each renamed file's name (minus `.txt`)
directly as its assembly label, so the name must be a valid identifier
(letters/digits/underscore, not starting with a digit) and unique across
all 65 entries -- both checked at pack time.

US only -- content not yet checked against JP.

## What's NOT yet known

- **Opcode semantics beyond the 23 named opcodes.** 95 of the 114
  opcodes actually used across the 65 scripts are still just `opcode_XX`,
  and `StatusEffect` itself still has 17 of 29 sub-cases unnamed. Working
  these out means reading each of the 168 case handlers inside
  `InterpretObjectScript`; the codec/extraction tooling above is designed
  so that filling names in incrementally (via `opcodes.json`) is cheap.
- **The `bl`-unwind subtlety around `ContinueObjectScript`.** Resolved:
  *which* cases return from `InterpretObjectScript` is now known -- the
  `Wait` family (see "The Wait family" above), the only ones that branch
  straight to the real epilogue (`0x0801AE04`) instead of
  `ContinueObjectScript`. What's still open is a narrower question this
  raised: most case handlers (including e.g. `GotoIfLocalANotEqual`'s
  handler and the shared `0x0801A3B2` tail) reach `ContinueObjectScript`
  via `bl`, not `b` -- and since the dispatch itself jumps in via `mov pc,
  r0` without touching `lr`, if `ContinueObjectScript` or its callees ever
  *did* return normally (rather than looping forever via its own
  always-taken `bl sub_08018CF8`), that return would unwind back through
  each such `bl`'s saved return address, landing partway into the *next*
  case's code rather than back at a sensible call site. Since
  `ContinueObjectScript` in practice never returns that way (confirmed:
  its guard is dead code), this may be entirely inert -- not confirmed
  either way.
- **`0x99`'s global-state check and `sub_080249FC`.** The opcode that
  conditionally resets `bScriptLocalA` based on `0x03003EF4`'s contents
  (see the opcode table above) isn't named -- what that global represents
  and what `sub_080249FC` computes aren't known.
- **Why `0x24`/`0x28` (`GotoIfLocalAEqual`/`_2`) and `0x26`/`0x2A`
  (`GotoIfLocalANotEqual`/`_2`) exist as byte-for-byte identical duplicate
  handlers.** No functional or contextual difference found. `0x28`, `0x2A`,
  and `0x88` (`GotoIfLocalAInRange`) are additionally never actually used
  by any of the 65 real scripts, unlike their surviving counterparts.
- **Operand semantics.** Even for named opcodes, individual operand
  bytes aren't broken out into named sub-fields (e.g. `StatusEffect`'s
  2nd/3rd operand bytes, which look related to the `field_0x14a8`
  message-announcement mechanism documented in `../memory-map/battle.md`,
  are just raw bytes here).
- **Control-flow opcodes.** Fully resolved: `InterpretObjectScript`
  contains exactly 3 direct calls to `FindScriptLabelOffset` in its
  entire body (checked exhaustively by grepping the whole function for
  `bl sub_0801B710`) -- one inside the shared `0x0801A3B2` tail (reached
  by the 8 `GotoIfLocalA*` comparisons and `GotoLocalIndexedLabel`), and
  two standalone ones (`GotoIfFighterRosterMatches`/`_2`, added to the
  opcode table above). No other opcode can jump `wScriptPC`.
- **Whether any script content differs between US/JP** -- not checked;
  `regions.jp.txt` has no `objscript-table` row yet.

## Future work

- **Reverse-engineer the remaining opcode handlers.** 95 of 114
  used top-level opcodes and 17 of `StatusEffect`'s 29 sub-cases are
  still unnamed (`opcode_XX`/`sub_case_XX`). Each is a real, bounded
  chunk of work: read one handler in `InterpretObjectScript`, name it
  and its operand layout in `tools/objscript/opcodes.json`, re-run
  `just migrate-objscript` to refresh `data/scripts/`'s text.
- **Link effect scripts to Harry's Folio Universitas cards.**
  `../memory-map/battle.md` maps most of Harry's 16 cards to an effect
  id via `g_abHarryCardEffectId_candidate`, but several remain open: the
  "opponent loses a turn" card (candidate effect id `47`, opcode `0x97`
  sub-case `0x12`/`Paralyze_3`, not confirmed against a specific card
  name), the extra-XP card (candidate effect id `14`, index `11`, not
  confirmed), and "Girding All" (a second `DefenseBoost`-applying script
  at effect id `36` that doesn't match any of the 16 known card slots).
  Naming more of the opcodes above -- particularly whichever one turns
  out to control the per-turn "which move did the player pick" text or
  icon -- is the most likely way to pin these down from the script side
  rather than from battle-message content alone.
