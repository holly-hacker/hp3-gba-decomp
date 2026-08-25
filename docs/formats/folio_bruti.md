# Folio Bruti (in-game bestiary) format

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

**Naming note:** despite this doc's title, `MonsterTable` (`0x0804F410`)
is NOT exclusively Folio Bruti bestiary data -- it's shared by every
`InitMonsterBattleActor` battle participant, bestiary-tracked or not.
Only its first **53** of 69 rows (indices 0-52) are ever shown in the
Folio Bruti grid -- **PROVEN live, see "The grid boundary" below** --
the rest (53-68) are boss/story encounters that never appear there.
Kept the filename/doc title as-is since the table was found and is
still mostly discussed via the Folio Bruti code path, but don't take
"in `MonsterTable`" to imply "shown in the bestiary."

Status: **PROVEN** for the core ask -- the per-monster, per-spell effectiveness
data that drives the 8 spell sliders on the Folio Bruti detail screen is
located, its accessor function is fully understood via a decompiled jump
table, and its result is traced end-to-end into the slider dot's pixel
X-position (and into the animated "?" placeholder branch for
unseen/unanalyzed monsters). The backing monster stat table (HP, base
damage range, accuracy, and the rest) is **PROVEN field by field**,
each from a live code path that reads it -- see "The monster stat table"
below, and [`../memory-map/battle.md`](../memory-map/battle.md) for the
readers themselves. The stat table is extracted end-to-end -- curated
JSON under `data/monsters/`, packed byte-exact back into the ROM by
`tools/monsters/pack_monsters.py` (`just compare us` passes) -- see "The
extraction pipeline" below. The
three functions that use the table (`DrawFolioBrutiMonsterPanel`,
`GetMonsterSpellEffectiveness`, `InitMonsterBattleActor`) are named in
`functions.us.cfg` but their own code is NOT extracted to `asm/*.s`; per
the project's hard rule 5 that requires fully-walked function
boundaries, out of scope here.

**JP status:** `MonsterTable` content is now **PROVEN byte-identical**
between US and JP (same as Krawall audio), just at a different address
(`0x0804F33C`, `data/monsters/monsters.json` is shared between both
versions, `regions.jp.txt` has its own `monster-table` row). Two of the
three functions are matched and named in `functions.jp.cfg`:
`InitMonsterBattleActor` (`0x08014C74`) and `GetMonsterSpellEffectiveness`
(`0x080188F8`), both content-verified (matching instruction shapes plus
the relocated `MonsterTable` literal landing at the same relative
offset) since `tools/match_functions.py`'s signature matching doesn't
catch either one on its own -- see "The extraction pipeline" below for
why. `DrawFolioBrutiMonsterPanel`, `UpdateFolioBrutiGridCursor`, and the
other functions found alongside them are still US-only; not yet matched
to JP.

## What we know

### The Folio Bruti detail-panel function

**PROVEN.** `sub_08036D60` (US ROM `0x08036D60`, Thumb) draws the entire
per-monster detail panel: the row of 8 spell-effectiveness sliders, the
monster's name, and its description. Identified by the dialog string IDs
it passes to `GetDialogText` (`0x080425E4`, see `docs/formats/text.md`):

- Loops `spell_index` 0..7, calling `GetDialogText(0x498 + spell_index)`
  (`0x498` = 1176) to print the 8 spell name labels. String IDs
  1176-1183 decode to Flipendo, Verdimillious, Incendio, Petrificus
  Totalus, Wingardium Leviosa, Spongify, Diffindo, Glacius, in that
  order (verified against `data/text/en_us.json`) -- this fixes the
  spell-index-to-name mapping used everywhere else in this doc.
- Computes a monster linear index `r7 = ([0x03005300+0xc] * 9) +
  [0x03005300+0x10]` (a 9-column grid; row/col -> linear index), then
  calls `GetDialogText(r7 + 0x4A2)` for the monster's name and
  `GetDialogText(r7 + 0x4E6)` for its description (`0x4A2` = 1186,
  `0x4E6` = 1254). Verified: index 4 decodes to name "Rat" (string 1190)
  and description "A rodent common to houses and barns." (string 1258)
  -- this is the exact string that started this investigation.

### The spell-slider draw loop and the effectiveness accessor

**PROVEN.** Inside the same function, a second loop over `spell_index`
(register `r6`) 0..7 (`build/us/full_disasm.s` lines ~53742-53852, ROM
`0x08036DFA`-`0x08036EC8`) draws the 8 sliders:

```
for spell_index in 0..7:
    sprite = per-slot sprite object (allocated once, OBJ template 0x080C2E78)
    effectiveness = sub_0801890C(monster_index, spell_index)   ; r0=r7, r1=r6
    if effectiveness == -1  OR  ram[0x03003190 + monster_index] <= 2:
        ; monster not yet Informus-analyzed (0x03003190 = g_abMonsterDocLevel_candidate,
        ; bumped to 4 by casting Informus -- see battle.md's
        ; `BumpMonsterDocLevel` writeup) (or this spell has no data):
        ; draw the fixed/animated "?" placeholder graphic
        ; (gfx 0x0806959C, frame data 0x080695CE)
    else:
        ; analyzed: draw the "dot" graphic, palette/frame picked via
        ; a small LUT at 0x080695DC indexed by divsi3_thumb(effectiveness, 0x21)
        x = sub_0802BF14(effectiveness << 16, 0xc8 << 15) * 0x1a + 0x9000
    place sprite at (x, y);  y += fixed row spacing
```

This is a direct, code-level match for the behavior described by the
user and by the game's own help text (dialog string 1468: *"The bars at
the bottom of the screen indicate how strong or weak the creature's
resistance is to each of the player's spells. The weaker the creature's
resistance to a spell, the further to the right the indicator on the bar
will be."*) -- `effectiveness` (0-100) is scaled and added to a base X,
so a higher value pushes the dot right, and the "?" branch fires exactly
when the monster's per-monster state byte at `0x03003190 + index` is
`<=2` (not yet analyzed), matching the "unseen -> silhouette, seen ->
sprite, analyzed -> name+description+dots" three-state design described
by the user (see also `docs/memory-map` conventions -- this state byte
array was already known from the Folio Bruti grid-icon code, not
independently re-derived here).

**`sub_0801890C(monster_index, spell_index)` -- the effectiveness
accessor, PROVEN via full decompilation of its body** (US ROM
`0x0801890C`, `build/us/full_disasm.s` line ~25351):

```c
u8 sub_0801890C(int monster_index, int spell_index) {
    if ((unsigned)spell_index > 7)
        return 0;
    switch (spell_index) {
        case 0: return MonsterTable[monster_index].byte[0xA];   // Flipendo
        case 1: return MonsterTable[monster_index].byte[0xC];   // Verdimillious
        case 2: return MonsterTable[monster_index].byte[0xB];   // Incendio
        case 3: return 100;                                     // Petrificus Totalus (fixed)
        case 4: return MonsterTable[monster_index].byte[0xD];   // Wingardium Leviosa
        case 5: return 100;                                     // Spongify (fixed)
        case 6: return MonsterTable[monster_index].byte[0xF];   // Diffindo
        case 7: return MonsterTable[monster_index].byte[0xE];   // Glacius
    }
}
```

(`MonsterTable[i]` = 24-byte stride, see below; the real code computes
the record address as `i*3` then `<<3`, i.e. `i*24`, and is a genuine
Thumb jump table at `_08018924`, 8 `.4byte` case targets, `mov pc, r0`
dispatch -- textbook `switch` compilation, not hand-rolled.) Only one
caller exists in the disassembly: the slider loop in `sub_08036D60`
above. Two of the eight spells (Petrificus Totalus, Spongify) are
**always 100% effective against every monster** -- not a per-monster
value at all, just a compiled-in constant in this function. This is a
real game-design fact, not a gap in the table.

### The monster stat table

**PROVEN.** Table base
**`0x0804F410`**, US ROM, stride **24 (0x18) bytes**, **69 records**
(monster index 0-68). The table's end lines up exactly with a
previously-known table start (`0x0804FA88`, referenced directly by
address in `sub_08036D60`'s icon-silhouette code): `0x0804F410 + 69*24 =
0x0804FA88`, confirming both the stride and the count independently of
the spell-effectiveness accessor.

Byte layout per record (offsets in hex), as read by `sub_0801890C` and by
the battle-init routine `InitMonsterBattleActor` (`sub_08014C88`,
`build/us/full_disasm.s` line ~22494, the field-copy loop starts at ROM
`0x08014E54`). This routine is the strongest evidence in
this document: it copies the *entire* record, field by field, into a
live battle-participant RAM struct -- one `ldrb`/`ldrh` per record field,
immediately followed by a `strb`/`strh` into the destination struct, with
no arithmetic in between. That gives two independent things for free:
the destination offsets prove the source's HP field really is used as
HP (below), and the specific instruction used for each source read
(`ldrb` vs `ldrh`) **proves each field's exact width/boundary**, even
for fields whose semantic meaning is still unknown. Note that offsets
`0x02`/`0x03` are two independent `u8` fields, not one `u16`: the trace
shows two separate `ldrb` reads, at `+2` and `+3`.
Offsets `0x14`/`0x16` are not touched by this routine at all -- no
corroboration either way for those two.

- `+0x00` (u16, HP) -> struct offsets `+8` AND `+0x24` (same raw value,
  written twice) -- matches the classic "current HP = max HP" battle-init
  idiom. **PROVEN this field is HP**, not just plausible from content.
- `+0x02` (u8) -> struct `+0xE`
- `+0x03` (u8) -> struct `+0x2A`
- `+0x04` (u8) -> struct `+0x2B`
- `+0x05` (u8) -> struct `+0x2C`
- `+0x06` (u16) -> struct `+0x30`
- `+0x08` (u16) -> struct `+0x32`
- `+0x0A`.."+0x0F" (six u8, the effectiveness bytes) -> struct
  `+0x34`.."+0x39"
- `+0x10` (u16) -> struct `+0xC`
- `+0x12` (u16) -> struct `+0x28`

| Offset | Size | Field | Confidence and reader |
|---|---|---|---|
| `0x00` | u16 | `hp` | **PROVEN** -- copied to both a current-HP and a max-HP struct offset, the classic battle-init idiom |
| `0x02` | u8 | `level` | boundary **PROVEN** (own `ldrb`, not half of a u16 with `0x03`); a monster's own value has **no traced reader** -- see the `bLevel` note below |
| `0x03` | u8 | `speed` | **PROVEN** -- turn order, lower = earlier. Common monsters cluster at `178-254` (act late); Lupin Werewolf `20` and Draco `60` act early |
| `0x04` | u8 | `accuracy` | **PROVEN** -- the attacker's hit-chance stat in `ResolveEnemyAttack`'s `Mt19937RandMax(99)` roll |
| `0x05` | u8 | `crit_chance` | **PROVEN** -- bonus-damage roll threshold (probability `this/101`). Monster-only in practice. Observed values: 3, 5, 10, shared within monster families |
| `0x06` | u16 | `damage_min` | **PROVEN** -- fed straight into `ResolveEnemyAttack`'s damage roll. Monotonic with monster tier |
| `0x08` | u16 | `damage_max` | **PROVEN**, same evidence |
| `0x0A` | u8 | Flipendo effectiveness (0-100) | **PROVEN** (`GetMonsterSpellEffectiveness` case 0) |
| `0x0B` | u8 | Incendio effectiveness | **PROVEN** (case 2) |
| `0x0C` | u8 | Verdimillious effectiveness | **PROVEN** (case 1) |
| `0x0D` | u8 | Wingardium Leviosa effectiveness | **PROVEN** (case 4) |
| `0x0E` | u8 | Glacius effectiveness | **PROVEN** (case 7) |
| `0x0F` | u8 | Diffindo effectiveness | **PROVEN** (case 6) |
| `0x10` | u16 | `reward_xp` | **PROVEN** -- paid into `g_nXpAccum` on kill, confirmed live in-game |
| `0x12` | u16 | `reward_gold` | **PROVEN** -- paid into `g_nGoldAccum`, same evidence |
| `0x14` | u8 | `special_effect_chance` | **PROVEN** -- percent chance (100 = guaranteed) that a scripted effect also fires after the monster's melee attack |
| `0x15` | u8 | `special_effect_id` | **PROVEN** -- effect-script id passed to `TriggerBattleEffect`; named entries in `tools/objscript/script_names.json` (e.g. `27` = poison bite, `60` = paralyzing blow). Clusters by monster family |
| `0x16` | u16 | padding | STRUCTURAL MATCH -- always 0 across all 69 records, and not read by battle-init |

Every reader named above lives in
[`../memory-map/battle.md`](../memory-map/battle.md), which owns each
field's semantics and the evidence behind it (turn order,
`ResolveEnemyAttack`'s formula, `ResolvePlayerAttack`'s effectiveness
switch, the XP/gold payout, `RollMonsterSpecialEffect_candidate`).

**The `bLevel` note.** `BattleFighter+0xE` is a proven level counter for
*player* fighters. No monster ever reaches either code path that reads
it (every monster's `Object` is wired to the melee-only tick callback,
and `ResolveEnemyAttack` doesn't touch the offset), so a monster's own
value at `+0x02` has no traced reader -- it is the same field at the
same offset, filled the same way as every other column here, just never
observed being consumed.

**Note on `0x14`/`0x15`:** these are two `u8` fields, not one `u16` --
boundary-PROVEN, `RollMonsterSpecialEffect_candidate` reads them with two
separate `ldrb` instructions (`byte[0x14]`, `byte[0x15]`).

No stored field is used for Petrificus Totalus or Spongify -- confirmed
by `sub_0801890C` directly (see above), not an oversight in this table.

### Statistical corroboration for the stat fields

The field table above gives every one of these offsets a traced reader,
which is the authority. This section records the separate statistical /
gameplay observations that bear on them -- much weaker evidence, worth
knowing about mainly so nobody re-derives a wrong reading from content
shape alone.

- `0x02` (`level`) correlates with HP across the 53 real Folio Bruti
  rows (Pearson r ~ 0.81), and its two highest values belong to Draco
  (60) and Lupin Werewolf (55).
- `0x03` (`speed`): Lupin Werewolf holds the table-wide lowest value
  (`20`), fitting a boss that acts first. The correlation is not
  reliable in general, though -- Gytrash is a known-fast creature in
  play but sits at `245`, i.e. a late turn (`0x02=11, 0x03=245,
  0x04=85, 0x05=3`).
- **A defense / magic-defense reading of any field here is
  unsupported.** Lupin Werewolf being physically vulnerable and
  magic-immune, while `0x03`/`0x04` sit at opposite extremes, invites
  reading them as an asymmetric defense pair; `0x04` has a traced
  reader making it accuracy, an unrelated stat. Treat any
  defense-flavoured reading as unsupported until a real reader turns
  up.

### Ghidra cross-check

Re-verified independently against a Ghidra decompilation of
`baserom.us.gba` (not just the project's own `gbadisasm` output), per the
project's caution that either tool's auto-analysis can be wrong --
disassembly, not decompilation, was treated as ground truth wherever the
two disagreed.

`InitMonsterBattleActor` (`0x08014C88`) and `GetMonsterSpellEffectiveness`
(`0x0801890C`) decompile exactly as described above, field-copy by
field-copy and case by case.

One Ghidra-side boundary error worth knowing about: its auto-analysis
mis-split a nearby, unrelated function (`0x08014f1c`-`0x0801500e`, the
fighter-select-marker sprite spawner
`SpawnTurnOrderIcon_candidate`) into two, guessing a bogus second entry
point at `0x08014fb0` for what disassembly shows is the else-arm of an
`if`/`else` (its only xref is a conditional branch from inside the same
function, no `bl`, no prologue, shared epilogue). Re-merged in the
Ghidra DB; deliberately **not** added to `functions.us.cfg`, since it
isn't a real function boundary.

Content sanity-check (not proof, but corroborating): indices 0-2 are the
three Fire Crab colour variants (Ruby/Emerald/Sapphire, string ids
1186-1188) with HP 36/50/120 -- rarer variant, tougher monster -- and all
three carry Incendio effectiveness `10` against Glacius `100`: a fire
crab is near-immune to a fire spell and maximally vulnerable to ice,
exactly the type-matchup a bestiary would encode. Indices 4-6 are
Rat/Albino Rat/Plague Rat (string ids 1190-1192) with HP 18/25/35,
again increasing with tier and sharing one effectiveness row across the
family. (Values read from `data/monsters/monsters.json`.)

Verification snippet:

```python
import struct
rom = open('baserom.us.gba', 'rb').read()
def monster_record(i):
    off = (0x0804F410 - 0x08000000) + i * 24
    return rom[off:off+24]

SPELL_BYTE_OFFSET = {0: 0xA, 1: 0xC, 2: 0xB, 4: 0xD, 6: 0xF, 7: 0xE}  # 3, 5 are fixed at 100
def effectiveness(monster_index, spell_index):
    if spell_index in (3, 5):
        return 100
    return monster_record(monster_index)[SPELL_BYTE_OFFSET[spell_index]]

hp = struct.unpack_from('<H', monster_record(0))[0]
print(hp, effectiveness(0, 2))  # Ruby Fire Crab HP, Incendio effectiveness -> 36 10
```

### Adjoining tables (found, not decoded)

Immediately **before** the stat table, ROM `0x0804E6B4`-`~0x0804F400`,
is a monster graphics-pointer table (32-byte stride, ~106 rows -- more
rows than the 69-monster stat table, see "What's NOT yet known"). This
was independently found via the same `sub_08036D60` function (its icon
rendering reads this table at `+0x08`/`+0x18` for palette-swap variant
pointers); not re-derived here in detail.

Immediately **after** the stat table, `0x0804FA88` (4-byte stride,
referenced directly by `sub_08036D60`'s icon-silhouette-vs-real-sprite
branch): the first ~20 entries sampled are all the constant
`0x00010000`, which reads naturally as a 16.16 fixed-point `1.0` --
candidate "per-monster icon animation speed multiplier" with most
monsters left at the default. **UNCONFIRMED**, not pursued further.

An apparently unrelated table with smoothly, monotonically increasing
values (consistent with an XP-per-level or similar progression curve)
begins somewhere past `0x0804FC00`-ish, discovered incidentally while
scanning past the end of the stat table's padding region. **Address not
pinned down, structure not verified, completely out of scope for Folio
Bruti** -- flagged here only so a future session doesn't reinvestigate
from scratch and mistake it for bestiary data.

### The grid boundary: 53 real entries, not 69 -- PROVEN via live mGBA debugging

**PROVEN**, dynamically, not just inferred from static/content evidence.
`MonsterTable` has 69 rows total, but the Folio Bruti bestiary grid only
ever displays/navigates to the first **53** of them (indices 0-52) --
indices 53-68 are boss/story encounters that share the table (see below)
but are never reachable through the bestiary UI.

Confirmed live via mGBA's debugger console (breakpoint on
`DrawFolioBrutiMonsterPanel`, `0x08036D60`, plus reading its screen-state
struct `0x03005300` -- `+0xC` = cursor row, `+0x10` = cursor column,
matching the `row*9 + column` linear-index computation already
identified statically). The grid is a real 9-column x 6-row layout (54
physical cells). Moving the cursor to `row=4, col=8` (0-indexed; the
rightmost column of the second-to-last row) and then moving one more
step **wrapped straight back to `row=0, col=8`, skipping `row=5, col=8`
entirely** -- the one physical grid cell the user had already identified
as visually empty (bottom-right corner, missing in the live 9x6 render).
`row=5, col=8` -> linear index `5*9+8 = 53` -- exactly monster index 53,
`"Flesh-eating Slug (not in game, needs to be in file for coders - no
need to translate)"`. The cursor-movement code steps over this one index
on purpose; it is unreachable in normal play. This also matches the
user's own live observation of the grid's content: index 0-2 (Fire Crab
trio) at the start, and indices 50-52 (Tree Frog / Wide-mouth Toad /
Bullfrog) as the last visible row before the gap.

Net result: **53 real Folio Bruti monsters, indices 0-52.** Indices
53-68 are `MonsterTable` rows used by `InitMonsterBattleActor` for
combat (bosses/story fights per the user's gameplay knowledge -- Crabbe,
Draco, Goyle, Lupin Werewolf, "The Monster Book of Monsters" x3, River
Troll, Venemous Tentacula, etc., see prior investigation), but never
exposed through the bestiary grid at all. Index 53 itself
("Flesh-eating Slug") is confirmed to be the boundary marker the user
suspected, not a real monster -- both by its own dev-comment name text
and now by the cursor explicitly skipping over it.

**Update -- the skip code itself is now found and fully decompiled.**
`UpdateFolioBrutiGridCursor` (`sub_08036BB8`, US ROM `0x08036BB8`) is the
D-pad handler. Located by combining the live backtrace above (which
resolved to a generic dispatcher chain, not a Folio-Bruti-specific
caller, so no direct route from the backtrace alone) with a `capstone`
linear disassembly of the raw ROM bytes in the gap between the two
functions the backtrace *did* land in (`sub_08035EB0` and
`DrawFolioBrutiMonsterPanel`) -- `gbadisasm` had no seed anywhere in this
whole stretch (`0x08035F7C`-`0x08036D60`, reached only via indirect
dispatch, same as everything else on this screen) and had dumped all of
it as unclaimed raw `.byte` data despite it being real, live-executing
code. That one gap turned out to contain **18 separate undetected
functions**, all seeded in `functions.us.cfg` and verified to assemble
byte-exact (`just disasm-compare`/`just check-all` both pass).

Reads the held-key bitmask at `0x030034F0` (bits `0x10`/`0x20` = D-pad
Right/Left, `0x40`/`0x80` = Up/Down -- inferred from which axis of
`0x03005300+0xC`/`+0x10` each one updates, matching standard GBA
`KEYINPUT` bit order) and updates the cursor's row (`+0xC`) and column
(`+0x10`) fields directly in the screen-state struct. All four
directions share the identical guard, run as a do-while after applying
one step:

```c
do {
    // apply one step in the pressed direction to row and/or column,
    // wrapping row 0<->5 and column 0<->8 independently
} while (column == 8 && row == 5);
```

i.e. after each single-step move (with independent wraparound on each
axis), if the new position is exactly `row=5, col=8` (monster index 53,
"Flesh-eating Slug"), the handler applies **another** step in the same
direction before stopping -- so the cursor always passes straight
through that one cell without ever resting on it. This is an exact,
code-level match for the live behavior observed above (wrap from
`row=4,col=8` straight to `row=0,col=8`, i.e. two steps applied for one
button press specifically at that boundary). Right/Left move the linear
`row*9+col` index by +-1 with carry into the other axis (page-scroll
style); Up/Down move `row` by +-1 with column held fixed -- both
share the same skip guard.

### The extraction pipeline, built and build-integrated

**PROVEN** (round-trips byte-exact, `just compare us` passes). Mirrors
the Krawall/dialog-text pipelines:

- `tools/monsters/monster_codec.py` -- shared record layout: field
  name/struct-format pairs in on-disk order, matching the table above
  exactly (unconfirmed fields named `unk_0x<offset>_u<bits>`).
- `tools/monsters/extract_monsters.py` (`just extract-monsters`) -- one-time
  bootstrap, reads `baserom.us.gba`, writes `data/monsters/monsters.json`
  (a plain JSON array, index = monster index, one object per record).
  Gitignored, same footing as the baserom, per hard rule 2 -- not
  regenerated by `just build`, meant to be user-editable.
- `tools/monsters/pack_monsters.py` (`just pack-monsters`, wired into
  `just build`) -- reads `data/monsters/monsters.json` plus the
  `monster-table` row in `regions.<ver>.txt`, re-packs each record with
  `monster_codec.pack_record` and writes `build/<ver>/monsters/*.s`.
- `regions.us.txt`'s new `monster-table` row (`0x0804F410`-`0x0804FA88`)
  and `tools/gen_rom_s.py`'s new `monster-table` directive wire the
  packed output into the stitched build the same way `krawall-module`
  rows do.
- Each JSON record also gets leading `_name`/`_description` fields
  (`extract_monsters.py`, `NAME_STRING_ID_BASE`/`DESC_STRING_ID_BASE` +
  index decoded straight from the ROM's dialog text) purely as
  human-readable annotations -- `pack_monsters.py` ignores both
  entirely, so they round-trip fine, but neither is real extracted ROM
  data the way the 24-byte record is. `_description` is `null` for
  indices `>= FOLIO_BRUTI_COUNT` (53) rather than showing the unrelated
  text the formula lands on there (spell names, battle-HUD strings,
  etc. -- see "The grid boundary" above); `_name` is left as-is past
  that cutoff since it's frequently still real, meaningful text (boss
  names), just not a bestiary entry -- known exception: index 68 (see
  "What's NOT yet known").
- Two of the three US-named functions are matched into `functions.jp.cfg`
  too: `InitMonsterBattleActor` (JP `0x08014C74`) and
  `GetMonsterSpellEffectiveness` (JP `0x080188F8`), plus the JP
  `MonsterTable` address itself (`0x0804F33C`, content byte-identical to
  US). `tools/match_functions.py`'s automated signature matching does
  NOT find either function on its own -- its `bl`/`blx`-target masking
  doesn't cover the plain `ldr =literal` absolute addresses these two
  rely on heavily (the jump table pointer, the `MonsterTable` address
  itself), so their signatures differ between versions even though the
  code is identical. Both were instead confirmed by direct content
  comparison: matching instruction shapes end-to-end, plus (for
  `InitMonsterBattleActor`) the exact same struct-offset copy sequence
  as the already-verified US version, and (for
  `GetMonsterSpellEffectiveness`) the same case-handler struct offsets
  (e.g. `+0xA` for Flipendo) after skipping past the jump table itself
  (which capstone, lacking boundary info, decodes as garbage
  instructions -- expected and harmless, same as gbadisasm would do
  before a function is seeded). Match a candidate on its *interior* (the
  field-copy sequence), not just its prologue: `0x08014F08` carries a
  prologue identical to `InitMonsterBattleActor`'s while being an
  unrelated function, and only the interior check separates it from the
  real one at `0x08014C74`.

## What's NOT yet known

- **`MonsterTable` holds boss/story encounters, not just Folio Bruti
  monsters -- indices 53 onward** (now PROVEN as a grid boundary, see
  "The grid boundary" above). Per the user (real gameplay knowledge, not
  independently code-traced): Crabbe, Draco, Goyle, Lupin Werewolf, "The
  Monster Book of Monsters", River Troll, and Venemous Tentacula are all
  boss encounters that do **not** appear in the Folio Bruti bestiary
  grid. `_description`'s garbage output for indices 53-68 (spell names,
  multiplayer labels, battle-HUD text -- see the extraction pipeline
  section) is independent corroboration for the same range. Still open:
  exactly which of indices 54-68 map to which real boss encounter --
  only the ones the user identified by name are confirmed; indices 59
  (`Giant Rat`), 64 (`Snake`), 65 (`Brown Recluse Spider`) reuse ordinary
  creature names rather than character names, so are plausibly
  "boss-tier" versions of regular monsters rather than misattributed --
  not confirmed either way.
- **Index 68's stat record is byte-identical to index 58's**, in every
  field except `_name`/`_description` (58 decodes to a real boss name;
  68's `NAME_STRING_ID_BASE + index` lookup lands on a stray description
  sentence instead, and its own description lookup is equally
  unrelated). Given the finding above, both readings are consistent with
  68 being unused/padding at the very end of the table; whether it's a
  genuine reachable 4th "Monster Book of Monsters" fight is still
  unconfirmed -- not investigated further.
- **The exact monster count discrepancy.** The stat table (and the
  `0x03003190` per-monster state array reset loop, `sub_080370A0`,
  bound `0..0x44` inclusive = 69) both agree on **69** monsters. But the
  graphics-pointer table at `0x0804E6B4` structurally continues for
  ~106 rows before its pattern breaks. Two options, neither confirmed:
  (a) the graphics table includes non-Folio-Bruti monsters (enemies
  that appear in combat but were never added to the bestiary grid), or
  (b) the break-detection heuristic used to find row 106 is simply
  wrong about where that table really ends. Not resolved.
- **The graphics-pointer table's own fields** (`0x0804E6B4`, 32-byte
  stride) beyond what was already used elsewhere (`+0x08`, `+0x18`) --
  not revisited here.
- **JP ROM** -- nothing in this document has been cross-checked against
  `baserom.jp.gba`. Given the Krawall and dialog-text precedent (see
  `CLAUDE.md`), the underlying data is likely to be content-identical
  but at a different address; do not assume the addresses above apply
  to JP without verifying.
- **Neither of the three named functions' code is extracted to
  `asm/*.s`.** `DrawFolioBrutiMonsterPanel` (`0x08036D60`) and
  `InitMonsterBattleActor` (`0x08014C88`) are large and only partially
  walked, so their boundaries don't meet hard rule 5's bar; they are
  named in `functions.us.cfg` so the disassembly reads clearly, and
  nothing more.
- The graphics-pointer table (`0x0804E6B4`) was NOT extracted -- its own
  fields are still unconfirmed (see above) and its row-count discrepancy
  with the stat table is unresolved.
