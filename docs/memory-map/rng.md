# RNG / MT19937 — memory map

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

## RNG and battle-fighter memory layout (external, unverified against our disasm)

Sourced from a BizHawk Lua script (`hp3rng.lua`, a live RNG-manipulation
display tool for TAS/speedrunning), shared by **jogotu** from the "Harry
Potter Handheld Speedrunning" Discord server. This was *not* derived from
our own disassembly -- it's runtime EWRAM addresses read live by an
emulator script, presumably reverse-engineered by that author independently
(likely on the US ROM, version unconfirmed). Treat everything below as
**UNCONFIRMED** until cross-checked against our own disassembly/Ghidra
findings; addresses are given as-is from the script.

### PRNG: Mersenne Twister (MT19937)

The script's `rnd_from_state` function is the textbook MT19937 tempering
step:

```
y ^= y >> 11
y ^= (y << 7)  & 0x9D2C5680
y ^= (y << 15) & 0xEFC60000
y ^= y >> 18
```

This is a strong structural signal (matches the public-domain MT19937
reference constants exactly) that the game's RNG is MT19937, not a
hand-rolled LCG -- worth confirming against `docs/compiler.md`/library-call
findings once the relevant function is located in our disasm.

EWRAM state, read live by the script:

- `0x03005578` (u32) -- `total_index`, a running count of numbers drawn.
- `0x0300557C` (u32) -- `stateptr`, base address of the 624-word MT state
  array (read as 2500 bytes = 625 x 4-byte words in the script, one word
  more than the canonical 624 -- possibly an off-by-one in the script, or a
  genuine extra slot; unconfirmed).
- `0x03005580` (u32) -- `curptr`, pointer into the state array at the
  current draw position (`curindex = (curptr - stateptr) / 4`).
- `0x03005584` (u32) -- `remainingIndices`, count of untempered words left
  before the next full MT19937 regeneration pass.

### Bounded-random helper

```
get_random_int_max(state, max) = (2 * (state & 0x7FFF) * (max + 1)) >> 16
```

Takes a tempered MT19937 output, keeps only its low 15 bits, and maps it
into `[0, max]`. This is the shape to look for when identifying the game's
"roll a random int in range" library function in disasm -- distinctive
because it discards the upper 17 bits of entropy entirely.

### Battle/fighter struct layout

- `0x030024E8` (u32, EWRAM) -- pointer to the current fight struct, `0` when
  not in a battle.
- fight struct:
  - `+0x4` (u32) -- pointer to the brutes (fighters) array.
  - `+0x106F` (u8) -- fighter count.
- brute/fighter struct, array stride `0x48` bytes:
  - `+0x0` (u8) -- type tag: `0xFF` = enemy (next byte indexes the enemy
    name table below), otherwise indexes the hero table
    (`Harry`/`Hermione`/`Ron`/`Buckbeak`).
  - `+0x1` (u8) -- enemy/hero index.
  - `+0x8` (u16 LE) -- current SP.
  - `+0xA` (u16 LE) -- current MP.
  - `+0x2B` (u8) -- accuracy stat, compared against
    `get_random_int_max(roll, 100)` to decide attack hit/miss (hit if
    `roll100 >= acc`). **Confirmed correct, see
    [`battle.md`](battle.md)**: `ResolveEnemyAttack` (`0x08017E44`, found
    from an address contributed by jlun2) reads the attacker's `+0x2B` as
    an accuracy stat and rolls `Mt19937RandMax(99)` against it for
    hit/miss -- direction is hit if `roll < acc` (miss if `roll >= acc`),
    the opposite framing from this note's `roll100 >= acc` but the same
    field and the same mechanic. `MonsterTable+0x04`, the table field this
    stat is loaded from, is documented as `accuracy` in
    [`../formats/folio_bruti.md`](../formats/folio_bruti.md).

### Enemy name table (75 entries, script order = presumed in-game index order)

Ruby/Emerald/Sapphire Fire Crab; Cornish Pixie; Rat, Albino Rat, Plague Rat;
Clabbert; seven Suit of Armor variants (Footman/Cavalier/Paladin/Squire/
Swordsman/Crusader/Knight); Funnelweb/Brown Recluse/Large/Redback/Giant/
Cocoon/Whitetail Spider; Flobberworm; Snail, Large Orange Snail, Flailtail
Snail; Bat, Fruitbat, Mortis Bat; Dragonfly, Imperial Dragonfly; Horklump;
Snake, Spitting Snake; Wasp, Tarantula Hawk Wasp; Bowtruckle, Oaken
Bowtruckle; Doxy, Doxy Queen; Hinkypunk; Gytrash; Grindylow; Red Cap,
Armored Red Cap; Salamander, Amazonian Salamander, Peruvian Salamander;
Charmed Skeleton, Jinxed Skeleton; Tree Frog, Wide-mouth Toad, Bullfrog;
Flesh-eating Slug (per the script author's comment: "not in game, needs to
be in file for coders -- no need to translate"); Whomping Willow; Forest
Troll, River Troll; Venemous Tentacula; 'The Monster Book of Monsters';
Giant Rat; Crabbe, Draco, Goyle; Lupin Werewolf; Snake (repeat); Brown
Recluse Spider (repeat).

If/when this table is located as a real data structure in our disassembly,
it should be cross-checked entry-by-entry (including the two trailing
repeats and the "not in game" placeholder) before being trusted as
complete/ordered correctly.

### Updates from a newer script revision (`hp3rng (2).lua`, same author/attribution)

A later revision of the same script (still jogotu, same Discord) adds a
second bounded-random helper and two new derived-stat formulas. Same
confidence caveat as above -- UNCONFIRMED against our own disasm.

```
get_random_int_range(state, min, max) = min + ((state & 0x7FFF) * (max - min + 1)) >> 15
```

A `min`/`max` generalization of `get_random_int_max` (which is just this
with `min=0`, plus a `>>16` instead of `>>15` -- the two are not quite the
same rounding, so both forms may be genuinely distinct in-game helpers
rather than one calling the other; unconfirmed which the real code uses
where).

New fighter struct field:

- `+0x10` (u8) -- level.

Two new formulas built on top of the existing pieces:

- **Card draw**: `get_random_int_range(roll, 0, 29)` -- a 30-outcome roll,
  driven by a standalone persistent "cards" window in the script (not tied
  to a specific fighter). Likely backs a collectible-card/trading-card
  minigame (the game has a Famous Witches & Wizards card mechanic);
  unconfirmed which subsystem actually consumes this.
- **Critical hit**: uses the *next* MT19937 draw after the hit/miss roll
  (`rnd_next`, i.e. `curindex + j + 1`, not `j`) fed through
  `get_random_int_max(rnd_next, 100)`, then crit if
  `rnd_next100 > (97 - min(level, 24))`. So crit chance scales with level,
  capped at level 24 (i.e. crit roll threshold never drops below `97-24=73`,
  so max ~27% crit chance), and consumes a second, separate RNG draw beyond
  the accuracy roll for the same attack.

## MT19937 PRNG located and named in disasm -- PROVEN

Found by grepping the full disassembly (`build/<ver>/full_disasm.s`) for the
MT19937 tempering constants `0x9D2C5680`/`0xEFC60000` from jogotu's script
(see above) and the standard twist-loop matrix constant `0x9908B0DF` --
all three appear together, giving a **PROVEN** structural match to the
Matsumoto/Nishimura reference algorithm (not a reimplementation guess: the
twist loop is split into the textbook two passes of `N-M` (227) and `M-1`
(396) iterations plus the wraparound word, `N=624`/`M=397`, with the
canonical upper/lower masks `0x80000000`/`0x7FFFFFFF`). A 16-function
cluster was identified this way, named in `functions.us.cfg`/
`functions.jp.cfg` (verified with `just disasm-compare` -- both versions
still byte-identical to their donor ROMs after seeding these names):

| Name | US addr | JP addr | What it does |
|---|---|---|---|
| `Mt19937Regenerate` | `0x0803B1B8` | `0x0803B220` | Regenerates all 624 state words (the "twist"), tempers and returns the most recently generated word. Called only when the draw cursor is exhausted. Also contains a defensive re-seed path (LCG multiplier `0x10DCD` = 69069, the classic 1998 Matsumoto/Nishimura `sgenrand` multiplier) gated on an unusual "remaining < -1" sentinel, not yet understood. |
| `Mt19937AllocState` | `0x0803B314` | `0x0803B37C` | Allocates the 625-word state block (`AllocBlock(0x9C4)`) into `gMt19937StatePtr` at boot; sole caller `AgbMain`. Only words 0-623 are used (word 624 is never read or written). |
| `Mt19937AutoSeed` | `0x0803B330` | `0x0803B398` | Derives a seed from `g_pVBlankState->dwVBlankCount` (see `include/vblank.h` -- a general interrupt-state struct, not RNG-specific), a `0x030034EC` halfword counter, and an accumulating `0x03005594` global, then calls `Mt19937SetSeed`. Likely the startup auto-seed path. |
| `Mt19937SetSeed` | `0x0803B3AC` | `0x0803B414` | Takes an explicit seed parameter, calls `Mt19937SeedArray`, then immediately marks the full 624-word block as available (`remainingIndices = 0x26F`) and resets the draw cursor to `stateptr + 4` -- state[0] (raw seed OR'd with 1) is skipped as internal-only. |
| `Mt19937RandRange` / `Mt19937RandRange2` | `0x0803B3E0` / `0x0803B40C` | `0x0803B448` / `0x0803B474` | `min + ((draw & 0x7FFF) * (max-min+1)) >> 15` -- matches the script's `get_random_int_range`. `2` variants read from the second draw cursor (see below). |
| `Mt19937RandMax` / `Mt19937RandMax2` | `0x0803B434` / `0x0803B458` | `0x0803B49C` / `0x0803B4C0` | `(2 * (draw & 0x7FFF) * (max+1)) >> 16` -- matches the script's `get_random_int_max`. |
| `Mt19937RandSigned` / `Mt19937RandSigned2` | `0x0803B47C` / `0x0803B4A8` | `0x0803B4E4` / `0x0803B510` | Symmetric variant returning a value in `[-max, max]`; not represented in either version of jogotu's script. `2` variant reads from the second draw cursor. No callers found yet. |
| `Mt19937Chance` / `Mt19937Chance2` | `0x0803B4D4` / `0x0803B500` | `0x0803B53C` / `0x0803B568` | Boolean percent-chance check: `(draw & 0x7FFF) * 101 >> 15` compared against a caller-supplied percent threshold. `2` variant reads from the second draw cursor. No callers found yet. |
| `Mt19937ChanceNoisy` | `0x0803B52C` | `0x0803B594` | Same as `Mt19937Chance` but adds the live VCOUNT hardware register (`0x04000006`) into the draw before masking -- an extra hardware-timing-noise source layered on top of the PRNG, not represented in the script either. |
| `Mt19937SeedArray` | `0x0803B560` | `0x0803B5C8` | Low-level: fills `state[0]` with `seed \| 1`, then `state[i] = 0x10DCD * state[i-1]` for the rest -- the actual LCG-based initial fill (called by both seeding entry points). |
| `Mt19937Next` / `Mt19937Next2` | `0x0803B598` / `0x0803B5F4` | `0x0803B600` / `0x0803B65C` | "Get next tempered value" -- decrements the remaining-count, calls `Mt19937Regenerate` when exhausted, otherwise tempers the current state word inline and advances the cursor. Equivalent to the reference `genrand_int32()`. |

**New finding beyond jogotu's script**: there are two entirely independent
draw cursors sharing one 624-word state array --

- Cursor 1 (the one the script tracks): index `0x03005578`, cursor pointer
  `0x03005580`, remaining count `0x03005584` (US); `0x030055D8`/
  `0x030055E0`/`0x030055E4` (JP).
- Cursor 2 (undocumented by the script): index/remaining at `0x0300558C`,
  cursor pointer `0x03005588` (US); `0x030055EC`/`0x030055E8` (JP). Its
  regeneration path never calls `Mt19937Regenerate` -- it only wraps to
  `stateptr + 4` on exhaustion, so it can read but never regenerate the
  shared state array; it can't affect cursor 1's outputs. No callers found
  yet for any `*2` helper. Working hypothesis: cursor 2 is a read-only tap
  for non-gameplay/cosmetic rolls, not something a battle simulator needs
  to keep in lockstep with cursor 1. Unconfirmed -- needs an actual `*2`
  call site to verify.

`Mt19937Next` also writes the temper result's low byte to a single-byte
global (`0x03005574` US / `0x030055D4` JP) as a side effect on every call --
purpose unconfirmed (a "last roll" cache for some other subsystem?).

Not yet done: locating actual callers (e.g. the battle hit/miss and crit
logic jogotu's script infers from EWRAM battle structs) to confirm which of
the two cursors and which helper each gameplay system actually uses.