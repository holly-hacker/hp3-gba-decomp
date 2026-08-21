# Object/spell behavior-script bytecode

Status: **PROVEN** for the interpreter, the byte format, and the
script/pointer-table layout (all confirmed live in Ghidra, matched
against `gbadisasm`'s own independent disassembly, plus a built,
byte-exact extraction/pack round-trip -- `just compare us` passes with
the pipeline below wired in). Opcode *semantics* are only worked out for
3 of the ~168 possible opcodes (`End`, `Label`, `StatusEffect`, the
latter with 12 of its own 29 sub-cases named) -- see "What's NOT yet
known".

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
setup (`push`/register spill and a `bl sub_08031748`) done at the real
entry (`0x08018CC0`). Net effect: most case handlers don't return to
their caller after finishing -- they tail into `ContinueObjectScript`,
which loops straight back into the opcode fetch/dispatch. **A single
external call into `InterpretObjectScript` can therefore execute many
opcodes**, not necessarily just one -- it keeps going, opcode after
opcode, until some case actually returns (not yet identified which
ones do) rather than tail-calling onward. This is the real reason
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
| `0x60` | `Label` | 1 (label id) | A branch target marker, consumed by `FindScriptLabelOffset` -- not itself an executable effect. |
| `0x97` | `StatusEffect` | 3 | A sub-dispatch: the first operand byte selects one of 29 cases via `g_apScriptStatusEffectCaseTable` (US `0x0801A650`, `code*[29]`, sub-cases `0x00`-`0x1C`). This is the opcode battle status effects (`BattleFighter.bStatusFlags` bits, extra-XP tracking, etc.) run through -- **see `../memory-map/battle.md` for the full case-by-case writeup**, not duplicated here. It's the only opcode confirmed (so far) to build its own internal jump table -- see "Is `StatusEffect` unique?" below. |

`StatusEffect`'s sub-cases, matched against
`g_apScriptStatusEffectCaseTable`'s real entries (see "A `battle.md`
address to fix" below for one discrepancy between the two docs):

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
(its hex value) in the extracted data -- see "What's NOT yet known".

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

### A `battle.md` address to fix

`../memory-map/battle.md`'s "`0x02` status-flags bits" section's
`Poisoned` bullet cites `0x0801A856` for sub-case `5`, but that address
is actually sub-case `0x16`'s entry (part of the `Paralyze` cluster,
matching this table's `Paralyze_4`). Sub-case `5`'s real entry is
`0x0801A71C`, whose code matches the bullet's own functional description
(`bStatusFlags & 0x06` gate, `field_0x14a8 = 3`, `FUN_0801B590` VFX call)
exactly -- so the case number and the described behavior both check
out, just not that address. Not fixed in `battle.md` itself -- for you
to confirm/fix there.

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

- **Opcode semantics beyond `End`/`Label`/`StatusEffect`.** 111 of the
  114 opcodes actually used across the 65 scripts are still just
  `opcode_XX`, and `StatusEffect` itself still has 17 of 29 sub-cases
  unnamed. Working these out means reading each of the 168 case
  handlers inside `InterpretObjectScript`; the codec/extraction tooling
  above is designed so that filling names in incrementally (via
  `opcodes.json`) is cheap.
- **Which case(s) actually return** from `InterpretObjectScript` rather
  than tail-calling `ContinueObjectScript` -- i.e. what ends a tick's
  worth of script execution. Not identified.
- **Operand semantics.** Even for named opcodes, individual operand
  bytes aren't broken out into named sub-fields (e.g. `StatusEffect`'s
  2nd/3rd operand bytes, which look related to the `field_0x14a8`
  message-announcement mechanism documented in `../memory-map/battle.md`,
  are just raw bytes here).
- **Control-flow opcodes.** `FindScriptLabelOffset` clearly exists to
  support branching, but which opcode(s) actually call it and jump
  `wScriptPC` to the result haven't been identified.
- **The `battle.md` address fix** noted above (`Poisoned`'s cited
  `0x0801A856` vs. the real `0x0801A71C`) -- not fixed there yet.
- **Whether any script content differs between US/JP** -- not checked;
  `regions.jp.txt` has no `objscript-table` row yet.

## Future work

- **Reverse-engineer the remaining opcode handlers.** 111 of 114
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
