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
- A community-written GameFAQs guide broke a symmetry `ResolveSpellAttack`
  alone couldn't: `PetrificusTotalus` and `Spongify` are structurally
  interchangeable in the disassembly (both absent from the effectiveness
  switch, both zero-power), so which of `SpellId` `1`/`6` is which had
  to be pinned down externally -- see `g_awSpellMpCost` below.

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

### `0x42` status-flags bits

Two independent lines of evidence now cover this bitfield: how
`ResolveMeleeAttack`/`ResolveSpellAttack` *read* it (below), and where
it's actually *written* -- a status-effect sub-table (**opcode `0x97`**)
inside the object/spell behavior-script bytecode interpreter at
`FUN_08018cf8` (`0x08018cf8`). That interpreter runs one opcode per
switch case against a per-object script buffer; it's the same engine
`TickObject_candidate`'s callback dispatch reaches (see
`ThumbInterworkVeneer_bx_r1` above) and is not battle-specific by
itself -- opcode `0x97`'s cases are the ones spell/attack scripts call
to apply named battle status effects. All 8 bits are claimed by a
combat-mechanical effect below, several PROVEN via a `ShowBattleMessage`
call immediately after the flag write.

`FightState` field **`field_0x14a8`** is "which status to announce
after the current damage number," consumed by
`ShowBattleMessage(CriticalHit, 0, field_0x14a8)` calls throughout (case
5's sub-dispatch; see the case-5 row in the dialog-text table below).
Defaults to `0x12` (18, "none"). Opcode `0x97`'s status-applying cases
set it to a specific sub-case value right where they set the
corresponding bit -- this is the evidence behind bits `0x02`/`0x10`
below (`0x04`/`0x08`/`0x01` are PROVEN via a direct adjacent
`ShowBattleMessage` call instead, not `field_0x14a8`).

- **bit `0x01`** = **Hidden** status. PROVEN: opcode `0x97` cases 8/9
  (`0x0801a7b6`/`0x0801a7e8`) OR this bit in, then call
  `ShowBattleMessage(Hidden, ...)` (case 9 differs only in
  `ShowBattleMessage`'s second argument, 0 vs 1). Read on the
  *defender* in `ResolveMeleeAttack`: reduces the attacker's effective
  accuracy by 25, and gates the bonus-damage/crit check further down
  (must be clear for that check to run) -- consistent with "target is
  hidden from view." **Confirmed spell: Fumos** -- Fumos makes a target
  harder to hit (Uno: one ally, Duo: the whole party), matching bit
  `0x01`'s accuracy-reduction effect exactly. The game's spell glossary
  lists 10 named spells
  (`Flipendo`, `Informus`, `Verdimillious`, `Diffindo`, `Incendio`,
  `WingardiumLeviosa`, `PetrificusTotalus`, `Glacius`, `Fumos`,
  `Spongify`), but `SpellId` only covers 8 values (`0`-`7`). `Informus`
  is cast in battle too, but from the battle menu's top level (a sibling
  entry to "Cast a Spell," not part of the spell submenu), so it
  wouldn't set `bSpellId` at all -- the `bSpellId == 8` sentinel only
  appears inside the spell-casting code path
  (`TickPlayerActionState_candidate` case `0x1a`/`FUN_080161fe`), which is
  reached from the spell submenu, leaving `Fumos` (a submenu spell) as
  the sole candidate. Not traced to an opcode `0x97` case 8/9 call site
  from that sentinel path -- the spell identity is confirmed by content,
  the call site is not.
- **bit `0x02`** = **Poisoned**. PROVEN: opcode `0x97` case 5
  (`0x0801a71c`), gated on `(bStatusFlags & 0x06) == 0` (i.e. not
  already `Poisoned` or `PoisonImmune`), sets the bit alongside
  `FUN_0801b590` (a particle/VFX spawn) and `field_0x14a8 = 3` -- sub-case
  `3` of `ShowBattleMessage`'s case-5 dispatch is "Harry is poisoned."
  (see the dialog-text table below). Not read by either damage-resolution
  function (poison presumably applies its own per-turn damage elsewhere,
  not traced).
- **bit `0x04`** = **PoisonImmune**. Set by opcode `0x97` case 7
  (`0x0801a7ac`), silently -- and it's exactly the bit that, alongside
  `Poisoned` itself, gates case 5 above (`& 0x06`) from applying poison
  again. This is a structural mirror of `Paralyzed`/`0x80` below (same
  "status bit + immunity bit blocks re-apply" shape). **PROVEN source:
  Harry's card index `5`** in `g_abHarryCardEffectId_candidate`
  (`0x080514c8`) is effect id `18`, whose script contains opcode `0x97`
  case `7` three times -- a real traced call site (see the "Poison
  Immunity" writeup below), not just an effect-to-description match.
- **bit `0x08`** (checked on the *attacker* in `ResolveMeleeAttack`):
  independently contributes one halving of the computed damage (see
  below). PROVEN as **Attack Weakened**: opcode `0x97` case 6
  (`0x0801a790`) OR's this bit in, then calls
  `ShowBattleMessage(AttackWeakened, 0, 0)` -- matches
  `BattleMessageCode.AttackWeakened` (15, "The opponent's attacks are
  weakened.") exactly. **Spongify weakens one enemy's attacks** --
  matches this bit's effect exactly, but `Spongify` (`SpellId` `1`;
  `g_abSpellEffectId_candidate` effect ids `[38,38,38]`) traces to opcode
  `0x97` cases `0xc`/`0xd` instead, not case `6` (see the `0x10` bullet
  and the `Poison Immunity`/XP writeup below for what those cases
  actually do). `AttackWeakened`'s real effect id (`29`) doesn't appear
  in `g_abSpellEffectId_candidate`, `g_abHermioneLectureEffectId_candidate`,
  or `g_abHarryCardEffectId_candidate` -- Spongify's bStatusFlags write
  is unlocated, same class of gap as `Informus`'s Folio Bruti write
  below. `Poisoned`'s source (effect id `27`) is equally unconfirmed.
- **bit `0x10`** = **Paralyzed**. PROVEN: applied through a dedicated
  helper, `FUN_0801b430` (`0x0801b430`), called from several opcode
  `0x97` cases (10, 0x11, 0x12, part of 0x16/0x17). It only sets the bit
  if `bStatusFlags & 0x90 == 0` (i.e. not already paralyzed, nor bit
  `0x80` set); otherwise it fires `ShowBattleMessage(ImmuneToParalysis,
  ...)` when its `param_2` is nonzero. Case `0x16`'s call site sets
  `field_0x14a8 = 4` on success -- sub-case `4` of `ShowBattleMessage`'s
  case-5 dispatch is "Harry is paralyzed."/"The opponent is paralyzed!"
  (same `field_0x14a8` mechanism as `Poisoned` above). A third parameter
  to `FUN_0801b430` (varies per call site: `0x19`,
  `0x63`, `0x50`, ...) is stored to `fighter+0x44`, not consumed by RNG
  inside this function -- likely a duration or an already-resolved
  chance, not traced further. Not read by
  `ResolveMeleeAttack`/`ResolveSpellAttack` (paralysis presumably gates
  action/turn selection elsewhere, not the damage formula).
  **Case `10` is conditionally gated, cases `0x11`/`0x12` are not** --
  confirmed by reading each call site's `param_2` (`FUN_0801b430`'s 2nd
  arg): case `10` (`0x0801a818`) passes `0` (or `1` only if the target
  fighter's roster byte reads `0xFF`, a sentinel case), while cases
  `0x11`/`0x12` (`0x0801a83e`/`0x0801a84a`) hardcode `1`. Inside
  `FUN_0801b430`, the whole apply-or-skip block is additionally gated by
  `(DAT_0300276e != 0 && DAT_0300276e != 0x3e9) || param_2 != 0` -- i.e.
  with `param_2 == 0` (case `10`'s normal path), paralysis only applies
  when `DAT_0300276e` (written only by `FUN_08018b70`'s `param_6`, the
  effect-trigger's caller-supplied 6th argument -- not traced further)
  holds some other value; cases `0x11`/`0x12`'s `param_2 == 1`
  unconditionally satisfies the `||`, skipping that check entirely. So
  case `10` is genuinely conditional on external state (a real
  "chance"/context gate) while `0x11`/`0x12` always apply (subject only
  to the immunity-bit check both paths share). **PROVEN source:
  PetrificusTotalus** -- `SpellId` `6`'s effect ids
  (`g_abSpellEffectId_candidate` `[33,34,33]`, indexed `spellId*3 +
  castLevel`) trace to opcode `0x97` case `10` -- **confirmed directly
  against the extracted script text** for *both* effect ids `33` and `34`
  (`data/scripts/SpellPetrificusTotalusUno.txt`/`SpellPetrificusTotalusDuo.txt`,
  see `docs/formats/object_script.md`): both unconditionally contain a
  `StatusEffect 10 0 0` instruction, so both apply the same
  conditionally-gated paralysis -- correcting an earlier, unverified
  claim in this doc that effect id `34` had no opcode `0x97` call at all.
  The two scripts differ only in animation timing (effect id `34` has an
  extra root-vs-spawned-copy branch skipping an initial flash animation,
  and uses different animation-frame operand values) -- not in
  whether/how paralysis is applied. Named `Uno`/`Duo` (the in-game names
  for cast levels `0`/`1`) rather than `Duo`/`Tria`: castLevel `1`
  (`Duo`) is uniquely effect id `34`, so that association is solid, but
  castLevel `2` (`Tria`) reuses castLevel `0` (`Uno`)'s effect id `33`
  verbatim -- and whether PetrificusTotalus even has a real, player-
  reachable `Tria` cast is unconfirmed. `g_awSpellMpCost`'s row for this
  spell (`10/15/20`) has a distinct nonzero value at the `Tria` slot,
  suggestive but not proof; the community GameFAQs guide cross-check
  above (see "External, unverified leads") only ever cited its `Uno`/
  `Duo` costs, never a third value for `Tria`. So effect id `33` is named
  `Uno` for its primary, definitely-real association, with the `Tria`
  slot's reuse of the same script left as a documented fact here rather
  than folded into the filename.
  `PetrificusTotalus` and `Spongify` share
  `SpellId` values `6`/`1` in a way that isn't decidable from
  `ResolveSpellAttack`'s effectiveness switch alone (both spells are
  absent from it identically) -- `g_awSpellMpCost` below is what pins
  `PetrificusTotalus=6` specifically, and this bit's opcode `0x97` case
  `10` (not case `0xc`/`0xd`, which is what `SpellId` `1` traces to
  instead) is the corroborating evidence: only the `6`/`10` pairing
  produces a paralysis effect, matching what `PetrificusTotalus` is
  known to do. **Also candidate: Harry's Folio Universitas card index
  13** (of 16, `bSlotParam` `13` in `g_abHarryCardEffectId_candidate`)
  -- its effect script (effect id `47`) also contains opcode `0x97` case
  `0x12`, another bare `FUN_0801b430()` call, this time the
  unconditional-apply variant -- a plausible second source for "opponent
  loses a turn," not traced to a specific card name.
- **bit `0x20`** = **DefenseBoost** (checked on the *defender* in
  `ResolveMeleeAttack`): independently contributes one halving of the
  computed damage. Set by opcode `0x97` case 0xb (`0x0801a8e4`), no
  message attached -- a silent status flag matching a passive
  defense buff. Named for the effect rather than a specific spell/card
  since it's confirmed generic (see below), matching the
  effect-based naming of `Hidden`/`Poisoned`/etc. **PROVEN source:
  Hermione's "Be More Careful"** -- `g_abHermioneLectureEffectId_candidate`
  (`0x0805150d`, 3 entries, one per lecture) index `0` is effect id `49`,
  whose script contains opcode `0x97` case `0xb` -- a real traced call
  site, not just an effect-to-description match. A second, independent
  script (effect id `36`) also applies this same bit but doesn't match
  any entry in the 16-slot `g_abHarryCardEffectId_candidate` table read
  so far, so it's not yet pinned to a specific card; **Harry's "Girding
  All"** (party-wide "Increases all party members' physical defense")
  remains the leading candidate for it by elimination and effect match,
  since no dedicated party-wide status-loop exists elsewhere in opcode
  `0x97` (the only party-wide loops there, cases `0xd`/`0xe`, target
  *enemies* via `Object+0x115`, not `bStatusFlags`) -- a card applying
  this bit once per party member from its own script remains the natural
  implementation. The two halving bits (attacker's `0x08`, defender's
  `0x20`) stack multiplicatively: neither set -> no change; exactly one
  set -> damage `>>= 1`; both set -> damage `>>= 2` (quartered).
- **bit `0x40`** = **SpellPowerBoost**: read by `ResolveSpellAttack` as
  a `x4/3` power boost and a crit-chance boost (see below). Set by
  opcode `0x97` case 0x13 (`0x0801aa0a`), no message attached -- same
  shape as case 0xb. **PROVEN source: Hermione's "Proper Wand
  Technique"** -- `g_abHermioneLectureEffectId_candidate` index `1` is
  effect id `51`, whose script contains opcode `0x97` case `0x13`, a
  real traced call site. No second source found sharing this bit.
- **bit `0x80`**: only observed as part of `FUN_0801b430`'s `0x90` gate
  mask (`0x80 | 0x10`) -- blocks (re-)applying `Paralyzed`, the same
  structural role `PoisonImmune` (`0x04`) plays for `Poisoned` (`0x02`).
  No spell/card identified; a generic "paralysis immunity" effect is the
  natural guess by symmetry with `PoisonImmune`, but nothing else
  confirms it. UNCONFIRMED.

**Poison Immunity, PROVEN source.** `g_abHarryCardEffectId_candidate`
(`0x080514c8`, 16 entries, one per Folio Universitas card, `bSlotParam`
`0`-`15`) index `5` is effect id `18`, whose script contains opcode
`0x97` case `7` (`PoisonImmune`) **three times** -- consistent with
"Gives all party members immunity to poison for one magical encounter"
applying the flag once per non-caster party member. This is Harry's
card index `5`.

**On the "extra XP" special move**: doesn't fit `bStatusFlags` -- traced
to a different mechanism instead. Hermione's "Good Study Habits" is
`g_abHermioneLectureEffectId_candidate` index `2`, effect id `50`; its
script contains opcode `0x97` case `3` (`field_0x1480 = 2`, via
`LAB_0801ab2a`), not a `bStatusFlags` write. `g_abHarryCardEffectId_candidate`
index `11`, effect id `14`, uses the same family (case `2`,
`field_0x1480 = 1`) -- the leading candidate for Harry's XP-bonus card,
and if so it **does** share a mechanism with Hermione's move, just
`field_0x1480` (an unidentified `FightState` field) rather than
`bStatusFlags`. `field_0x1480` itself is not traced further; not
obviously connected to the `g_nRewardAccum1`/`g_nRewardAccum2` payout in
`ApplyDamageToFighter` (see "XP/reward payout" above), which remains an
alternative, untraced possibility.

**How the effect-id -> script trace works**, for reproducing/extending
this: `FUN_08018b70(effectId, ...)` (the anim/effect trigger already
documented above) calls `FUN_08018be0(effectId, ...)`, which spawns a
new `Object` and sets `Object+0x62 = effectId` and `Object+0x98` to a
generic dispatcher (`0x08018cc1`); `TickObject_candidate` then
interprets that object's script every tick via `FUN_08018cf8`
(`0x08018cf8`), which looks up the script buffer as
`g_apEffectScripts_candidate[Object+0x62]` --
`g_apEffectScripts_candidate` (`0x0805b978`) is an array of 60+ script
pointers (at least `0`-`59` populated), one per effect id. Each opcode's
length is looked up in a 256-entry table at `0x08054f34`
(`instruction length = table[opcode] + 1` bytes, including the opcode
byte itself); walking a script from its pointer with that table finds
every opcode `0x97` instance and its case (sub-case) byte. Spell/card
effect-id tables (`g_abSpellEffectId_candidate` for the 8 real spells,
`g_abHermioneLectureEffectId_candidate` for Hermione's 3 moves,
`g_abHarryCardEffectId_candidate` for Harry's 16 cards) then map a
specific spell/card to one of those effect ids.

Note: opcode `0x97`'s case numbering above is the *inner* switch's case
index (the effect-type byte read from the script), distinct from
`FUN_08018cf8`'s own outer opcode number (`0x97`) that selects this
whole sub-table.

## Attack resolution -- `ResolveMeleeAttack` (`sub_08017E44`, US `0x08017E44`)

**PROVEN**, traced end-to-end from the on-disk `gbadisasm` output
(`build/us/full_disasm.s`) and confirmed via Ghidra decompilation
against the typed `BattleFighter` struct.

Signature: `int ResolveMeleeAttack(int attackerIndex, int defenderIndex)`.

```c
int ResolveMeleeAttack(int attackerIndex, int defenderIndex) {
    BattleFighter *fighters = g_pFightState->pFighters;
    BattleFighter *attacker = &fighters[attackerIndex];
    BattleFighter *defender = &fighters[defenderIndex];

    // hit/miss
    int accuracy = attacker->bAccuracy;
    if (defender->bStatusFlags & 0x01)
        accuracy -= 25;
    if (Mt19937RandMax(99) >= accuracy)
        return 0;                                    // miss

    // base damage, scaled by defender's defense factor
    int damage = Mt19937RandRange(attacker->wDamageRollMin, attacker->wDamageRollMax);
    damage = damage * defender->bDefenseFactorPercent_notFromMonsterTable / 100;

    // halving (attacker bit 0x08 and defender bit 0x20 each independently halve)
    if (attacker->bStatusFlags & 0x08)
        damage >>= (defender->bStatusFlags & 0x20) ? 2 : 1;
    else if (defender->bStatusFlags & 0x20)
        damage >>= 1;
    damage += 1;                                       // rounding

    // bonus-damage / crit-style check
    if (damage != 0 && !(defender->bStatusFlags & 0x01)) {
        int roll = Mt19937RandMax(100);
        if (roll > 100 - attacker->bCritChance_candidate) {
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
- `attacker->bCritChance_candidate` is `MonsterTable+0x05` (previously
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

All 27 case bodies are traced to genuine termination -- see "The
attack-animation state dispatcher" section below. Case 0 (`0x080156B4`)
leads into the code that calls `ResolveMeleeAttack` at `0x08015BCE`.
Deeper call-stack frames above this (through
`0x08001FDA`, `0x0800091A`, `0x0802C822`, `0x0802C6B6`, into `main` at
`0x08029690`) were captured in the same backtrace but not investigated --
they're low-address, high-xref functions that look like generic engine
dispatch rather than battle-specific code.

## Damage application -- `ApplyDamageToFighter` (`sub_08017F98`, US `0x08017F98`)

**PROVEN**, decompiles cleanly in Ghidra once typed against the
`BattleFighter` struct.

```c
void ApplyDamageToFighter(short damage, uchar fighterIndex) {
    BattleFighter *f = &g_pFightState->pFighters[fighterIndex];
    f->wHp -= damage;
    if (f->wHp == 0 || f->wHp > f->wHp_max) {   // fainted, or underflowed past 0
        g_pFightState->dwUiUpdateNeeded = 1;
        if (g_pFightState->bFaintMessageCount_candidate == 0)
            ShowBattleMessage(CriticalHit, fighterIndex, 2);

        // record the roster slot as fainted, in the first free slot
        int slot = 0;
        if (g_anFaintedRosterIndices[0] != -1)
            while (g_anFaintedRosterIndices[slot] != -1 && slot < 4) slot++;
        g_anFaintedRosterIndices[slot] = f->bRosterIndex;

        // reward payout -- MonsterTable+0x10/+0x12, indexed by roster index
        g_nRewardAccum1 += MonsterTable[f->bRosterIndex].u16[0x10];
        g_nRewardAccum2 += MonsterTable[f->bRosterIndex].u16[0x12];

        f->wHp = 0;
        f->nSelectedTargetIndex_candidate = -1;
        SetFighterAttackAnimState_candidate(f->pObject, 1);
    }
}
```

`ShowBattleMessage(CriticalHit, ...)` firing here (guarded by
`bFaintMessageCount_candidate == 0`) rather than `FaintResult` is as
decompiled; not yet reconciled with why the faint path shows a
"critical hit" message code.

### XP/reward payout -- new candidate identity for `MonsterTable+0x10`/`+0x12`

On a fighter fainting, `ApplyDamageToFighter` adds
`MonsterTable[fighter.bRosterIndex].u16[0x10]` and
`.u16[0x12]` into two separate running EWRAM accumulators
(`g_nRewardAccum1` at `0x0300260E`, `g_nRewardAccum2` at `0x03002610`).
The reads resolve to `0x0804F420`/`0x0804F422` with a `0x18`-byte stride,
i.e. literally `MonsterTable + 0x10`/`+0x12` (`MonsterTable` itself is
`0x0804F410`, stride `0x18`, per `../formats/folio_bruti.md`) --
confirming the indexing is by roster/monster index directly into
`MonsterTable`.
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
field table match these corrected labels.

## The attack-animation state dispatcher -- `TickFighterAttackAnimState_candidate` (`0x08015608`)

The dispatcher's boundary is **PROVEN and fully walked**: all 27 case
bodies trace to genuine termination, matching gbadisasm's own
single-function span (`0x08015608`-`0x08015F4F`, confirmed against
`build/us/full_disasm.s`; no `thumb_func_start` anywhere in between). No
second indirect-jump pattern exists anywhere in the span.

The shared epilogue at `0x08015F16` (reached via `bl`-as-branch, see the
"attack-animation dispatcher" note above) decompiles cleanly once each
`bl 0x08015F16` call site and the epilogue's own `pop {r0}; bx r0`
(`0x08015F24`) get Ghidra instruction-level flow overrides (`Call-Return`
and `Return` respectively) -- Ghidra can't infer these are non-returning
on its own since the epilogue manually pops the *caller's* original
return address into a register instead of using `pop {..., pc}`/`bx lr`.
With those applied, the full 27-case `switch` decompiles correctly.

Three callees identified from decompiling the dispatcher body (all
`_candidate`, structurally strong but not proven identities):

- **`ShowBattleMessage`** (`0x08010864`) -- dispatches on a message code
  (param 1) plus two context args; every case ends by picking a dialog
  text ID (keyed off fighter type/roster index) and tail-calling
  `GetDialogText`. **Case 6** handles fainted messages (checks
  `bFaintMessageCount_candidate`), while case 5 handles damage-number
  text and does the `param_2 < 1000` check matching the `+999` sentinel
  documented in `ResolveMeleeAttack` above.
- **`ShowDamageNumber_candidate`** (`0x08017B5C`) -- stores a damage
  value onto the target's sprite `Object+0x62` and triggers a state
  change via `SetFighterAttackAnimState_candidate`.
- **`SetFighterAttackAnimState_candidate`** (`0x08001E7C`) -- writes
  directly to `Object+0x8D` (the exact byte `TickFighterAttackAnimState_candidate`
  switches on) and sets the `+0x90` bit-`0x01` flag several case bodies
  check. This is the dispatcher's own state-transition setter.

**"Tick" is PROVEN**, from the caller chain traced via `gbadisasm`'s
ground truth plus Ghidra decompilation:

- `InitMonsterBattleActor` (`0x08014C88`) writes
  `TickFighterAttackAnimState_candidate`'s address into `Object+0x98`
  (`build/us/full_disasm.s` ~line 22461: `ldr r0, =sub_08015608` / `str
  r0, [r1]` where `r1 = object+0x98`) -- a callback-registration slot,
  not a direct call.
- **`TickObject_candidate`** (`0x08001FDA`) is a per-object
  per-update-pass function: it reads `Object+0x98`, and if non-null (and
  a gating check, `FUN_0800359c`, passes), calls
  **`ThumbInterworkVeneer_bx_r1`** (`0x0804A2C4`, see
  `krawall.md`) to invoke it.
- **`TickObjectList_candidate`** (`0x0800091A`) walks a linked list of
  all active objects, calling `TickObject_candidate` once per object per
  call.

The call chain is `TickObjectList_candidate` -> (per object)
`TickObject_candidate` -> `ThumbInterworkVeneer_bx_r1` ->
`TickFighterAttackAnimState_candidate`, a generic
per-object-per-frame callback dispatch. "AttackAnimState" is arguably
too narrow given case `0x1a`'s broader turn/action-execution content
(target selection, `ResolveMeleeAttack`, message/reward dispatch) -- not
renamed further here, flagged as a scope question rather than a naming
error.

**`FUN_0800359C`** (the `TickObject_candidate` gate) returns true
iff `g_dwCurrentGameMode_candidate` (`0x03003EF4`) `!= 0x18` AND it equals
`g_dwPendingGameMode_candidate` (`0x03003F18`, via `FUN_0802c860`'s
not-equal bit-trick) -- i.e. "no mode transition in flight, and not in
mode `0x18`". `g_dwCurrentGameMode_candidate` has enormous fan-out (80+
xrefs ROM-wide) consistent with being the central game-mode/scene state
variable; specific mode values (including `0x18`) not identified --
would need tracing the broader top-level state machine, out of scope
here.

**`FightState` struct corrections/additions**, from decompiling
`TickFighterAttackAnimState_candidate` and `ShowBattleMessage`:

- `+0x147E` -> **`bActionDelayCounter_candidate`** (u8): decremented once
  per `Tick` call (bits `0x20`/`0x40` of a per-fighter status byte each
  drive one decrement path), gates further action once it hits 0. Set to
  5/10/20 depending on branch. Candidate: frames-remaining delay before
  an action/animation actually fires.
- `+0x14AC`..`+0x14C4` -> **`aFaintMessages_candidate`**, a 6-entry
  `FaintMessageEntry_candidate[6]` array (`{u16 wDamage; u8 bEffectId; u8
  bFlag;}`, 4 bytes/entry -- the 6-entry count falls out exactly from
  `(0x14C4 - 0x14AC) / 4`, not a guess). One entry per queued
  fainted-fighter message.
- `+0x14C4` -> **`bFaintMessageCount_candidate`**: an incrementing array
  write-cursor/count into `aFaintMessages_candidate`. The `== 0` gate in
  `ApplyDamageToFighter` means "no messages queued yet".

### `BattleFighter+0x00` (`bFighterType`) -- enum, `FighterType` -- PROVEN

`Harry=0, Hermione=1, Ron=2, Buckbeak=3, Enemy=0xFF`. No `_candidate`
suffix: every value is backed by an exact string match, not inference --
"Harry"/"Hermione"/"Ron" literally appear at `0x8ec`-`0x8ee`, "Buckbeak"
at `0xa3d`, and the same 0-3 mapping is independently corroborated
across six different `ShowBattleMessage` cases (2, 4, 7, 8,
0xD, 0xE) plus its default section's explicit `==1`/`==2`/`==0` checks,
with no contradictions found anywhere. `Enemy=0xFF` was already PROVEN
per the `BattleFighter` struct table above. Applied to
`BattleFighter.bFighterType` in Ghidra.

### `messageCode` -- enum, `BattleMessageCode`

Applied to `ShowBattleMessage`'s first parameter, named from
the case table below: `SpellLevelUp=0, EscapeBlocked=1,
SpecialMoveAnnounce=2, SpecialAbilityText=3, ActionAnnounce=4,
CriticalHit=5, FaintResult=6, ItemUseAnnounce=7, StatusRestore=8,
SpCost=9, MpCost=10, Victory=11, Defeat=12, CantMove=13,
CanMoveAgain=14, AttackWeakened=15, Hidden=16, ImmuneToParalysis=17`.
`SpecialAbilityText` (3) doesn't get its own visible `case` label in the
decompile -- it shares a body with the switch's trailing default block,
a decompiler-view limitation, not a boundary error (confirmed correct
via the real jump table, see below).

### Functions called from `ShowBattleMessage`, partially identified

- **`PlaySoundEffect_candidate`** (`0x0803FF70`) -- called by
  `SpellLevelUp` (id `0x1a`). Looks up `DAT_08fb0cc4[soundId]` and
  passes it into `FUN_08047dfc`, which sits deep in Krawall's driver
  cluster (`0x08046000`-`0x08048000`, see `krawall.md`) and manipulates
  a full per-channel state array -- closer in shape to a Krawall
  module-switch (`kramPlayModule`-equivalent) than a one-shot SFX
  trigger.
- **`PrepareBattleMessageDisplay_candidate`** (`0x08012FD4`) -- called
  at the top of every `ShowBattleMessage` case. Draws/positions the
  message window and clears a status bit on every active fighter's
  sprite `Object` via **`ClearFighterObjectFlag_candidate`**
  (`0x08012CB4`), which indexes a 7-slot array,
  **`g_apFighterObjects_candidate`** (`0x03002668`, `Object*[7]`, likely
  one slot per active `BattleFighter`).
- `0x0804A2C4` (**`ThumbInterworkVeneer_bx_r1`**) is one of a family of
  generic ARMv4T-Thumb interworking veneers (`0x0804A2C0`-`0x0804A2E4`,
  one `bx rN` stub per register -- Thumb has no `blx reg`), documented
  in `krawall.md`; Krawall's mixer uses the same family. Reached from
  `TickObject_candidate`'s callback dispatch.

No `_candidate` suffix: every one of the 18 cases has real, verified
dialog text (case table below), including all 5 of case 5's inner
sub-cases. The one remaining gap -- case 4's third call site (`0x08010c92`) passing
the fighter struct pointer directly as a textId, likely dead code -- is
a single unexplained instruction, not a gap in the case identities
themselves, so it doesn't block dropping the suffix here.

### `TickPlayerActionState_candidate` (`0x0801602C`) -- second `+0x8D` dispatcher

Same structural pattern as `TickFighterAttackAnimState_candidate`: reads
`Object+0x8D`, 27-entry jump table, shared epilogue reached via
`bl`-as-branch (`0x08017B42`). Distinct case targets at 0, 1, 2, 5, 15,
21, 26; default for the rest. Found while tracing `ShowBattleMessage`'s
callers looking for the player-spell damage formula.

Case 21, **`HandleScriptedDamageEvent_candidate`** (`0x08016E64`), spans
both `0x08016E64` and `0x0801732C` -- one function, not two (the
`unaff_rX` shared-epilogue false-split pattern documented elsewhere in
this codebase). Dispatches on a status byte (`Object+0x60`) into 5 sub-states
(1-5), each calling `ApplyDamageToFighter` with a **fixed** damage
constant (5, 20, 20, 45) -- no RNG roll. Looks like scripted/special-
event damage (e.g. a cutscene or forced outcome), not the normal
per-turn combat formula. No call to `Mt19937RandRange` (the RNG damage
roll used by `ResolveMeleeAttack`) appears anywhere in this dispatcher's
address range (`0x08016000`-`0x08017FFF`) -- the real player spell-damage
formula, if randomized, is not in this function; the other case targets
(`0x080160FC`, `0x08017A7C`, `0x080161A2`, `0x08017ADE`, `0x0801618A`,
`0x080161FE`) haven't been walked yet.

## Player spell/action damage -- `ResolveSpellAttack` (`0x08017C24`)

Found via `TickPlayerActionState_candidate`'s case `0x1A`, which calls it
as `ResolveSpellAttack(attackerIndex, targetIndex)` and stores
the result into `DAT_0300274a` -- the same scratch slot
`ResolveMeleeAttack`'s caller uses. This is the Harry/Hermione/Ron
damage path (`ResolveMeleeAttack` is proven melee-only and covers
enemies/Buckbeak instead); structurally similar in shape to
`ResolveMeleeAttack` but a genuinely different formula, not a shared
routine.

```c
int ResolveSpellAttack(int attackerIndex, int targetIndex) {
    BattleFighter *attacker = &g_pFightState->pFighters[attackerIndex];

    // miss check -- skipped entirely (guaranteed hit) once
    // g_bSpellMissStreak reaches 2
    if (g_bSpellMissStreak < 2 &&
        Mt19937RandMax(100) >= attacker->bAccuracy) {
        g_bSpellMissStreak++;
        power = 0;
    } else {
        g_bSpellMissStreak = 0;

        // base power: two tables indexed by (spellId*3 + spellLevel),
        // second one scaled by the attacker's own stat, divided by 9
        int idx = attacker->bSpellId * 3 + attacker->bSpellLevel;
        power = g_awSpellPowerBase[idx]
              + divsi3_thumb(g_awSpellPowerScale[idx] * attacker->bStat_attack, 9);

        // per-character modifier
        if (attacker->bFighterType == Hermione) power = power * 17 / 16;
        else if (attacker->bFighterType == Ron)  power = power * 15 / 16;
        // Harry: no modifier

        if (power == 0) power = 1;
        if (attacker->bStatusFlags & 0x40) power = power * 4 / 3;   // 0x40 = ProperWandTechnique
    }

    if (power == 0) return 0;

    // crit-chance scaling factor from the attacker's own stat, capped at 12
    uint critScale = attacker->bStat_attack < 2 ? 0
                     : min(12, (attacker->bStat_attack >> 1)
                               + ((attacker->bStatusFlags & 0x40) ? attacker->bStat_attack >> 2 : 0));

    // target's effectiveness against the cast spell -- a switch on
    // bSpellId picks one of the 6 aSpellEffectiveness slots (slot index
    // is not spellId itself; see the mapping below). PetrificusTotalus
    // and Spongify (the two "always 100%" spells per folio_bruti.md) have
    // no case at all and return 0 damage, matching both power tables
    // being zero at those two SpellId indices
    int slot;
    switch (attacker->bSpellId) {
        case Flipendo:           slot = 0; break;
        case Verdimillious:      slot = 2; break;
        case Diffindo:           slot = 5; break;
        case Incendio:           slot = 1; break;
        case WingardiumLeviosa:  slot = 3; break;
        case Glacius:            slot = 4; break;
        default: return 0;   // PetrificusTotalus, Spongify
    }
    int effectiveness = target->aSpellEffectiveness[slot];

    int roll = Mt19937RandMax(100);
    bool crit = (97 - critScale) < roll;
    if (crit) power *= 2;

    int damage = (effectiveness * power) / 100 + 1;
    if (crit) damage += 0x3E9;   // 1001 -- sentinel, same convention as ResolveMeleeAttack's +999
    return damage;
}
```

### `BattleFighter+0x3C`/`+0x3D` -- `bSpellId` (enum `SpellId`) / `bSpellLevel`

Added to the struct at the offsets `ResolveSpellAttack` reads.
`bSpellLevel` (0-2) explains `ShowBattleMessage`'s
`SpellLevelUp` case -- spells have 3 power tiers, and that case's
`FUN_0803FF70`-driven jingle is almost certainly what plays when this
field increments. `bSpellId`'s 8 values were derived from
`ResolveSpellAttack`'s own `aSpellEffectiveness` switch: the
two values with **no case at all** (1 and 6) are exactly the two power
tables' zero entries below, matching `folio_bruti.md`'s two "always 100%
effective, not a per-monster stat" spells (Petrificus Totalus, Spongify)
-- `Flipendo=0, Spongify=1, Verdimillious=2, Diffindo=3, Incendio=4,
WingardiumLeviosa=5, PetrificusTotalus=6, Glacius=7`. This is the game's
own internal spell-ID ordering -- notably different from both
`folio_bruti.md`'s spell-index order (used for the Folio Bruti UI) and
`aSpellEffectiveness`'s storage order, so don't assume any of the three
line up. Which of values `1`/`6` is `PetrificusTotalus` vs. `Spongify`
isn't decidable from the switch alone (both are absent from it
identically) -- PROVEN via `g_awSpellMpCost` below instead.

### The two base-power tables, decoded

`g_awSpellPowerBase` (`0x080538EC`) and
`g_awSpellPowerScale` (`0x08053928`), both `ushort[24]`
indexed `spellId*3 + spellLevel`. `g_awSpellPowerScale` is the
term multiplied by the attacker's `bStat_attack` and divided
by 9 (via `divsi3_thumb`, the Thumb-mode signed-division runtime --
**not** a spell-specific scaling helper, same algorithm shape as the
already-documented `__rt_divsi3`/`udivsi3_thumb`).

| Spell | lvl0 base/scale | lvl1 base/scale | lvl2 base/scale |
|---|---|---|---|
| Flipendo | 10 / 4 | 20 / 8 | 15 / 10 |
| Spongify | 0 / 0 | 0 / 0 | 0 / 0 |
| Verdimillious | 15 / 6 | 25 / 12 | 20 / 14 |
| Diffindo | 30 / 18 | 30 / 19 | 40 / 20 |
| Incendio | 23 / 8 | 35 / 16 | 45 / 18 |
| WingardiumLeviosa | 35 / 20 | 45 / 21 | 55 / 22 |
| PetrificusTotalus | 0 / 0 | 0 / 0 | 0 / 0 |
| Glacius | 30 / 18 | 40 / 20 | 45 / 20 |

Power generally grows with level as expected, though not always
monotonically (Flipendo's base term dips 20->15 from level 1 to 2,
offset by its scale term still growing 8->10) -- not investigated
further whether that's deliberate balancing or two independent curves
that just happen to combine this way.

### Spell MP cost -- `g_awSpellMpCost` (`0x08053964`), PROVEN

`ushort[24]`, indexed `spellId*3+level`, same shape as the power tables.
Deducted directly from `BattleFighter.wMp` in
`TickPlayerActionState_candidate` case `0x1A` -- all spells share one MP
pool, no separate per-spell resource type. Confirmed against a
community-written GameFAQs guide's real per-spell MP costs (see the
attribution note near the top of this document): all 6 unambiguous
spells match exactly, and `PetrificusTotalus`'s `Uno`/`Duo` costs
(`10`/`15`) match `SpellId` value `6`'s row here, which is what proved
`PetrificusTotalus=6`/`Spongify=1` rather than the reverse:

| Spell | lvl0/1/2 cost |
|---|---|
| Flipendo | 0/10/20 |
| Spongify | 0/0/0 |
| Verdimillious | 3/15/25 |
| Diffindo | 10/0/0 |
| Incendio | 6/20/30 |
| WingardiumLeviosa | 20/30/40 |
| PetrificusTotalus | 10/15/20 |
| Glacius | 15/25/0 |

Its companion byte array at the same index,
`g_abSpellEffectId_candidate` (`0x080538B0`), is a per-`(spellId,level)`
animation/VFX id fed into `FUN_08018b70` (the same anim-trigger function
used throughout this code) -- not a resource-type selector.

### Battle item/equipment database -- `g_pBattleItems_candidate` (`0x08060F08`)

78-entry array of `BattleItemEntry_candidate` (0x34-stride: type, param,
two unknown dwords, a name text ID, three icon/sprite pointers, two
more unknown dwords). Covers the game's full equipment catalog (belts,
gloves, boots, hats/caps, robes/cloaks, potions) plus key items
(Firebolt, Hedwig, Time-Turner, Trevor, Scabbers, Crookshanks, The
Monster Book of Monsters), zero-padded past index 77. `dwType`/`dwParam`
not decoded. Read by item index via `FUN_08026CDC`/`FUN_08026CF0` from
an item-use code path unrelated to spell MP cost.

### `ShowBattleMessage` -- case -> dialog text table

Text pulled from `data/text/en_us.json` by string ID.
`GetDialogText` (`0x080425E4`) returns a decompressed-text pointer (or
0 on failure); prototype `void *GetDialogText(int textId)`. Every call
site checked (24 across the ROM) is a genuine `bl`, not a tail-branch.

Several logical cases compile to more than one physical call site
(tail-duplication, up to 5 for case 6) -- every one of the 25 physical
`GetDialogText` call sites is individually annotated in Ghidra
(decompiler PRE_COMMENTs, visible inline in the decompile). Case
boundaries are read directly from the switch's real 18-entry jump table
(`0x080108D4`), which does not match the decompiler's own case-label
order.

| `messageCode` | Text ID | Text |
|---|---|---|
| 0 | `0x904` (static) | "The spell levels-up!" |
| 1 | `0x902` (static) | "Your escape has been blocked." |
| 2 | `fighterType*4 + 0x970` (dynamic) | e.g. "Harry performs a Special Move:" |
| 4 | `DAT_0804e344[fighterType]` (hero, indices 0-3) or `DAT_0804e344[rosterIndex+4]` (enemy, indices 4+) -- both branches read the SAME table, confirmed by reading the pool pointers at both call sites | hero: "Harry casts a spell:" / "Hermione casts a spell:" / "Ron casts a spell:" / "Buckbeak attacks!" (indices 0-3). enemy (sampled indices 4-7): "The ruby fire crab attacks!" / "The emerald fire crab attacks!" / "The sapphire fire crab attacks!" / "The Cornish pixie attacks!". A third call site (`0x08010c92`) passes the fighter struct pointer itself as the textId -- almost certainly dead/unreachable code, not resolved |
| 5 | `param1 > 999`: `0x995` (static). Else dispatches on `param2` (0-4, attack-result variants), each rendered via `DrawTextLines_candidate` (`0x08020F44`, see `docs/formats/text.md` -- a multi-line text-box drawer built on `DrawTextLine`): `0`: `"@1 damage."` (`0x997`), value = `param1` or `param1-999` past the sentinel; `1`: `0x996` (hero) or `0xa1b` (enemy); `2`: `DAT_0804e468[fighterType or rosterIndex+4]`, target's name; `3`: `0x976+targetFighterType`; `4`: `fighterType==Enemy` -> `0x97a+targetFighterType`, else `0xa1f` | "Critical hit!" / "@1 damage." / "The spell misses." or "The attack misses." / (target name) / "Harry is poisoned." / "Harry is paralyzed." or "The opponent is paralyzed!" |
| 6 | fainted-message queue pop (`aFaintMessages_candidate[--bFaintMessageCount_candidate]`): `bEffectId<3` -> `0x8ec+bEffectId`; `==3` -> `0xa3d`; else -> `0x49e+bEffectId`; then unconditionally a damage-amount message, plus a miss-message variant | "Harry"/"Hermione"/"Ron" or "Buckbeak" (who fainted the target), then spell name e.g. "Diffindo"/"Glacius" (what fainted them), then "@1 damage." (two call sites, same text) or "The attack misses." |
| 7 | `fighterType + 0x973` (dynamic) | e.g. "Harry uses a potion:" |
| 8 | inner `switch(arg2)`: `0x38`/`0x39` -> `fighterType + 0x98d`; `0x3a`/`0x3b` -> `0xa27`; `0x3c` -> `fighterType + 0x985`; `0x3d` -> `fighterType + 0x981` | "Harry's SP are replenished." / "Your Magic Points are refilled." or "The party is revived!" / "Harry feels better!" / "Harry can move again!" (per fighterType) |
| 9 | `0x998` (static) | "@1 SP" |
| 10 | `0x999` (static) | "@1 MP" |
| 0xb | `0xa1e` (static) | "You are victorious!" |
| 0xc | `0xa1d` (static) | "You've been defeated." |
| 0xd | `fighterType==0xff` ? `0xa1c` : `DAT_0804e5ec[fighterType]` | "The opponent can't move!" (enemy), or "Harry"/"Hermione"/"Ron"/"Buckbeak can't move." (hero, per `FighterType`) |
| 0xe | `fighterType==0xff` ? `0xa20` : `fighterType + 0x981` | "The opponent can move again!" (enemy), or "Harry"/etc. "can move again!" (hero) |
| 0xf | `0xa3c` (static) | "The opponent's attacks are weakened." |
| 0x10 | `pFighters[arg3].fighterType + 0x991` (dynamic) | e.g. "Harry is hidden from view!" |
| 0x11 | `0xa3e` (static) | "The opponent is immune to paralysis!" |
| default | keyed on the *acting* fighter's `bFighterType`: `1` (Hermione) -> `arg2 + 0xa39`; `2` (Ron) -> `arg2 + 0xa36`; `0` (Harry) -> several sub-branches (`arg2==3`/`6`/`0xf` index different tables, e.g. `0xf` -> `... + 0xa2d`); else -> `0` | Hermione/Ron/Harry special-move descriptions, e.g. "Wow! Harry learned all possible spells!" |
