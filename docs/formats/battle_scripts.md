# Battle-script bytecode

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

Status: **PROVEN** for the interpreter, the byte format, and the
script/pointer-table layout (all confirmed live in Ghidra, matched
against `gbadisasm`'s own independent disassembly, plus a built,
byte-exact extraction/pack round-trip -- `just compare us` passes with
the pipeline below wired in). Opcode *semantics* are worked out for 44 of
the ~168 possible opcodes (`End`, `Label`, `StatusEffect` with all 29 of its
own sub-cases named, the 3-opcode `Wait` family, `MoveTo`, `SetObjectAnim`,
`PlaySound`, `SpawnEffect`/`SpawnEffectDetached`, `ToggleObjectFlipX`,
`TeleportToSlotPosition`, `ClearObjectFlag1`, `SetObjectFlag1`,
`SetAllEnemiesFlagBits`/`SetAllAlliesFlagBits`, `JitterPosition`, `Goto`,
`TeleportTo`, `ShowCannedDialogBlock`, `SetBgPriority`,
`PlaySoundOrDefault`, `DarkenScreenPalette`, `RestoreScreenPalette`,
`GrantMonsterKillReward`, the
`GotoIfFighterRosterMatches` pair, `MoveFighterTo`/`MoveFighterToSlotPosition`,
plus 14 opcodes forming the
`Local`-prefixed family below -- see "The Wait family" and "The
script-local bytes"), 40 of which are actually exercised by the 65 real
scripts -- see "What's NOT yet known".

## What this is

A bytecode VM that drives per-`Object` behavior scripts, reached via
`TickObject`'s generic callback dispatch for any object whose
tick callback happens to be the script interpreter.

**Battle-only, structurally.** `CreateEffectScriptObject` (`0x08018BE0`)
is the only function that points a new object's `pfnTick` at
`InterpretObjectScript`, and it directly indexes `g_pFightState->
pFighters[...]`. Its only caller, `TriggerBattleEffect` (`0x08018B70`),
is called exclusively from the documented battle range `0x08015000`-
`0x08018000` (`RollMonsterSpecialEffect`, `ExecutePlayerAttackSequence`,
`ResolvePlayerAttack`; see
[`../memory-map/battle.md`](../memory-map/battle.md)). The only other
xrefs to the interpreter's entry address are `WaitFramesTick`/
`WaitForCounterTick`/`WaitForFieldClearTick` restoring `pfnTick` on an
already-running script object, not new spawns. Consistent with
`data/battle_scripts/`'s 65 effects all reading as combat content (spells,
monster attacks, `SpecialHarry`/`SpecialRon` abilities). Static xref
trace, exhaustive for direct references but not a runtime trace -- see
`docs/README.md`'s confidence-key legend. Status-effect opcode `0x97`
is one in-battle consumer among the rest.

## The interpreter

**`InterpretObjectScript`** (US `0x08018CC0`-`0x0801ADF9`, Thumb,
~6.9KB) is **one function**, reached via `Object+0x98` (field
`pfnTick`), a generic per-tick callback pointer set by `FUN_08018be0`
(US `0x08018BE0`) when it spawns a script object
(`Object+0x62 = effectId`, `Object+0x98 = InterpretObjectScript`).
`TickObject` calls that pointer every tick.

Before its first opcode fetch, the real entry (`0x08018CC0`) also sets up
two registers held for the rest of the call: `r8` and `sl` (`r10`), each
`*(0x030024E8)[4] + slotByte*72` -- i.e. an entry in what's structurally
a `BattleFighter fighters[]` array (72-byte stride), indexed by one of
two adjacent global bytes (`0x03002750+0x22` for `r8`, `+0x23` for `sl`).
CONFIRMED via `TriggerBattleEffect`'s raw disassembly (`0x08018B70`):
`0x03002750+0x23` (`sl`) is `g_bEffectCasterIndex`, `+0x22` (`r8`) is
`g_bEffectTargetIndex` -- `sl` is the caster/active fighter, `r8` the
target. Consumed by at least two opcodes: `MoveTo`'s
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
   `wScriptPC`'s low byte (`Object+0x60`) is reused for an unrelated purpose
   once script execution for that object finishes: the same byte is what
   `TickPlayerActionState` and `TickFighterAttackAnimState_candidate`
   read/write as a small attack-outcome state counter (see `opcode_30` below
   and [`../memory-map/battle-ui.md`](../memory-map/battle-ui.md)'s
   `TickPlayerActionState` writeup) -- a real, storage-reuse
   overlap confirmed from both sides, not a struct-offset error.
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
`tools/battle_scripts/opcodes.json` or `data/battle_scripts/`, see "Why no addresses
in opcodes.json" below:

| Opcode | Name | Operand bytes | Meaning |
|---|---|---|---|
| `0x00` | `End` | 0 | Terminates the script. Every one of the 65 scripts' last instruction is `End`, and nothing after it is ever reached -- confirmed by the same walk that validated the length table. |
| `0x01` | `SetObjectAnim` | 2 (table index, frame offset) | Calls `SetObjectAnimData(self, animTable + index*16, frameTable + index*226, frameOffset)` -- `SetObjectAnimData` (US `0x080018D8`) is an already-named function taking exactly this 4-argument shape. `animTable`/`frameTable` are two fixed base addresses (`0x08053E64`/`0x08054FE2`) read from the handler's own literal pool; `index` (operand 0) selects a 16-byte row from the first and a 226-byte row from the second. Handler at US `0x08019016`. Opcode `0x02` (not otherwise investigated) shares nearly identical code immediately after this handler in memory, plus one extra call -- likely a close sibling. |
| `0x06` | `PlaySound` | 1 (sound id) | `PlaySoundById(soundId)` -- a direct, single-argument call to the already-named `PlaySoundById` (US `0x0803FC68`). Handler at US `0x0801ADDC`, placed among the interpreter's tail-shared code rather than near the other low-numbered opcodes' handlers. Also reached by `PlaySoundOrDefault` (`0xA4` below) via a shared branch. |
| `0x08` | `WaitFrames` | 1 (frame count) | Sets `Object+0x8a = frameCount` (u16 target), zeroes `Object+0x80` (u16 elapsed), points `Object.pfnTick` at `WaitFramesTick` (US `0x0801B650`, not discovered by `gbadisasm` -- see "The Wait family" below), and **returns from `InterpretObjectScript`** -- the first case confirmed to actually reach `InterpretObjectScript`'s real epilogue (`0x0801AE04`) instead of tail-calling `ContinueObjectScript`, resolving that open question. Handler dispatch at US `0x08019128`. |
| `0x09` | `WaitForCounter` | 0 | Waits for `Object+0xdc` (an externally-driven byte, not written by this opcode) to advance past its value at the moment this opcode ran, or for `Object+0xc` bit `0x40000` to be set (early abort) -- either condition restores `pfnTick` to `InterpretObjectScript`. Tick handler `WaitForCounterTick` (US `0x0801B684`). Handler dispatch at US `0x0801914C`. |
| `0x0A` | `WaitForFieldClear` | 0 | Waits while `Object+0x14` (u16) is nonzero (and at least one tick has elapsed), then restores `pfnTick` **and calls `InterpretObjectScript` immediately** (via `ThumbInterworkVeneer_bx_r1`, US `0x0804A2C4` -- see "The Wait family" below) -- unlike its two siblings, this resumes the script the same frame the wait ends. Tick handler `WaitForFieldClearTick` (US `0x0801B6D0`). Handler dispatch at US `0x08019168`. |
| `0x0C` | `MoveTo` | 5 | Computes a target position -- either from a per-fighter-slot table (`0x08053D2A`/`0x08053D38`, the same tables `TeleportToSlotPosition` reads) or from `sub_0801B620`'s query (a small fallback returning one of 3 fixed screen-coordinate pairs, `(0xB0,0x72)`/`(0x30,0x50)`/`(0x40,0x50)`, keyed on global byte `DAT_03002771` -- candidate: a battle-phase/dialog-state indicator, not identified further), offset by two signed operand bytes -- optionally applies a repeated per-generation offset (`bScriptLocalA` iterations of `sub_08001AA8`, gated by operand 4, which forwards to `sub_08001F98(obj, *(r8+4)->animDescriptor+4, ...)` -- i.e. an offset drawn from `r8`'s linked `Object`'s current animation data, see "The interpreter" above for `r8`), then calls `StartObjectMove` (US `0x08001A84`) with the result and operand 2 as the duration. Handler at US `0x08019184`. `WaitForFieldClear` is how a script waits for this to finish -- see "The Wait family" above. |
| `0x0E` | `SpawnEffectDetached` | 1 (effect id) | `CreateEffectScriptObject(effectId, 0)` -- same call `SpawnEffect` (`0x0F`) makes, but with `attachToParent = 0` instead of `1`; what that parameter actually changes in `CreateEffectScriptObject` isn't traced here. Handler at US `0x08019236`. One of exactly 5 opcode handlers that call `CreateEffectScriptObject` (`0x0E`, `0x0F`, `0x11`, `0x13`, `0x16`, confirmed via `get_xrefs_to`; see "The script-local bytes" below for the spawn-time `bScriptLocalA`/`bScriptLocalB` copy-and-increment all 5 trigger) -- the other 3 (`0x11`, `0x13`, `0x16`) aren't individually named yet. |
| `0x0F` | `SpawnEffect` | 1 (effect id) | `CreateEffectScriptObject(effectId, 1)` -- see `SpawnEffectDetached` (`0x0E`) immediately above for the sibling family member and the full 5-opcode spawn family. 155 real-script occurrences, the 3rd most-used opcode overall. `CreateEffectScriptObject` (US `0x08018BE0`) is an already-named function; the returned child `Object*` is passed into the shared spawn-copy tail (US `0x08019320`, not traced further here). Handler at US `0x08019244`. |
| `0x17` | `ToggleObjectFlipX` | 0 | Toggles the running object's horizontal-flip state: `SetObjectFlippedX(self, !IsObjectFlippedX(self))`. Both are already-named functions (US `0x08003708`/`0x08003928`) that branch on `Object+0xD1 & 3` (a rendering-mode selector, `0` = plain sprite, nonzero = a multi-cell/affine object): in plain mode the flip is a single bit (`0x10`) of `Object+0xD3`; in the other mode `SetObjectFlippedX` negates `Object+0xEC` (the object's affine/scale-style X parameter, set up by the same helper `StartOrbitMotion`'s neighbors use for cell placement) and re-issues the affine setup call. Traced end-to-end to a real consumer: `WriteObjectOamCells` (US `0x08002C18`) reads `Object+0xEC` at entry and multiplies it against each sub-cell's stored X-offset to compute that cell's on-screen X position, before handing the result to `QueueOamEntry`/`SubmitOamAttrsNudged` (US `0x0802FFA0`/`0x0802FEAC`), which write it into `g_pOamShadowBuffer` (`0x03003FE8`) -- an 8-byte-stride, double-buffered (`+0x0`/`+0x400`) shadow copy of real GBA OAM, matching hardware OAM's exact size (`128 * 8 = 0x400` bytes). Negating a per-cell X-scale multiplier this way is the standard technique for mirroring a multi-cell/affine sprite horizontally on hardware that has no affine H-flip attribute bit -- confirmed by data flow through to the OAM write, not by watching it render. Handler at US `0x0801934C`. |
| `0x1C` | `TeleportToSlotPosition` | 1 (generation-offset count) | Self-targeted, immediate counterpart to `MoveFighterToSlotPosition` (`0x7B` below): looks up `x`/`y` from the same per-fighter-slot tables (`0x08053D2A`/`0x08053D38`, indexed by the byte at global `0x03002770`), optionally adds a repeated per-generation offset (`operand - 1` iterations of `sub_08001AA8`, gated on `operand != 0` -- the same offset mechanism `MoveTo` uses), then calls `SetObjectPosition(self, x, y)` -- **an immediate teleport, not an animated move**: `SetObjectPosition` (US `0x080019B0`, already named) writes both the current position (`Object+0x2c`/`0x30`) and the previous position (`Object+0x34`/`0x38`) to the same value in one call, so there's no interpolation to animate. Handler at US `0x08019402`. |
| `0x20` | `SetLocal` | 2 (index, value) | `Object.bScriptLocal<index> = value` (see "The script-local bytes" below). Handler at US `0x080194E0`. Unconditional store, no bounds check on `index`. |
| `0x21` | `IncrementLocal` | 1 (index) | `Object.bScriptLocal<index> += 1`. Handler at US `0x080194F4`. **This is a same-object mutation** -- unlike the spawn-time copy (see below), this opcode changes the field on the object that's currently executing, proving the field can change across ticks of one persistent object, not just at spawn. |
| `0x24` | `GotoIfLocalAEqual` | 2 (compare value, label id) | `if (Object.bScriptLocalA == compareValue) goto Label(labelId)`, via the shared tail at `0x0801A3B2` (`FindScriptLabelOffset` + tail-call into `ContinueObjectScript`). Always reads index 0 specifically (offset `0x63` with no operand-driven add) -- unlike `SetLocal`/`IncrementLocal`, none of the 8 comparison opcodes below take an index operand. Handler at US `0x08019538`. |
| `0x26` | `GotoIfLocalANotEqual` | 2 (compare value, label id) | `if (Object.bScriptLocalA != compareValue) goto Label(labelId)` -- the complement of `GotoIfLocalAEqual`. Handler at US `0x08019570`. |
| `0x27` | `GotoIfFighterRosterMatches` | 1 (label id) | `if (r8's linked BattleFighter's roster index (offset 0x01, per battle.md) is 58 or 59) goto Label(labelId)` -- the only two comparison values come from a **fixed engine constant** (`0x08053D28`, 2 bytes: `0x3B`,`0x3A`), not from script data, unlike every `GotoIfLocalA*` opcode. Calls `FindScriptLabelOffset` directly (not via the shared `0x0801A3B2` tail the other 9 `Goto*` opcodes use). Which characters roster indices 58/59 are isn't identified. Handler at US `0x0801958A`. |
| `0x28` | `GotoIfLocalAEqual_2` | 2 | Byte-for-byte identical handler body to `GotoIfLocalAEqual` (`0x24`) -- confirmed by direct comparison, not just similar shape. Handler at US `0x080195B4`. No functional difference found; kept as a separate name only because it's a genuinely separate opcode number/table entry. |
| `0x2A` | `GotoIfLocalANotEqual_2` | 2 | Byte-for-byte identical handler body to `GotoIfLocalANotEqual` (`0x26`). Handler at US `0x080195EC`. |
| `0x2B` | `GotoIfFighterRosterMatches_2` | 1 (label id) | Byte-for-byte identical handler body to `GotoIfFighterRosterMatches` (`0x27`) (register allocation differs -- `r1` vs `r5` for the loop temp -- but the logic is identical). Never used by any of the 65 real scripts. Handler at US `0x08019606`. |
| `0x30` | `opcode_30` | 0 | The single most-used opcode across the 65 real scripts (190 occurrences), but not confidently named -- what it's for isn't known, only its mechanics. Reads `sl`'s linked `BattleFighter`'s `Object` (`*(sl+4)`, via the same `fighters[]` array/72-byte-stride lookup documented in "The interpreter" above), increments a byte at that `Object+0x60` by 1, then mirrors state into the global `FightState` (`*(0x030024E8)`, see [`../memory-map/battle.md`](../memory-map/battle.md)): copies the `*(sl's Object)+0x60` byte (post-increment) into `FightState.field_0x1058`, and latches `*(sl+4)` (the `Object` pointer itself) into `FightState.field_0x1054`, guarded on that field being currently `0` (a "first writer wins" latch). No other effect -- tail-calls `ContinueObjectScript` immediately. Handler at US `0x08019698`. Real scripts call it in tight, `Wait`-free bursts (e.g. `SpellVerdimilliousUno.txt` calls it twice in a row, does other work, then three more times in a row). `TickFighterAttackAnimState_candidate` (US `0x08015608`, the per-tick attack-animation state machine for the currently-attacking fighter) reads and branches on the same `Object+0x60` byte as a small state value (checks against `1`/`2`/`4`) to steer attack-outcome handling, and zeroes `Object+0x60` together with `FightState.field_0x1054`/`field_0x1058` once an attack sequence fully resolves -- all three fields are managed as one unit across the script interpreter and the native attack-animation code -- `sl` is CONFIRMED as the currently-attacking (caster) fighter's own object, see "The interpreter" above. Values `2`/`4` of `Object+0x60` are written directly by that native code (this opcode only ever adds `1`). See [`../memory-map/battle.md`](../memory-map/battle.md)'s `FightState+0x1054`/`+0x1058` section for what happens (or doesn't) to the accumulated value. |
| `0x41` | `StartOrbitMotion` | 2 (index, angle tweak) | Copies a 3-dword `{angleX/Y, velX/Y, radiusX/Y}` row (into `Object+0x54`/`0x58`/`0x5c`) from a table at `0x08053C68` (12-byte stride, selected by operand 0) via `CopyOrbitParamsFromTable` (US `0x08003A20`), then tweaks `angleX` (`Object+0x54`'s low 16 bits) by `Object.bScriptLocalA * operand1` (shifted left 8, 8.8 fixed point) -- staggering each spawned generation's starting angle, e.g. to arrange copies evenly around a ring. Fully resolved: `ApplyObjectOrbitMotion` (US `0x08003980`, called every tick for every object by `TickObjectList`, independent of any opcode) advances `angleX`/`angleY` by `velX`/`velY`, looks up a sine table at `0x0806589C` (`angleX` read with a quarter-turn phase offset, i.e. cosine; `angleY` raw), scales by `radiusX`/`radiusY`, and adds the result into `Object+0x34`/`0x38` (`nXPrev`/`nYPrev`) -- i.e. this opcode **starts a 2D orbital motion** (circular or elliptical, per-axis-configurable) around the object's current position. Handler at US `0x0801990C`. |
| `0x45` | `StartOrbitMotion_2` | 2 | Same computation as `StartOrbitMotion`, but targets a *different* object -- `*(sl+4)+0x54`, i.e. the caster's own linked `Object` rather than the running `Object` itself (see "The interpreter" above for `r8`/`sl`). Handler at US `0x080199E0`. |
| `0x52` | `ClearObjectFlag1` | 0 | `Object.dwUnk_0x0c &= ~1` on the running object itself (`r7`) -- reads the field, clears bit `0x1`, stores back, tail-calls `ContinueObjectScript`. Handler at US `0x08019BE8`. Complementary pair with `SetObjectFlag1` (`0x53`) immediately below it in the case table. Which behavior bit `0x1` of `Object+0xc` actually gates isn't identified -- other known bits of this field are `0x2` (checked at `TickFighterAttackAnimState_candidate`'s entry) and `0x40000` (`WaitForCounter`'s "AnimationDone", see "The Wait family" above); bit `0x1` is distinct from both. |
| `0x53` | `SetObjectFlag1` | 0 | `Object.dwUnk_0x0c \|= 1` on the running object -- the complement of `ClearObjectFlag1` (`0x52`). Handler at US `0x08019BF6`. |
| `0x54` | `opcode_54` | 1 | Sets a 2-bit field (bits `0x0C`, i.e. bits 2-3) of the byte at offset `0xD5` of the *running* `Object` (`r7`) to `(operand & 3) << 2`: `ldrb`, mask off `0x0C`, OR in the shifted operand, `strb` back -- then tail-calls `ContinueObjectScript`. Handler entry at US `0x08019C02`, which tail-jumps directly into `opcode_55`'s own body (both reach the same `adds r3, #0xD5` instruction, just with `r3` pre-loaded from a different source register) -- confirming this is the exact same operation as `0x55`, just targeting `r7` instead of `r8`'s linked `Object`. `Object+0xD5`'s *upper* nibble is a separate, already-documented graphics-cache slot index (see `graphics.md`'s `sub_08030978` note) -- these bits 2-3 don't overlap that nibble, but what they control isn't identified; not confidently named. Real scripts use values `0`, `1`, and `2` across this opcode and its `0x55`/`0x56`/`0x57` siblings (see those rows), so it's a genuine multi-value field, not a boolean flag. |
| `0x55` | `opcode_55` | 1 | Same operation as `opcode_54`, but targets `r8`'s linked `Object` (`*(r8+4)`, see "The interpreter" above) instead of the running object. Handler at US `0x08019C0A`. |
| `0x56` | `SetAllEnemiesFlagBits` | 1 | Broadcast form of `opcode_54`/`opcode_55`: loops over every entry in the `fighters[]` array (`*(0x030024E8)[4]`, 72-byte stride, up to the fighter count read from `FightState`), and for each one whose fighter-type-tag byte (offset `0x00`, per [`../memory-map/battle.md`](../memory-map/battle.md)'s `BattleFighter` layout) equals `0xFF` -- i.e. every *enemy* -- applies the identical `Object+0xD5` bits-2-3 write (skipped if that fighter has no linked `Object`). Handler at US `0x08019C2A`. Which behavior the bits gate is still unidentified, same caveat as `0x54`/`0x55` -- this opcode only pins down *who* it's applied to, not *what* it does. |
| `0x57` | `SetAllAlliesFlagBits` | 1 | Identical loop and bit-write to `SetAllEnemiesFlagBits`, but the fighter-type-tag check is inverted (`!= 0xFF`) -- applies to every *non-enemy* (party) fighter instead. Handler at US `0x08019C8C`, sharing the same body shape as `0x56` one case entry later. Real call sites bracket a screen-darken effect: e.g. `SpecialHarryUltimateMp.txt` sets all enemies/allies to `2` right after `DarkenScreenPalette`, sets just the target fighter (`opcode_55`) to `1`, runs the visual effect, then resets all enemies/allies back to `1` right before `RestoreScreenPalette` -- suggestive of a per-object brightness/palette-variant selector tied to that darken effect, but not traced to an actual reader, so not folded into the name. |
| `0x5B` | `JitterPosition` | 2 (x range, y range) | Adds a random offset to the running object's current position and applies it immediately: `x = Mt19937RandSigned(operand0)`, `y = Mt19937RandSigned(operand1)` (`Mt19937RandSigned`, US `0x0803B47C`, an already-named RNG function returning a signed value in range), added to `Object.nX`/`nY` (`+0x2c`/`0x30`), then passed to `SnapObjectPosition` (US `0x080019A4` -- takes already-shifted 16.16 fixed-point coordinates and writes both the current and previous position fields to the same value, i.e. a teleport with no interpolation, the same primitive `TeleportTo`/`TeleportToSlotPosition` use). Handler at US `0x08019D70`. A screen-space jitter/shake effect. |
| `0x60` | `Label` | 1 (label id) | A branch target marker, consumed by `FindScriptLabelOffset` -- not itself an executable effect. |
| `0x61` | `Goto` | 1 (label id) | Unconditional jump: reads the operand as a label id and branches straight into the shared `0x0801A3B2` tail (`FindScriptLabelOffset` + tail-call into `ContinueObjectScript`) -- the same tail every `GotoIfLocalA*` comparison opcode uses, but with no comparison of its own. Handler at US `0x08019DEA`, just two instructions before the branch. |
| `0x63` | `GotoLocalIndexedLabel` | 8 (index, then up to 7 embedded label ids) | Reads `Object.bScriptLocal<index>`, adds `2`, and uses that as a byte offset into *its own operand bytes* to pick one of several embedded label ids, then jumps to it via the same `0x0801A3B2` tail as the other `Goto*` opcodes. In effect a value-indexed jump table baked directly into the instruction's operands. Handler at US `0x08019DF6`. Real scripts always pass index `0`. |
| `0x7A` | `MoveFighterTo` | 3 (x, y, duration) | Like `MoveTo`, but targets `r8`'s linked `BattleFighter`'s `Object` (`*(r8+4)`, see "The interpreter" above) instead of the running object itself -- confirmed by comparing register allocation directly against `MoveTo`'s handler, which passes `r7` (the running object) to the same `StartObjectMove` call where this opcode passes `r0 = *(r8+4)`. Reads all 3 operand bytes directly as `x`, `y` (each `<<16`, i.e. the operand is the fixed-point integer part) and `duration`, with no offset/lookup/per-generation logic -- calls `StartObjectMove(*(r8+4), x<<16, y<<16, duration)` then tail-calls `ContinueObjectScript`. Handler at US `0x08019FF0`. Both real call sites are `MoveFighterTo 120 80 20` (`SpecialHarryReplenishMp.txt`, `SpecialHarryUltimateMp.txt`) -- `(120,80)` is the GBA's `240x160` screen center, consistent with moving a visual effect object (an MP-restore icon/particle) to mid-screen. |
| `0x7B` | `MoveFighterToSlotPosition` | 1 (duration) | Same target (`*(r8+4)`) and same `StartObjectMove` call as `MoveFighterTo`, but `x`/`y` are looked up rather than given as operands: `x` from the halfword table at `0x08053D2A` (2-byte stride, the same table `MoveTo`'s fallback and `TeleportToSlotPosition` read) and `y` from the byte table at `0x08053D38` (1-byte stride, ditto), both indexed by the byte at global `0x03002770` -- one byte before `DAT_03002771`, `MoveTo`'s "battle-phase/dialog-state indicator" candidate global (see the `MoveTo` row above); not confirmed further, but structurally reads like a companion fighter-slot-index byte in the same small global block. Handler at US `0x08019FFC`. |
| `0x82` | `TeleportTo` | 2 (x, y) | Self-targeted immediate teleport to an absolute position: `SnapObjectPosition(self, x<<16, y<<16)` (see `JitterPosition`, `0x5B` above, for `SnapObjectPosition`). Handler at US `0x0801A240`. The `MoveTo`/`TeleportTo` naming split mirrors `MoveTo`/`MoveFighterTo`: animated-vs-immediate, not self-vs-fighter here -- both this and `MoveTo` target the running object. |
| `0x80` | `ShowCannedDialogBlock` | 1 (block index) | Looks up a pointer and a length byte from two parallel tables (`0x08053B08`, 4-byte stride; `0x08053B14`, 1-byte stride, both indexed by the operand) and calls `QueueScanlineEffectTable` (US `0x080450D4`) with them, so the operand selects a ROM table of `length` 0x10-byte scanline-effect entries; see [`../memory-map/scanline_effects.md`](../memory-map/scanline_effects.md). Handler at US `0x0801A208`. The opcode name predates that finding and needs revisiting; the tables' contents are not decoded. |
| `0x83` | `GrantMonsterKillReward` | 0 | Reads `BattleFighter+1` (a species/monster-id byte) and adds `MonsterTable[speciesId].wRewardXp`/`.wRewardGold` straight into `g_nBattleXpReward`/`g_nBattleGoldReward` -- the same two accumulators `ApplyDamageToFighter` fills on a normal faint (see [`../memory-map/battle.md`](../memory-map/battle.md)'s "XP/reward payout" section), but reached independently of that function. Also zeroes the fighter's current SP (`+8`), sets `+0x48` to `0xFFFF`, sets the fighter's `Object+0x8D`/`+0x80` attack-state bytes, and sets `FightState+0x1494 = 1`. Handler spans US `0x0801A254`-`0x0801A2C3` (Ghidra mis-splits this into two functions at an internal loop branch, `0x0801A29A`; the real boundary is the whole range, confirmed against `full_disasm.s`). The only script using it, `SpecialHarryTempestJinx` ("Blows one opponent off-screen"), calls it right after teleporting a target off-screen -- consistent with granting that monster's normal kill reward to substitute for the on-faint payout a banished (not damaged-to-0) monster would otherwise never trigger. |
| `0x86` | `GotoIfLocalAGreater` | 2 (compare value, label id) | `if (Object.bScriptLocalA > compareValue) goto Label(labelId)` (unsigned `bhi`). Handler at US `0x0801A344`. |
| `0x87` | `GotoIfLocalALess` | 2 (compare value, label id) | `if (Object.bScriptLocalA < compareValue) goto Label(labelId)` (unsigned `blo`). Handler at US `0x0801A35C`. |
| `0x88` | `GotoIfLocalAInRange` | 3 (low, high, label id) | `if (low < Object.bScriptLocalA < high) goto Label(labelId)` (both bounds exclusive). Handler at US `0x0801A374`, shares its final compare-and-jump tail with `0x89`. |
| `0x89` | `GotoIfLocalAOutOfRange` | 3 (low, high, label id) | `if (Object.bScriptLocalA <= low OR Object.bScriptLocalA >= high) goto Label(labelId)` -- the complement of `GotoIfLocalAInRange`. Handler at US `0x0801A394`. |
| `0x8C` | `SetBgPriority` | 2 (bg layer, priority) | Calls `SetBgPriority` (US `0x08007EB8`): updates a per-background shadow-register struct (`&DAT_03001e84 + bgLayer*0x6c`) and writes the result straight into the real hardware register array `(&BG0CNT)[bgLayer]`, setting that background's priority field (bits 0-1) to `priority & 3` -- a real GBA `BGxCNT` priority write, not a script-only side effect. After that call, if `bgLayer == 1` it also stores `priority` into global `0x03002776`, and if `bgLayer == 0` into global `0x03002775` (both globals already referenced elsewhere as small object/battle-state scratch bytes) -- a secondary cache of the last-set priority per layer, not traced to a reader. Handler at US `0x0801A428`. |
| `0x97` | `StatusEffect` | 3 | A sub-dispatch: the first operand byte selects one of 29 cases via `g_apScriptStatusEffectCaseTable` (US `0x0801A650`, `code*[29]`, sub-cases `0x00`-`0x1C`). This is the opcode battle status effects (`BattleFighter.bStatusFlags` bits, extra-XP tracking, etc.) run through -- **see [`../memory-map/battle.md`](../memory-map/battle.md) for the full case-by-case writeup**, not duplicated here. It's the only opcode confirmed (so far) to build its own internal jump table -- see "Is `StatusEffect` unique?" below. |
| `0x99` | `opcode_99` | 0 | Reads global state at `0x03003EF4` (offsets `+0xc`/`+0x4`); if it matches a specific pattern, sets `Object.bScriptLocalA = 3`, otherwise sets it to `sub_080249FC()`'s return value. Handler at US `0x0801AB4A`. Not confidently named -- the global's meaning and `sub_080249FC` aren't identified yet, so this isn't folded into the `Local`-family naming despite writing the same field. |
| `0xA2` | `SetLocalRandom` | 2 (index, max) | `Object.bScriptLocal<index> = Mt19937RandMax(max)` -- `Mt19937RandMax` is a real, already-named Mersenne Twister RNG function. Handler at US `0x0801ADA0`/`0x0801ADA8` (a `sub_08018CF8`-style split: `0x0801ADA8` gets its own `thumb_func_start` in `gbadisasm`'s output only because `0x0801ADA0` falls through into it with no intervening branch, same fallthrough-labeling artifact documented for `InterpretObjectScript` itself above). |
| `0xA4` | `PlaySoundOrDefault` | 1 (sound id) | Reads a halfword at a fixed global address (`0x0300276E`, two bytes before the `0x03002770` slot-index byte `TeleportToSlotPosition`/`MoveFighterToSlotPosition` read -- not otherwise identified); if it's `0`, plays a fixed sound (`PlaySoundById(0x4B)`) and tail-calls `ContinueObjectScript` directly. Otherwise it falls straight through into `PlaySound`'s own handler body (`0x0801ADDC`), playing `PlaySoundById(operand)` instead. Handler at US `0x0801ADC8`. What condition the global tracks isn't identified, only the branch's two outcomes. |
| `0xA5` | `DarkenScreenPalette` | 0 | Calls `DarkenScreenPalette` (US `0x0803C610`): halves every color's brightness in a screen palette buffer (BGR555 `(c & 0x7BDE) >> 1`, the standard channel-safe halving mask) and uploads it via the same palette-DMA-queue mechanism used elsewhere in the engine. Handler at US `0x0801ADE6`. Paired with `RestoreScreenPalette` (`0xA6`) -- a flash/dim visual effect. |
| `0xA6` | `RestoreScreenPalette` | 0 | Calls `RestoreScreenPalette` (US `0x0803D434`): copies the original (undarkened) palette back and re-uploads it, undoing `DarkenScreenPalette` (`0xA5`). Handler at US `0x0801ADEC`. |

`StatusEffect`'s 29 sub-cases are all identified.
[`../memory-map/battle.md`](../memory-map/battle.md)'s "`StatusEffect`
sub-cases" section owns their semantics and the evidence behind each
name; the names below are the ones `tools/battle_scripts/opcodes.json`
resolves, listed here only so a script's text reads without a second
lookup.

| Sub-case | Name | Touches |
|---|---|---|
| `0`, `1`, `0x15` | `SpawnEffectA`, `SpawnEffectB`, `SpawnEffectC` | VFX only |
| `2`, `3`, `0x1B` | `ExtraExpBonus`, `GrantExtraXp`, `ForceItemDrop` | `FightState+0x1480` bits `0x01`/`0x02`/`0x04` |
| `4` | `UnusedWinoutWrite` | `WINOUT` hardware register; unreachable from any real script |
| `5`, `7`, `0xF` | `Poisoned`, `PoisonImmune`, `CurePoison` | `bStatusFlags` bits `0x02`/`0x04` |
| `6` | `AttackWeakened` | `bStatusFlags` bit `0x08` |
| `8`, `9` | `HiddenSecondary`, `HiddenMain` | `bStatusFlags` bit `0x01` |
| `0xA`, `0x11`, `0x12`, `0x16`, `0x17` | `Paralyze25`, `Paralyze99`, `Paralyze80`, `ParalyzeMonster`, `ParalyzeMonsterChance` | `bStatusFlags` bit `0x10`, via `FUN_0801B430` |
| `0xB` | `DefenseBoost` | `bStatusFlags` bit `0x20` |
| `0xC` | `BumpMonsterDocLevel` | `g_abMonsterDocLevel_candidate` (`Informus`'s Folio Bruti write) |
| `0xD`, `0xE` | `SetPostActionFlashFlag`, `ClearPostActionFlashFlag` | `Object.bDrawFlags` bit `0x10` (`ObjectDrawFlagPostActionFlash`); visual only |
| `0x10` | `ToggleUltimateVisual` | anim-data table swap, and grants all spells at max level |
| `0x13` | `SpellPowerBoost` | `bStatusFlags` bit `0x40` |
| `0x14` | `CureAilments` | clears `Poisoned` and `Paralyzed` |
| `0x18` | `PaletteFlash` | VFX only |
| `0x19`, `0x1A` | `ReplenishPartySp`, `ReplenishTargetMp` | `BattleFighter+8`/`+0xA` from `+0x24`/`+0x26` |
| `0x1C` | `Revive` | `ReviveFighter_candidate` |

Both other top-level opcodes and the 14 `Local`-prefixed opcodes are
documented below -- see "What's NOT yet known".

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
execution to whenever `TickObject` next calls that handler and
it decides to swap `pfnTick` back. **None of these three handler
addresses (`0x0801B650`/`0x0801B684`/`0x0801B6D0`) were disassembled by
`gbadisasm`** (real code sitting in what looked like an unclaimed gap --
a genuine false negative, see the memory on disasm vs. Ghidra ground
truth). All three are verified via `disassemble_bytes` and carry Ghidra
functions/plate comments as `WaitFramesTick`, `WaitForCounterTick`,
`WaitForFieldClearTick`.

All three call `TickParticleEmitters` (US `0x08031748`) on entry -- the
same function
`InterpretObjectScript`'s own real entry point calls before its first
opcode fetch. Decompiled and confirmed unrelated to the calling object:
it walks a separate global linked list (`DAT_03005198`) of
struct-configured particle emitters and spawns particles via a large,
Mersenne-Twister-driven function (not itself decoded beyond confirming
its role) -- mandatory per-tick engine housekeeping that happens to be
invoked from these entry points, not something specific to script
objects or to waiting.

All three also unconditionally call `ProcessObjectFlagBehaviors` (US
`0x0801AF68`) every tick regardless of whether the wait condition is met. Decompiled and
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
handlers:
- `WaitFrames` and `WaitForCounter` only ever call `ProcessObjectFlagBehaviors`;
  on completion they just restore `pfnTick` and return, so the script
  actually resumes on the object's *next* regular tick.
- `WaitForFieldClear` is different: on completion it makes an additional,
  explicit call straight into `InterpretObjectScript` (`0x08018CC1`),
  reached through `ThumbInterworkVeneer_bx_r1` (US `0x0804A2C4`, one of a
  family of generic ARMv4T/Thumb interworking trampolines already
  documented in `krawall.md`; its "`param_2`" argument is simply the
  hardcoded `InterpretObjectScript` address). So **`WaitForFieldClear`
  does resume the script in the same frame its wait ends**, unlike its two
  siblings.

The three termination conditions:

- **`WaitFrames`**: `Object+0x80` (elapsed, reset to `0`) reaches
  `Object+0x8a` (target, set to the operand). A plain fixed-frame delay.
- **`WaitForCounter`**: `Object+0xdc` advances past the value it held
  when `WaitForCounter` ran (captured as `Object+0x8a` at setup time,
  reused as the same target field `WaitFrames` uses) -- or `Object+0xc` bit
  `0x40000` gets set, as an early abort. **Both fields' writer is found:
  `AdvanceAnimationCommand`** (US `0x080021F4`), the sprite-animation
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
  `0x08001A84`) sets
  `Object+0x4c`/`0x50` = target X/Y and `Object+0x14` = duration `+ 1`;
  it's general-purpose, called from several battle/fighter-animation
  sites (`FUN_080149C4`, `FUN_080161FE`, `FUN_08032C20`,
  `InitMonsterBattleActor`, `TickFighterAttackAnimState_candidate`) as
  well as from `InterpretObjectScript` itself, via the new opcode
  `MoveTo` (`0x0C`, see the opcode table -- computes a target position
  from either a per-fighter-slot table or a position-query function,
  optionally offset per `bScriptLocalA` generation, then calls
  `StartObjectMove`). `TickObjectMove` (US `0x0800351C`) is the
  counterpart that ticks it
  down: **called directly by `TickObject`**, the generic
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
"generation counter".** `GotoIfLocalANotEqual` and its two spawn-time
producer sites on their own would read as a generation counter; the other
15 opcodes that touch the same bytes are what rule that out -- see below.
Confirmed in Ghidra's `Object` struct (296 bytes total) as
`bScriptLocalA`/`bScriptLocalB` at offsets `0x63`/`0x64`, immediately
after `bScriptEffectId` (`0x62`), inside a larger gap that also holds
other, still-unidentified fields (the struct has no field between `0x65`
and `pfnTick` at `0x98`).

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
  (`CreateEffectScriptObject`, called from exactly 5 opcode handlers --
  `0x0E`, `0x0F`, `0x11`, `0x13`, `0x16`, confirmed via `get_xrefs_to` on
  the function itself; `0x10`, `0x12`, and `0x17` are separate opcodes that
  don't call it -- `0x17` is `ToggleObjectFlipX`, see its row above), both
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
  script (`data/battle_scripts/Effect19.txt`, not committed, see "US only" note
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
   `HiddenMain` sub-case (9, opens its own message box) after a small
   setup block, while a spawned copy jumps past it and applies
   `HiddenSecondary` (8, appends to the box the root cast already opened)
   instead.
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
top of it), which is why the opcodes carry the neutral `Local`-prefixed
names above rather than `Generation`-prefixed ones -- the underlying byte
is a general per-object script variable; auto-incrementing it on spawn is
just the one
piece of interpreter-provided behavior that makes the "root vs. spawned
copy" idiom convenient without an explicit `SetLocal` call.
`bScriptLocalB` is copied/incremented identically at every spawn site,
and no opcode inside `InterpretObjectScript` reads it back -- but
**`ProcessObjectFlagBehaviors`** (US `0x0801AF68`, see "The Wait family"
above) does, three separate ways, all gated by bits of `Object+0x66`
(not itself script-controlled -- no opcode was found writing it, so
presumably set by whatever native code puts an object into one of these
modes in the first place):

- bit `0x40`: passes `bScriptLocalB` straight to `PlaySoundById` (US
  `0x0803FC68`) -- looks up a sound-effect config row, dispatching to a
  fixed or `Mt19937RandMax2`-randomized (up to 7 variants) Krawall sample
  via veneers into IWRAM-installed driver code (`FUN_08049e40`/`FUN_08049e54`).
- bit `0x04`: if `bScriptLocalB != 0`, calls `SetAlphaBlendCoefficients`
  (US `0x0803D350` -- writes the GBA's hardware `BLDALPHA` register
  directly, confirming the
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
future shiftable build would relocate code freely -- a fixed address baked
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
-> `FUN_08018BE0(effectId, ...)` (see [`../memory-map/battle.md`](../memory-map/battle.md)'s "How
the effect-id -> script trace works" for the full spell/card -> effect
id -> script chain).

## The extraction pipeline, built and build-integrated

**PROVEN** (round-trips byte-exact, `just compare us` passes). Mirrors
the Krawall pipeline, with one difference:
the curated source is one plain-text file per script, not a single
JSON blob, and opcode naming lives in its own small JSON file (ISA-level
format knowledge, not game content, so it's committed rather than
gitignored):

- `tools/battle_scripts/opcodes.json` -- **the** opcode table: for each of
  the 168 opcodes, its current `name` (`opcode_XX` until identified) and
  `operand_length`; opcode `0x97` additionally carries a `sub_dispatch`
  object (`{"operand_index": 0, "cases": {sub-case value: name}}`)
  naming `StatusEffect`'s own sub-cases. **Deliberately carries no
  addresses** -- see "Why no addresses in opcodes.json" above. **To name
  a new opcode (or `StatusEffect` sub-case), edit this file.**
- `tools/battle_scripts/script_names.json` -- the per-*script* counterpart:
  keyed by effect id (`"0"`-`"64"`), each entry optionally carries
  `name` (the script's real-world identification, e.g.
  `SpecialHarryPoisonImmunity`) and `description` (a short, single-line
  functional summary, e.g. `"Grants the party poison immunity for one
  encounter."` -- not a citation trail; the real evidence for an
  identification belongs in `docs/memory-map/battle.md`, not here).
  Names are prefixed by category (`Spell`, `SpecialHarry`,
  `SpecialHermione`, ...) so they group sensibly when listed
  alphabetically. Committed, same footing as `opcodes.json` -- curated RE
  knowledge, not extracted content -- even though `data/battle_scripts/` itself
  is gitignored. **To name a newly-identified script, add or edit its
  entry here**, then re-run `just extract-battle-scripts`.
- `tools/battle_scripts/battle_scripts_codec.py` -- loads `opcodes.json` and
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
- `tools/battle_scripts/extract_battle_scripts.py` (`just extract-battle-scripts`) --
  one-time bootstrap, reads `baserom.us.gba`, writes one text file per
  effect id (named from `script_names.json` when that effect id has an
  entry there, else the default `EffectN.txt`) plus
  `data/battle_scripts/index.json` (a JSON array of 65 filenames, position =
  effect id -- see "Renaming a script" below). Gitignored, same footing
  as the baserom, per hard rule 2 -- not regenerated by `just build`,
  meant to be user-editable. Each named script's text also gets a
  leading `# <description>` comment line when `script_names.json`
  supplies one -- purely informational, stripped like any other comment
  by `parse_script_text`, so it never affects the packed bytes.
  Re-running it after naming an opcode in `opcodes.json` or a script in
  `script_names.json` refreshes every script's text/filename accordingly
  (and overwrites the whole directory, including any *hand*-renamed
  files not driven by `script_names.json` -- re-run against a clean
  extraction, not hand-edited content, same caveat as
  `extract_monsters.py`).
- `tools/battle_scripts/pack_battle_scripts.py` (`just pack-battle-scripts`, wired into
  `just build`) -- reads `data/battle_scripts/index.json` plus the
  `battle-script-table` row in `regions.<ver>.txt`, re-encodes each script
  (in `index.json`'s order) with `encode_script`, and emits
  `build/<ver>/battle_scripts/*.s`. Naming an opcode is purely
  cosmetic/annotation -- `parse_script_text` resolves either the curated
  name or the raw `opcode_XX` form to the same opcode number, so it
  never changes `encode_script`'s output and can't affect the build's
  byte-exactness. The pointer table itself is **not** stored in
  `data/battle_scripts/` -- it's fully determined by script order and size, so
  the packer computes and emits it directly, labeled `g_apEffectScripts`
  to match the ROM.
- `regions.us.txt`'s `battle-script-table` row (`0x0805994C`-`0x0805BA7C`)
  and `tools/manifest.py`'s `battle-script-table` directive wire the packed
  output into the build the same way `krawall-module` rows do.

### Renaming a script

The durable way to name a script, once its purpose is identified, is to
add an entry to `tools/battle_scripts/script_names.json` (effect id -> `name`
+ optional `description`) and re-run `just extract-battle-scripts` -- this
is committed and survives every future re-run of the bootstrap, unlike a
plain filesystem rename of a file under `data/battle_scripts/` (which is
gitignored and gets overwritten wholesale next time the bootstrap runs).
`script_names.json` is the actual source of truth for
`data/battle_scripts/index.json`'s filenames; hand-editing `index.json`/renaming
files directly still works for one-off local experimentation, but won't
survive a re-extract.

Whichever way a rename happens, order comes from `index.json`'s array
position, not from the filename or from sorting a directory listing, so
a rename never reshuffles which script lands at which effect id in the
packed `g_apEffectScripts` table. `pack_battle_scripts.py` also uses each
script's file name (minus `.txt`) directly as its assembly label, so the
name must be a valid identifier (letters/digits/underscore, not starting
with a digit) and unique across all 65 entries -- both checked at pack
time.

US only -- content not yet checked against JP.

## What's NOT yet known

- **Opcode semantics beyond the 44 named opcodes.** 74 of the 114
  opcodes actually used across the 65 scripts are still just `opcode_XX`.
  `StatusEffect`'s own 29 sub-cases are all named (see the table
  above). Working the rest out means reading each of the remaining case
  handlers inside `InterpretObjectScript`; the codec/extraction tooling
  above is designed so that filling names in incrementally (via
  `opcodes.json`) is cheap.
- **The `bl`-unwind subtlety around `ContinueObjectScript`.** Which cases
  return from `InterpretObjectScript` is settled: the `Wait` family (see
  "The Wait family" above), the only ones that branch straight to the
  real epilogue (`0x0801AE04`) instead of `ContinueObjectScript`. The
  narrower open question: most case handlers (including e.g.
  `GotoIfLocalANotEqual`'s
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
  message-announcement mechanism documented in [`../memory-map/battle.md`](../memory-map/battle.md),
  are just raw bytes here).
- **Control-flow opcodes.** Fully resolved: `InterpretObjectScript`
  contains exactly 3 direct calls to `FindScriptLabelOffset` in its
  entire body (checked exhaustively by grepping the whole function for
  `bl sub_0801B710`) -- one inside the shared `0x0801A3B2` tail (reached
  by the 8 `GotoIfLocalA*` comparisons and `GotoLocalIndexedLabel`), and
  two standalone ones (`GotoIfFighterRosterMatches`/`_2`, added to the
  opcode table above). No other opcode can jump `wScriptPC`.
- **Whether any script content differs between US/JP** -- not checked;
  `regions.jp.txt` has no `battle-script-table` row yet.

## Future work

- **Reverse-engineer the remaining opcode handlers.** 74 of 114
  used top-level opcodes are still unnamed (`opcode_XX`); `StatusEffect`'s
  29 sub-cases are all named. Each is a real, bounded chunk of work:
  read one handler in `InterpretObjectScript`, name it and its operand
  layout in `tools/battle_scripts/opcodes.json`, re-run `just extract-battle-scripts`
  to refresh `data/battle_scripts/`'s text.
- ~~**Link effect scripts to Harry's Folio Universitas cards.**~~ **Done**
  -- all 16 of Harry's cards are now named and mapped to their effect id
  in `tools/battle_scripts/script_names.json`, via the in-game Card Combo
  Glossary text (`data/text/en_us.json` string ids `1144`-`1175`, a
  16-entry name list immediately followed by a matching 16-entry
  description list) lining up positionally with
  `g_abHarryCardEffectId`'s 16 table entries -- see
  [`../memory-map/battle-ui.md`](../memory-map/battle-ui.md)'s "Harry's 16 Folio
  Universitas cards" for the full table and the corroborating evidence. This also resolved
  the "opponent loses a turn" card (`Snitch`, effect id `47`) and the
  extra-XP card (`Extra EXP`, effect id `14`). "Girding All" (index `7`,
  effect id `35`) remains a partial exception: its script has no
  `StatusEffect` (`0x97`) call at all, unlike every other card, so
  whatever `DefenseBoost`-equivalent mechanism it uses (probably a direct
  write to `BattleFighter+0x2E`, `bDefenseFactorPercent`, rather than the
  `bStatusFlags` bit) is not confirmed -- the effect id 1:1 mapping is
  solid (via card-list position and elimination), but its actual
  in-engine mechanism is not. Effect id `36` (the second
  `DefenseBoost`-applying script) is confirmed to be none of Harry's 16
  cards -- it's simply absent from the real 16-entry table.
