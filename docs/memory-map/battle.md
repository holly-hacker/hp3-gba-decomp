# Battle system -- memory map

See [`../memory-map.md`](../memory-map.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout.

External, unverified leads were contributed by two members of the HP3-GBA
speedrunning/TAS community and cross-checked against our own disassembly
before being trusted:

- **jogotu** (BizHawk live-memory script, `hp3rng.lua`) -- see
  [`rng.md`](rng.md) for the RNG/fighter-struct notes sourced from their
  script.
- **jlun2** -- pointed at three addresses from their own reverse-engineering
  work: `0x0803B3E0` (matches our already-identified `Mt19937RandRange`),
  `0x0803B400` (a literal-pool constant inside that same function, reached
  from a damage-roll call site), and `0x08017F70` (inside the attack-
  resolution function documented below, specifically its damage-halving
  logic tied to the in-game "Be More Careful" skill). All three led
  directly to the findings in this document.

Dynamic verification via mGBA's gdb stub (breakpoint at `0x08017E44`, run
directly through mGBA's own debug console rather than scripted) worked
cleanly here and confirmed several findings below live -- contrast with
`krawall.md`'s "Dynamic verification attempt" section, where the same
stub was unreliable under scripted breakpoint/continue sequencing.

## `BattleFighter` struct (0x48-byte stride)

Live, in-battle per-fighter record. Array pointer lives at
`fight_struct+4` (`fight_struct` itself is `*0x030024E8`, per jogotu's
script and confirmed directly in our own disasm -- see `rng.md`). One
record per active combatant (both party members and enemies share this
layout); `InitMonsterBattleActor` (`0x08014C88`, see
[`../formats/folio_bruti.md`](../formats/folio_bruti.md)) populates a
monster's record from `MonsterTable`.

| Offset | Size | Field | Confidence | Source |
|---|---|---|---|---|
| `0x00` | u8 | fighter type tag (`0xFF` = enemy, else indexes the hero table) | STRUCTURAL MATCH | jogotu |
| `0x01` | u8 | roster index (enemy/hero index) | STRUCTURAL MATCH | jogotu |
| `0x04` | u32 | pointer to this fighter's sprite `Object` | PROVEN | `InitMonsterBattleActor` |
| `0x08` | u16 | current HP | PROVEN | `InitMonsterBattleActor`, `ApplyDamageToFighter` |
| `0x24` | u16 | max HP | PROVEN | `InitMonsterBattleActor`, `ApplyDamageToFighter` |
| `0x2A` | u8 | candidate "defense" (`MonsterTable+0x03`) | STRUCTURAL MATCH, weak -- **no confirmed reader found**; not used by `ResolveMeleeAttack` | -- |
| `0x2B` | u8 | **accuracy** | **PROVEN** -- see "Attack resolution" below | jlun2 (led here) |
| `0x2C` | u8 | candidate "crit chance" (`MonsterTable+0x05`) | STRUCTURAL MATCH -- read as a roll threshold in the bonus-damage check, see below | jlun2 (led here) |
| `0x2E` | u8 | defense scaling, percent (`damage = damage * this / 100`) | PROVEN as a formula input; **origin not traced** -- `InitMonsterBattleActor` never writes it from `MonsterTable`, so monster records may rely on a default/zero here, or it's set by a separate (player-only?) code path not yet found | jlun2 (led here) |
| `0x30` | u16 | **base damage roll, min** (`MonsterTable+0x06`) | **PROVEN** -- fed directly into `Mt19937RandRange` as the attack's damage roll | jlun2 (led here) |
| `0x32` | u16 | **base damage roll, max** (`MonsterTable+0x08`) | **PROVEN** | jlun2 (led here) |
| `0x3A` | u8 | selected action/spell index for this turn | STRUCTURAL MATCH -- used across multiple AI/dispatch functions (e.g. `0x080100a0`) | -- |
| `0x42` | u8 | status-flags bitfield | PROVEN as a formula input, bits below | jlun2 (led here) |

### `0x42` status-flags bits (confirmed usage in `ResolveMeleeAttack`)

- **bit `0x01`** (checked on the *defender*): if set, reduces the
  *attacker's* effective accuracy by 25 before the hit roll. Also gates
  the bonus-damage/crit-style check further down (must be clear for that
  check to run at all). Candidate: an evasion/dodge stance.
- **bit `0x08`** (checked on the *attacker*): independently contributes
  one halving of the computed damage (see below). Meaning UNCONFIRMED --
  possibly "this is a weakened/reduced-power strike."
- **bit `0x20`** (checked on the *defender*): independently contributes
  one halving of the computed damage. **Candidate: the in-game "Be More
  Careful" skill** (per jlun2) -- a defensive action that halves incoming
  damage. The two halving bits (attacker's `0x08`, defender's `0x20`)
  stack multiplicatively: neither set -> no change; exactly one set ->
  damage `>>= 1`; both set -> damage `>>= 2` (quartered).

## Attack resolution -- `ResolveMeleeAttack` (`sub_08017E44`, US `0x08017E44`)

**PROVEN**, traced end-to-end from the on-disk `gbadisasm` output
(`build/us/full_disasm.s`) and independently confirmed via Ghidra
decompilation once the function boundary was defined there (Ghidra's own
auto-analysis did not find this function on its own; had no call site
recognized as Thumb yet, so it needed a manual boundary). Ghidra's
decompile of the function's tail (the bonus-damage block, past the
halving logic) is garbled (`Bad instruction data` / overlapping-
instruction warnings) -- that section is transcribed below from the
on-disk disassembly instead, which is unambiguous and treated as ground
truth here per the project convention.

Signature: `int ResolveMeleeAttack(int attackerIndex, int defenderIndex)`.

```c
int ResolveMeleeAttack(int attackerIndex, int defenderIndex) {
    BattleFighter *fighters = *(BattleFighter **)(currentFighterStruct + 4);
    BattleFighter *attacker = &fighters[attackerIndex];
    BattleFighter *defender = &fighters[defenderIndex];

    // hit/miss
    int accuracy = attacker->accuracy;
    if (defender->statusFlags & 0x01)
        accuracy -= 25;
    if (Mt19937RandMax(99) >= accuracy)
        return 0;                                    // miss

    // base damage, scaled by defender's defense factor
    int damage = Mt19937RandRange(attacker->damageRollMin, attacker->damageRollMax);
    damage = damage * defender->defenseFactorPercent / 100;

    // halving (attacker bit 0x08 and defender bit 0x20 each independently halve)
    if (attacker->statusFlags & 0x08)
        damage >>= (defender->statusFlags & 0x20) ? 2 : 1;
    else if (defender->statusFlags & 0x20)
        damage >>= 1;
    damage += 1;                                       // rounding

    // bonus-damage / crit-style check
    if (damage != 0 && !(defender->statusFlags & 0x01)) {
        int roll = Mt19937RandMax(100);
        if (roll > 100 - attacker->critChance_candidate) {
            damage *= 2;
            damage += 999;   // sentinel, not literal damage -- see note below
        }
    }

    ApplyDamageToFighter(damage, defenderIndex);
    return damage;
}
```

Notes:

- The `+= 999` (`0x3E7`) on the bonus-damage path is almost certainly a
  **sentinel/flag value, not literal damage points** -- monster HP in
  this data tops out around 254 (see `../formats/folio_bruti.md`), so a
  flat +999 would be absurd as real damage. The value `999`/`0x3E7`
  recurs elsewhere in this codebase's battle-message code as an
  out-of-band marker (e.g. `if (999 < someValue)` guards seen in
  `FUN_08010864` and the level-up display code), suggesting a
  project-wide convention of using it to flag "this isn't a plain number,
  handle specially" to whatever reads the return value. Not traced to a
  caller that consumes it that way; UNCONFIRMED but consistent.
- `attacker->critChance_candidate` is `MonsterTable+0x05` (previously
  labeled an unidentified "small discrete enum" in
  `../formats/folio_bruti.md`) -- being read as a roll threshold here is
  a strong new candidate identity (crit chance), consistent with its
  previously-observed small, tiered values (3, 5, 10).
- This function only resolves **one** attacker-vs-defender exchange.
  **PROVEN melee-only**: live mGBA gdb-stub testing (breakpoint at
  `0x08017E44`) hit on an enemy's physical attack but did not hit when the
  player cast a spell -- spell/magic damage goes through separate,
  not-yet-traced code.

### The caller, and `activeFighterIndex`

**PROVEN**, from the same live debugging session. Breaking at
`ResolveMeleeAttack` during an enemy-attacks-player exchange captured
`r0=1, r1=0` -- confirming the parameter roles above (`r0`/`attackerIndex`
first, `r1`/`defenderIndex` second) against real execution, not just
static inference.

The call site is at US ROM `~0x08015BCE` (`bl 0x08017E44`), inside an
unnamed function starting at `0x08015574` (per `gbadisasm`'s own
disassembly; not independently seeded in `functions.us.cfg`, discovered
via reachability from elsewhere; not walked/named here). Immediately
before the call:

```c
if (fighter[?].fighterType == 0xFF &&           // acting fighter is an enemy
    someObjectState[0x60] == 1) {               // turn sub-state gate
    if (MonsterTable[monsterIndex].byte[0x14] <= 99) {  // see below
        int attackerIndex = g_pFightState->activeFighterIndex;  // FightState+0x106C
        int defenderIndex = *(targetSelection + 0x3A);          // caller's local state
        int damage = ResolveMeleeAttack(attackerIndex, defenderIndex);
        g_nLastDamage = damage;  // 0x0300274A, a scratch result slot
    }
}
```

`FightState+0x106C` (`activeFighterIndex` in the `FightState` struct) is
the same field `FUN_080100a0` (the monster AI action dispatcher, US
`0x080100A0`, not walked/named here) already reads as "whose turn it is"
-- two independent call sites agreeing is good corroboration for this
field's role.

**`MonsterTable+0x14` reframed.** This call site only invokes
`ResolveMeleeAttack` at all when the acting monster's `byte[0x14]` is
`<= 99` -- i.e. **not** exactly `100`. Combined with the earlier finding
(`../formats/folio_bruti.md`) that the same field also gates a
`Mt19937RandMax(99)` roll into what looked like a standalone taunt/
message branch, the fuller picture is: `0x14` is a per-monster chance
that this turn's action is *something other than* a normal physical
attack (always-something-else at `100`, never at `0`, otherwise a
`0x14`% chance). "Taunt/special message" was this doc's earlier guess at
what that something-else is; still not confirmed which specific action(s)
it can be.

### The attack-animation dispatcher (candidate, boundary confirmed, not fully walked)

Found by walking the live call stack (mGBA gdb backtrace) up from
`ResolveMeleeAttack`. Two small functions, newly seeded in
`functions.us.cfg` (previously undiscovered by either `gbadisasm` or
Ghidra -- the whole region was raw, un-analyzed bytes):

- `TickFighterAttackAnimState_candidate` (US `0x08015608`-`0x08015643`):
  reads a per-fighter-`Object` state byte (`param_1+0x8D`) and dispatches
  through a 26-entry jump table at `0x08015648` (mostly to a shared
  default at `0x8015F16`). Boundary PROVEN; this is almost certainly the
  attack-animation state machine (candidate name only).
- `UpdateFighterFlashEffect_candidate` (US `0x08015574`-`0x08015607`):
  called from the above; toggles a sprite flash/blink effect. Boundary
  PROVEN, semantics STRUCTURAL MATCH only.

**Not walked**: the jump table's case bodies. Case 0 (`0x080156B4`) leads
into the code that eventually calls `ResolveMeleeAttack` at `0x08015BCE`,
but its own true extent (and the other 25 cases') is unconfirmed --
tracing it hit another jump table almost immediately, and fully walking
26 cases to hard-rule-5 standard was out of scope for this pass. Left as
Ghidra plate comments at `0x08015608`/`0x080156B4`/`0x08015648` for a
future pass to pick up. Deeper call-stack frames above this (through
`0x08001FDA`, `0x0800091A`, `0x0802C822`, `0x0802C6B6`, into `main` at
`0x08029690`) were captured in the same backtrace but not investigated --
they're low-address, high-xref functions that look like generic engine
dispatch rather than battle-specific code.

## Damage application -- `ApplyDamageToFighter` (`sub_08017F98`, US `0x08017F98`)

**PROVEN**, decompiles cleanly in Ghidra once typed against the
`BattleFighter` struct.

```c
void ApplyDamageToFighter(short damage, uchar fighterIndex) {
    BattleFighter *fighters = *(BattleFighter **)(currentFighterStruct + 4);
    BattleFighter *f = &fighters[fighterIndex];
    f->hp -= damage;
    if (f->hp == 0 || f->hp > f->hp_max) {   // fainted, or underflowed past 0
        // ... sets a "battle needs UI update" flag, dispatches a
        // "fighter fainted" message (FUN_08010864 case 5) unless a
        // "message suppressed" flag (currentFighterStruct+0x14C4) is set,
        // then on faint: awards two accumulators (DAT_0300260E,
        // DAT_03002610) from MonsterTable+0x10/+0x12 respectively --
        // see "XP/reward payout" below -- and clears the fighter's HP/turn
        // state.
    }
}
```

### XP/reward payout -- new candidate identity for `MonsterTable+0x10`/`+0x12`

On a fighter fainting, `ApplyDamageToFighter` adds
`MonsterTable[monster].u16[0x10]` and `MonsterTable[monster].u16[0x12]`
into two separate running EWRAM accumulators (`0x0300260E`, `0x03002610`).
`../formats/folio_bruti.md` previously left these two fields completely
UNCONFIRMED (noting only that an earlier "candidate attack/defense" guess
for them was ruled out). Being added into what look like per-battle reward
accumulators on a kill is a strong new candidate: **XP and a second reward
currency (e.g. gold), paid out per accumulator**. Not confirmed which
accumulator is which, or what consumes them after battle; not investigated
further.

## Corrections to `../formats/folio_bruti.md`

The formulas above directly read several `BattleFighter` fields that
`../formats/folio_bruti.md` had labeled from `MonsterTable` content shape
and (weak, self-described-as-a-guess) player memory of one boss fight, not
from a traced reader. Now that a real reader exists, those labels are
corrected:

- `MonsterTable+0x04` (`BattleFighter+0x2B`): **not** "magic defense" --
  relabel **`accuracy`**, PROVEN. The doc's earlier Lupin Werewolf
  argument for "magic defense" (built jointly on `+0x03`/`+0x04`) no
  longer holds for `+0x04`'s half of that argument; the `+0x03`
  ("defense") side of it is now also unconfirmed by any traced reader
  (see `+0x2A` above) and should be treated as weaker than previously
  stated.
- `MonsterTable+0x06`/`+0x08` (`BattleFighter+0x30`/`+0x32`): **not**
  "level-range min/max" -- relabel **`damage_min`/`damage_max`**, PROVEN
  (fed directly into the damage roll). The old "monotonic with tier"
  evidence for a level-range reading is equally consistent with a
  damage-range reading, so this isn't a contradiction, just a correction
  now that a real reader settles it.
- `MonsterTable+0x05` (`BattleFighter+0x2C`): still UNCONFIRMED, but has
  a new strong candidate identity, **crit chance**, from its use as a
  bonus-damage roll threshold.

`tools/monsters/monster_codec.py` and `docs/formats/folio_bruti.md`'s
field table have not yet been updated to match -- this document is the
current source of truth for these three fields pending that follow-up
pass.
