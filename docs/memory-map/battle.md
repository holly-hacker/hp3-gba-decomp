# Battle system -- memory map

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

This document covers battle *mechanics*: the `BattleFighter` record, turn
order, the melee and spell damage formulas, the status-effect system,
and the spell/level tables. The menu tree that selects an action, the
`ShowBattleMessage` dialog-text dispatcher, the item catalog, and the
per-character Special Move content are in [`battle-ui.md`](battle-ui.md).

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
| `0x2A` | u8 | **`bStat_speed`** (`MonsterTable+0x03`) | **PROVEN** -- turn-order/initiative value, not defense; see "Turn order" below | -- |
| `0xE` | u8 | **`bLevel`** | **PROVEN as a struct field** -- read by `ResolveSpellAttack` as the caster's spell power scale term and spell crit-chance term (see below), sourced from `g_pPartyMasterStats_candidate` for player casters. For monster records (`MonsterTable+0x02`), **UNCONFIRMED** -- monsters never reach `ResolveSpellAttack` as attacker, and `ResolveMeleeAttack` doesn't read this offset | -- |
| `0x2B` | u8 | **accuracy** | **PROVEN** -- see "Attack resolution" below | jlun2 (led here) |
| `0x2C` | u8 | **`bCritChance`** (`MonsterTable+0x05`) | **PROVEN** -- read as a roll threshold in the bonus-damage check, see below. Monster-only: never populated for player fighters | jlun2 (led here) |
| `0x2E` | u8 | **`bDefenseFactorPercent`**, percent (`damage = damage * this / 100`) | **PROVEN**, player-only -- `InitMonsterBattleActor` never writes it from `MonsterTable`; `InitPlayerBattleActor_candidate` copies it from `g_pPartyMasterStats`, see "Player fighters get `bLevel`..." below | jlun2 (led here) |
| `0x2F` | u8 | **`bMagicDefensePercent`** -- same shape as `0x2E` (reset/reduced identically) but **no damage formula reads it** | PROVEN as UI-displayed ("Magic Def"), UNCONFIRMED as a formula input | -- |
| `0x30` | u16 | **base damage roll, min** (`MonsterTable+0x06`) | **PROVEN** -- fed directly into `Mt19937RandRange` as the attack's damage roll | jlun2 (led here) |
| `0x32` | u16 | **base damage roll, max** (`MonsterTable+0x08`) | **PROVEN** | jlun2 (led here) |
| `0x3A` | u8 | selected action/spell index for this turn | STRUCTURAL MATCH -- used across multiple AI/dispatch functions (e.g. `DispatchPendingAction`, `0x080100a0`) | -- |
| `0x42` | u8 | status-flags bitfield | PROVEN as a formula input, bits below | jlun2 (led here) |
| `0xC` | u16 | `wRewardXp` (`MonsterTable+0x10`) | PROVEN | `InitMonsterBattleActor` |
| `0x28` | u16 | `wRewardGold` (`MonsterTable+0x12`) | PROVEN | `InitMonsterBattleActor` |
| `0x3E` | u8 | `bUnk_0x3E`, set to `0xff` on init | UNCONFIRMED, no reader traced | `InitMonsterBattleActor` |

`InitMonsterBattleActor` also spawns and wires the fighter's sprite
`Object`(s); several `Object` fields are typed
(`pfnTick` retyped to a real `ObjectTickFn *`, plus `pAnimTable`/
`pAnimFrameCursor`/`pAnimFrameBase`, `bAnimFrameDelay`/`bAnimFrameCounter`/
`bAnimFrameIndex_candidate`/`bLastAnimFrameValue`, `pShadowObject`/
`pOwnerObject`, `bFlagsAndEffectSlot_0xD5`). It hardwires `pfnTick` to
`TickFighterAttackAnimState_candidate` -- the concrete reason every
`Enemy` fighter resolves via `ResolveMeleeAttack` rather than
`ResolveSpellAttack` (see the NPC-vs-PC dispatch note above). Its
graphics-table reads are now typed too: `g_pMonsterGraphicsTable`
(`0x0804E6B4`, `MonsterGraphicsEntry_candidate[69]`, 32-byte stride --
row base is the anim table, `+0x08` an effect pointer registered via the
new `AllocEffectChannelSlot_candidate`/`BindEffectChannelSlot_candidate`/
`AttachObjectEffectSlot_candidate` family) and `g_pMonsterAnimFrameTable`
(`0x08051E70`, 96-byte stride, layout not decoded).

### Turn order -- `BattleFighter+0x2A` (`bStat_speed`), PROVEN

**PROVEN.** `MonsterTable+0x03` / `BattleFighter+0x2A`
(`bStat_speed`) is a turn-order/initiative value, lower = earlier turn.
Found by tracing `SetupBattleRoster_candidate` (`0x0800EDD8`, builds the
roster then calls the two functions below):

- **`JitterEnemyTurnOrder_candidate`** (`0x0800E5B8`) adds
  `Mt19937RandSigned(0x10)` jitter to each *Enemy* fighter's
  `bStat_speed`, clamped to `[5, 251]`. Player fighters are untouched --
  their `bStat_speed` source isn't located (no `InitPlayerBattleActor`
  analog found yet, same gap as `bDefenseFactorPercent`).
- **`BuildTurnOrder_candidate`** (`0x0800E62C`) selection-sorts
  `pStagingFighters_candidate` into `pFighters` ascending by
  `bStat_speed` (with a tie-breaking bump so equal values still order
  stably), then spawns each fighter's queue-position icon via
  **`SpawnTurnOrderIcon_candidate`** (`0x08014F1C`, boundary only --
  ends in an unrecovered indirect jump table).
- **`ReviveFighter_candidate`** (`0x0800E890`) restores
  `FightState.pTurnQueueFighters_candidate[fighterIndex]`'s `wHp`/`wMp`
  to max, then re-sorts the queue by `bStat_speed` to reinsert that
  fighter (`0xff` marks a fighter as already acted this round). Called
  from `sub_08018CF8` (the object-script interpreter,
  `../formats/object_script.md`'s `StatusEffect` opcode `0x97`, sub-case
  `0x1C`, `0x0801AB34`) with `g_bEffectTargetIndex` as `fighterIndex`.
  `data/scripts/SpecialHarryRevive.txt` is the only script using sub-case
  `0x1C` -- Harry's `Revive` card (`g_abHarryCardEffectId` index `6`,
  effect id `37`, "Revive an unconscious member of your party").

`bStat_speed` clusters at `178-254` across the 53 real Folio Bruti rows
for ordinary monsters (they mostly act after the player), while
dangerous ones act early (Lupin Werewolf `=20`, Draco `=60`).

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
5's sub-dispatch; see [`battle-ui.md`](battle-ui.md)'s case-5 table).
Defaults to `0x12` (18, "none"). Opcode `0x97`'s status-applying cases
set it to a specific sub-case value right where they set the
corresponding bit -- this is the evidence behind bits `0x02`/`0x10`
below (`0x04`/`0x08`/`0x01` are PROVEN via a direct adjacent
`ShowBattleMessage` call instead, not `field_0x14a8`).

- **bit `0x01`** = **Hidden** status. PROVEN. Read on the *defender* in
  `ResolveMeleeAttack`: reduces the attacker's effective accuracy by 25
  and gates the bonus-damage/crit check (which only runs while this bit
  is clear) -- consistent with "target is hidden from view".

  Applied by opcode `0x97` cases 8/9 (`0x0801a7b6`/`0x0801a7e8`), whose
  handlers are byte-for-byte identical apart from the `argA` they pass
  to `ShowBattleMessage(Hidden, argA, targetIndex)`. That argument gates
  one call: `argA == 1` (case `9`, `HiddenMain`) opens a fresh message
  box first, `argA == 0` (case `8`, `HiddenSecondary`) draws into
  whichever box is already open.

  **Confirmed spell: Fumos**, `SpellId` `8`, Hermione-exclusive
  (`g_abSpellIdByCursor`'s Hermione row is the only one containing `8`).
  It makes a target harder to hit, matching this bit exactly: `Uno`
  (effect id `11`, one ally) applies case `9` directly; `Duo` (effect id
  `32`, whole party) applies case `9` on its root cast and spawns copies
  of itself for the rest of the party, each copy taking case `8`
  instead via the `bScriptLocalA` root-vs-spawn idiom (see "The
  script-local bytes" in
  [`../formats/object_script.md`](../formats/object_script.md)).
- **bit `0x02`** = **Poisoned**. PROVEN: opcode `0x97` case 5
  (`0x0801a71c`), gated on `(bStatusFlags & 0x06) == 0` (i.e. not
  already `Poisoned` or `PoisonImmune`), sets the bit alongside
  `FUN_0801b590` (a particle/VFX spawn) and `field_0x14a8 = 3` -- sub-case
  `3` of `ShowBattleMessage`'s case-5 dispatch is "Harry is poisoned."
  (see [`battle-ui.md`](battle-ui.md)'s case-5 table). Not read by either damage-resolution
  function directly; its per-turn damage tick is below.
- **bit `0x04`** = **PoisonImmune**. Set by opcode `0x97` case 7
  (`0x0801a7ac`), silently -- and it's exactly the bit that, alongside
  `Poisoned` itself, gates case 5 above (`& 0x06`) from applying poison
  again. This is a structural mirror of `Paralyzed`/`0x80` below (same
  "status bit + immunity bit blocks re-apply" shape). **PROVEN source:
  Harry's card index `5`** in `g_abHarryCardEffectId`
  (`0x080514c8`) is effect id `18`, whose script contains opcode `0x97`
  case `7` three times -- a real traced call site (see the "Poison
  Immunity" writeup below), not just an effect-to-description match.
- **bit `0x08`** (checked on the *attacker* in `ResolveMeleeAttack`):
  independently contributes one halving of the computed damage (see
  below). PROVEN as **Attack Weakened**: opcode `0x97` case 6
  (`0x0801a790`) OR's this bit in, then calls
  `ShowBattleMessage(AttackWeakened, 0, 0)` -- matches
  `BattleMessageCode.AttackWeakened` (15, "The opponent's attacks are
  weakened.") exactly. Before setting this bit, the same handler ORs an
  unrelated `0x10` bit into a *different* byte -- not `bStatusFlags`,
  and not identified. **`Spongify` causes this bit -- PROVEN,
  `SpellId` `9`** (see the `bSpellId` writeup below):
  `g_abSpellEffectId_candidate[9*3+level]` is `[29,29,29]`
  (`data/scripts/SpellSpongify.txt`, effect id `29`), whose only
  gameplay opcode is exactly `StatusEffect 6 0 0`. This is the "6
  unambiguous spells" identification the `g_awSpellMpCost` writeup below
  already relied on, now traced all the way to the real applying case.
  `Poisoned` has no `SpellId`/lecture/card source of its own -- its only
  confirmed source is the monster-attack table (effect id `27`,
  `SpecialMonsterPoisonBite`, see "Monster special-attack effects"
  below).
- **bit `0x10`** = **Paralyzed**. PROVEN. Not read by
  `ResolveMeleeAttack`/`ResolveSpellAttack` at all -- paralysis gates
  *action selection*, not damage. See "The paralysis mechanic" below for
  the whole family.
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
  script (effect id `36`) also applies this same bit -- it is **none of
  Harry's 16 cards** (the real, complete
  16-entry `g_abHarryCardEffectId` table, decoded below, simply
  doesn't contain `36`), so this second source stays unattributed to any
  specific card or spell; not investigated further. **Harry's
  `Girding All`** card (index `7`, effect id `35`, "Increases all party
  members' physical defense") was the leading candidate for this bit by
  elimination, but its own script contains **no** opcode `0x97` call at
  all -- it must apply its defense boost some other way (plausibly a
  direct write to `BattleFighter+0x2E`,
  `bDefenseFactorPercent`, rather than the
  `bStatusFlags` bit), not traced further. The two halving bits (attacker's `0x08`, defender's
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

### Poison's per-turn damage tick -- `TickBattleTurnStateMachine_candidate` case 2, PROVEN

**PROVEN.** `TickBattleTurnStateMachine_candidate` (`0x0800F794`) is the main battle turn state machine (7
states, driven by `g_pFightState->field_0x1061`; not yet added to the
`FightState` struct, small distinct region at `+0x1061`-`+0x1068` just
before the already-named `+0x106C` (`bActiveFighterIndex`) block). Its
state-2 handler ("end of turn" processing) loops every active fighter
and checks `bStatusFlags & 0x02` (`Poisoned`):

```c
for (i = 0; i < fainted_candidate; i++) {   // "fainted_candidate" here really iterates every active fighter slot
    if (fighters[i].bStatusFlags & Poisoned) {
        ShowFloatingDamageNumber_candidate(fighters[i].bPoisonDamage, 4, i, 0);   // floating damage-number popup
        ApplyStatusDamageToFighter_candidate(fighters[i].bPoisonDamage, i);        // apply the damage
        field_0x1068 = 0x3c;   // (re-)arm a delay timer
    }
}
```

Both calls read a newly-identified field, **`BattleFighter+0x43`
(`bPoisonDamage`)**, immediately after `bStatusFlags` -- not
copied from `MonsterTable` by `InitMonsterBattleActor` (which never
touches this offset), so its value's origin for monster fighters is
still unknown; likely written by the same status-effect opcode that sets
the `Poisoned` bit itself (case 5, `0x0801a71c`, not fully walked past
its bit-set/VFX call), not traced further here.

(Ghidra renders these two reads as `aSpellEffectiveness[iVar10+0xe/0xf]`
because the underlying pointer carries that array's element type;
`iVar10` is `fighterIndex * 0x48`, so the constant offsets land at
absolute `+0x42`/`+0x43`, past the array. The real fields are the two
above.)

**`ApplyStatusDamageToFighter_candidate`** (`0x08018094`) is
`ApplyDamageToFighter`'s (`0x08017F98`) sibling for
this path: same `+999`/`0x3e6` sentinel unwrap, same `wHp -= damage` /
faint check / `SetFighterAttackAnimState_candidate(pObject, 1)` shape,
and a HUD-mirror write (`DAT_030024f4[fighterType*0x24] = wHp`) -- but
**no XP/gold reward payout**, consistent with a status-tick rather than
a kill-credited attack. **`ShowFloatingDamageNumber_candidate`**
(`0x080181AC`) is the floating damage-number
popup: shows `GetDialogText(0x8f8)` = `"Miss!"` when its first and
fourth parameters are both `0`, otherwise formats its first parameter
(the damage/poison amount) into `GetDialogText(0x8f7)` = `"@1"` (a
single-value template) and spawns a text sprite positioned relative to
the target's `Object` (`+0x2e`/`+0x32` offsets).

### The paralysis mechanic, PROVEN

Every source of `Paralyzed` (bit `0x10`) goes through one helper,
**`FUN_0801b430`**, called from five `StatusEffect` sub-cases. The
helper sets the bit only when `bStatusFlags & 0x90 == 0` (not already
paralyzed, and bit `0x80` clear); otherwise it may announce
`ImmuneToParalysis`, depending on its `param_2`.

| Sub-case | Name | Start escape % | Gated? | Feedback on success |
|---|---|---|---|---|
| `0x0A` | `Paralyze25` | 25 | yes, on `g_wEffectContextValue` | none |
| `0x11` | `Paralyze99` | 99 | no | none |
| `0x12` | `Paralyze80` | 80 | no | none |
| `0x16` | `ParalyzeMonster` | script operand | same gate as `0x0A` | VFX + "is paralyzed" text |
| `0x17` | `ParalyzeMonsterChance` | script operand | own `Mt19937ChanceNoisy` roll first | VFX only, silent |

The gate (`(g_wEffectContextValue != 0 && != 0x3e9) || param_2 != 0`)
means `Paralyze25`/`ParalyzeMonster` apply only under external effect
context, while `Paralyze99`/`Paralyze80` pass `param_2 = 1` and so
always apply. `ParalyzeMonsterChance` uniquely passes `param_2 = 0`, so
it can never show `ImmuneToParalysis`.

**The third parameter is a starting escape chance, not a duration.** It
lands in `BattleFighter+0x44` (`bParalysisEscapeChance`).
Every turn a paralyzed fighter would act,
`TickBattleTurnStateMachine_candidate`'s cases `3`/`4` call
`RollFighterParalysisEscape_candidate` (`0x0800FFAC`) first:

```c
int RollFighterParalysisEscape_candidate(uint fighterIndex) {
    BattleFighter *f = &g_pFightState->pFighters[fighterIndex];
    if (!(f->bStatusFlags & Paralyzed)) return 0;               // acts normally
    if (!Mt19937ChanceNoisy(f->bParalysisEscapeChance)) {
        f->bParalysisEscapeChance += 25;               // ratchet up
        return 1;                                                // can't move this turn
    }
    ClearParalyzedFighter_candidate(fighterIndex);               // clears Paralyzed, sets Unk_0x80
    return 3;                                                    // can move again
}
```

So the chance ratchets up by 25 per failed turn until it succeeds --
`Paralyze25` frees a fighter by the 4th attempt at the latest, while
`Paralyze99`/`Paralyze80` almost always end on the very next turn,
making them mechanically closer to "skip one turn" than a real lockout.
The caller shows `CanMoveAgain` on a `3` return and `CantMove` on a `1`,
which is where those per-turn messages come from -- not from the
`StatusEffect` case's own one-time message.
`ClearParalyzedFighter_candidate` is the same function `CureAilments`
(case `0x14`) calls, so breaking free naturally and being cured go
through one cleanup path.

`ParalyzeMonsterChance` therefore stacks three independent RNG layers
for one effect: whether the attack lands (`special_effect_chance`),
whether paralysis takes at all (its own roll), and whether/when the
target breaks free.

**PROVEN sources.** `PetrificusTotalus` (`SpellId` `6`) -- both its
effect ids `33`/`34` (`SpellPetrificusTotalusUno`/`Duo`) contain an
unconditional `StatusEffect 10 0 0`; the two scripts differ only in
animation timing, not in how paralysis applies. Harry's `Snitch` card
(effect id `47`, see [`battle-ui.md`](battle-ui.md)) uses case `0x12`, matching the
Card Combo Glossary's
"Snitch causes opponent to lose a turn" word for word. Ron's `Stink
Pellet`/`Stink Pellet 2` use case `0x11` (see
[`battle-ui.md`](battle-ui.md)). Cases `0x16`/`0x17` are
monster-special-attack only (Suits of Armor and Lupin Werewolf;
Hinkypunk and Skeleton respectively).

`PetrificusTotalus` never reaches a `Tria` cast in play --
`g_abSpellMaxLevel` caps it at level `2`, so effect id `33`'s reuse in
the `Tria` slot is unreachable table content.

### `FightState+0x1480` -- bonus-reward flags, no located reader

Three `StatusEffect` sub-cases OR a bit into this one `FightState` byte,
and nothing else touches it:

| Bit | Sub-case | Source |
|---|---|---|
| `0x01` | `2`, `ExtraExpBonus` | Harry's `Extra EXP` card (effect id `14`) |
| `0x02` | `3`, `GrantExtraXp` | Hermione's "Good Study Habits" (effect id `50`) |
| `0x04` | `0x1B`, `ForceItemDrop` | Ron's `Wizard Cracker` (effect id `46`) |

So it is a 3-bit "bonus reward for this encounter" byte: extra XP from
two independent sources, and an item drop. `Wizard Cracker`'s own
description (`data/text/en_us.json` string ids `1725`/`2615`) confirms
its effect is making the target drop an item, not a gold bonus.

**No reader exists in code either tool currently recognizes.** The three
writes build the `0x1480` offset with a `movs Rd, #imm8; lsls Rd, Rd,
#shift` pair rather than a literal-pool constant; all three
immediate/shift pairs that can produce `0x1480` (`0xA4<<5`, `0x52<<6`,
`0x29<<7`) were checked at every occurrence in the US disassembly, as
was a direct `ldr Rd, =0x1480`, as was Ghidra's own auto-analysis --
only the three writes above turn up. This is **not** proof of absence:
`gbadisasm`'s output only covers code reachable from what's seeded in
`functions.us.cfg`, so a reader in still-unseeded territory would not
appear (the same class of gap as `FightState+0x1054`/`+0x1058` below).

Consequently the in-game item drop is **not** traced to this byte --
case `0x1B` merely being the one `StatusEffect` call in `Wizard
Cracker`'s script is the whole of the evidence. Where an item actually
gets added to inventory isn't located either; the only item functions
found are `g_pItemTable`'s *consumption* pair
(`ConsumeBattleItemSlot`/`IsBattleItemSlotUsable`), subject to the same
caveat.

### `StatusEffect` sub-cases, PROVEN

All 29 sub-cases of opcode `0x97` (`g_apScriptStatusEffectCaseTable`,
US `0x0801A650`) are identified, cross-checked against every real script
that reaches each case (`grep`-ing `StatusEffect <N> ` across all 65
files in `data/scripts/`). `../formats/object_script.md` has the
condensed table; this is the supporting detail for the cases not already
covered by their own section above (`Poisoned`, `AttackWeakened`,
`PoisonImmune`, `HiddenSecondary`/`HiddenMain`, `Paralyze25` and
its `Paralyze99`/`Paralyze80`/`ParalyzeMonster`/
`ParalyzeMonsterChance` siblings, `DefenseBoost`, `SpellPowerBoost`, `GrantExtraXp`/
`ExtraExpBonus`/`ForceItemDrop`, `Revive` -- all documented in the
sections above and below).

`BattleFighter+0x8`/`+0x24` hold current/max SP (written by
`ReplenishPartySp`), and `+0xA`/`+0x26` hold current/max MP (written by
`ReplenishTargetMp`) -- both restored via a plain `strh currentField,
[maxField]`-style copy, mirrored by fighter id into
`g_pPartyMasterStats_candidate` (`0x030024EC`, see "Player fighters get
`bLevel` from `g_pPartyMasterStats_candidate`" below) -- the persistent,
`BattleFighter`-shaped per-character array that survives between
battles, so the restored SP/MP carries over outside the current
encounter, not just in the live roster copy.

- **Case `0` (`SpawnEffectA`) and case `1` (`SpawnEffectB`)**: call
  `sub_0801B204`/`sub_0801B2EC` respectively, then jump into a shared
  tail (`_0801AA3C`) that stashes the returned `Object*` into a global
  (`0x03002750`) and sets a byte at `+0x49` to `2`. Neither function
  touches `bStatusFlags` or any other `BattleFighter` field -- pure
  particle/VFX spawns, differing only in which canned effect they spawn.
- **Case `0xC` (`BumpMonsterDocLevel`)**: `SpellInformus`'s only
  `StatusEffect` case (effect id `38`, `SpellId` `1` -- `Informus`'s own
  real ID, see the `bSpellId` writeup below). Reads `BattleFighter+1` (a
  species/monster-id byte) and calls `sub_08037104(speciesId)`, which
  does exactly:
  `if (g_abMonsterDocLevel_candidate[speciesId] < 3) g_abMonsterDocLevel_candidate[speciesId] = 4;`
  -- then mirrors the same byte into a global at `0x03002748`. **This is
  `Informus`'s Folio Bruti write.** `Informus`'s own in-game description
  (`data/text/en_us.json` string id `1494`) is "Cast upon a creature to
  learn about its strengths and weaknesses" -- exactly this bump; it's
  the *entire* gameplay payload `Informus` produces (zero base power,
  zero MP cost -- see the base-power/MP-cost tables below).
  `g_abMonsterDocLevel_candidate`
  (`0x03003190`) is the exact same per-monster byte `../formats/folio_bruti.md`
  already documented independently: the Folio Bruti detail screen's
  spell-effectiveness slider loop shows a "?" placeholder instead of the
  real dot whenever this byte is `<= 2`. So the threshold this bump
  writes (`4`, only if currently `< 3`) is specifically what flips a
  monster from "unanalyzed" to "analyzed" on that screen -- the two
  findings, made independently in each doc, now confirm each other.
- **Case `0xD`/`0xE` (`SetPostActionFlashFlag`/`ClearPostActionFlashFlag`)**:
  a matched pair, both looping every fighter (`0 <= i <
  FightState+0x106F`, the same active-fighter-count field the turn-order
  code uses) and testing `field0 == 0xff` (per the turn-order section
  above, "already acted this round"). The set side unconditionally ORs
  `0x10` into that fighter's `Object+0x115` (the same byte `Hidden`
  overwrites wholesale with `0x20`); the clear side ANDs it off, but only
  for fighters that *don't* have `AttackWeakened` set. Both appear
  back-to-back in Harry's Sonorous Charm script, bracketing the roar
  animation -- read as a temporary "reacting to the roar" visual flag on
  everyone who's already had their turn, not a gameplay status; the
  `AttackWeakened` exception on the clear side is real in the
  disassembly but not explained further.
- **Case `0xF` (`CurePoison`)**: calls `sub_0800EB2C(g_bEffectTargetIndex)`
  (`g_bEffectTargetIndex` = `0x03002750+0x22`, the same global
  `Revive`/case `0x1C` reads). That function checks `bStatusFlags &
  Poisoned`, and if set: clears just the `Poisoned` bit (masking down to
  `Unk_0x80|SpellPowerBoost|DefenseBoost|Paralyzed|AttackWeakened|PoisonImmune|Hidden`),
  zeroes `bPoisonDamage` and the Object's blink-flag halfword
  (`Object+0x8A`), calls `FUN_08015484(Object,0)` (an anim-data-table
  toggle, see case `0x10` below), tears down an active
  particle/sound-channel pointer at `Object+0x24` if set, then refreshes
  the fighter's palette via `FUN_0800d264` (undoing the poison
  discoloration). Used by Harry's Poison Antidote.
- **Case `0x10` (`ToggleUltimateVisual`)**: operand `[2]`-driven.
  Operand `0` (called first in `SpecialHarryUltimateMp`, right before a
  210-frame wait) reads `Object+8` (a species/character-id `u16`) and
  calls `SetObjectAnimData` against an alternate table pair
  (`0x08051288`/`0x08054FDC`, indexed `id*0xA0`/`id*` a second stride)
  plus `sub_08001958(Object,0)` to reset the anim frame -- a visual-only
  "glow" swap. Non-zero operand (called second, after the wait) instead
  calls `sub_08015484(Object,0)` (which flips a toggle bit at `Object+0xC`
  and restores the *normal* anim-data table for that same species/id) and
  `sub_08012994(fighterIndex, BattleFighter+8)`, which sets all 10 of the
  target's spell cast-level bytes (`BattleFighter+8`, mirrored into the
  global `g_pPartyMasterStats_candidate` party-stats struct) to
  `g_abSpellMaxLevel[i]` -- i.e. **grants every spell at max level**, the
  actual "Grants one party member all spell abilities" effect of Harry's
  `Ultimate MP` card. The first (operand-`0`) call is purely the
  glow-in visual for the card's animation.
- **Case `0x14` (`CureAilments`)**: calls both `sub_0800EB2C` (the
  `CurePoison` function above) and `ClearParalyzedFighter_candidate` on
  `g_bEffectTargetIndex`. The latter checks `bStatusFlags & Paralyzed`,
  and if set: clears `Paralyzed`, then ORs in `Unk_0x80` (the same
  "recently cured/briefly immune" bit `FUN_0801b430`'s own gate checks
  for, `bStatusFlags & 0x90 == 0`), resets
  `bParalysisEscapeChance` (`BattleFighter+0x44`) to `100`
  (see "The paralysis mechanic" above for what this field actually
  is -- a per-turn escape-chance percentage, not a duration; why `100`
  specifically, given `Unk_0x80` already blocks re-application, isn't
  traced further), zeroes the Object blink halfword, and -- for
  player fighters only (`bFighterType != Enemy`) -- runs the same
  anim-data-toggle/particle-teardown/palette-refresh sequence
  `CurePoison` does (enemies instead call `FUN_0801539c(Object,0)`, not
  traced). So `CureAilments` is a superset of `CurePoison` that also
  lifts paralysis -- used by Harry's Remove Jinx (single target) and
  Reparifors (three calls, one per party member).
- **Case `0x15` (`SpawnEffectC`)**: calls `sub_0801B348`, a third member
  of the same VFX-spawn family as `SpawnEffectA`/`B` (spawns a particle
  `Object`, sets its position/velocity/timing fields from
  `g_bEffectScriptParam`-indexed tables, no `bStatusFlags`/other
  gameplay write), then falls into the same shared tail as cases `0`/`1`.
  Used three times in `SpecialMonsterHinkypunkParalyze`, once per
  target slot, immediately before the script's own `ParalyzeMonsterChance` roll.
- **Case `0x19`/`0x1A` (`ReplenishPartySp`/`ReplenishTargetMp`)**: see
  the field note above. `ReplenishPartySp` loops every active,
  non-fainted (`BattleFighter+8 != 0`) fighter and copies `+0x24` (max
  SP) over `+8` (current SP), mirroring the write into
  `g_pPartyMasterStats_candidate`; `ReplenishTargetMp` is the same copy
  (`+0x26` -> `+0xA`) for just `g_bEffectTargetIndex`'s `BattleFighter`
  (the current effect target, via `r8` directly rather than a re-lookup).
  Matches Harry's Replenish SP (party-wide) and Replenish MP
  (single-target) exactly.
- **Case `4` (`UnusedWinoutWrite`)**: writes the literal halfword
  `0x3F3D` to hardware register `0x0400004A` (GBA `WINOUT`, the
  window-0/1/OBJ-outside layer-visibility register) and returns
  immediately -- no `bStatusFlags`/other `BattleFighter` write. **No
  script among the 65 real ones reaches this case** (confirmed: `grep
  "StatusEffect 4 " data/scripts/*.txt` matches nothing), so it's
  either dead code or reachable only through content not currently
  extracted (e.g. an unused/cut effect id). Not traced further.

### `FightState+0x1054`/`+0x1058`: write-only, purpose unknown

Kept `field_`-prefixed rather than named, since nothing pins a purpose
down. The object-script interpreter's opcode `0x30` (see
[`../formats/object_script.md`](../formats/object_script.md)) increments
a byte at its target `Object+0x60`, mirrors the result into
`field_0x1058`, and latches the `Object` pointer into `field_0x1054` the
first time it runs (guarded on that field being `0`).
`TickFighterAttackAnimState_candidate` (`0x08015608`) reads the same
`Object+0x60` byte as a small state value (`1`/`2`/`4`) to steer
attack-outcome handling, and zeroes it together with both `FightState`
fields once an attack sequence resolves.

Every other site touching either field is the same reset-to-zero at a
different start/end-of-attack transition: `TriggerBattleEffect`
(`0x08018B70`), `ShowItemUseResult` (`0x08015F50`), and several
transitions inside the spell-resolution state machine `FUN_080161FE`.
**Nothing reads either field's accumulated value.** Both appear
write-only: tracked by the interpreter, reset at attack boundaries, with
no confirmed consumer and no known in-game effect. Found by checking
every occurrence of the two literal constants `0x1054`/`0x1058`, which
is not a proof that no reader exists by some other addressing path.

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
    damage = damage * defender->bDefenseFactorPercent / 100;

    // halving (attacker bit 0x08 and defender bit 0x20 each independently halve)
    if (attacker->bStatusFlags & 0x08)
        damage >>= (defender->bStatusFlags & 0x20) ? 2 : 1;
    else if (defender->bStatusFlags & 0x20)
        damage >>= 1;
    damage += 1;                                       // rounding

    // bonus-damage / crit-style check
    if (damage != 0 && !(defender->bStatusFlags & 0x01)) {
        int roll = Mt19937RandMax(100);
        if (roll > 100 - attacker->bCritChance) {
            damage *= 2;
            damage += 999;   // sentinel, not literal damage -- see note below
        }
    }

    ApplyDamageToFighter(damage, defenderIndex);
    return damage;
}
```

Notes:

- The `+= 999` (`0x3E7`) on the bonus-damage path is a **sentinel, not
  literal damage points**, PROVEN: `ShowBattleMessage`'s case 5 checks
  `param1 > 999` and displays `"Critical hit!"` (string `0x995`) on
  exactly this path (see [`battle-ui.md`](battle-ui.md)'s case-5 table).
- `attacker->bCritChance` (`MonsterTable+0x05`) is PROVEN as crit
  chance: read as a roll threshold that triggers the confirmed
  "Critical hit!" path above, at probability `bCritChance/101`
  (`Mt19937RandMax(100)` is 0-100 inclusive). Monster-only in practice --
  `InitPlayerBattleActor_candidate` never populates it for player
  fighters, and `ResolveMeleeAttack` only ever fires with an `Enemy`
  attacker. Observed values: 3, 5, 10.
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
`TickFighterAttackAnimState_candidate`, at two symmetric call sites
(`0x08015B5C`/`0x08015BE0`) -- one per branch of a `byte[0x14]==100`
check:

```c
if (MonsterTable[monsterIndex].special_effect_chance == 100) {
    int damage = ResolveMeleeAttack(activeFighterIndex, defenderIndex);
    g_nLastDamage = damage;                              // 0x0300274A
    RollMonsterSpecialEffect_candidate(monsterIndex, defenderIndex, damage);  // unconditional
}
... // unrelated status-flag housekeeping in between
if (MonsterTable[monsterIndex].special_effect_chance <= 99) {
    int damage = ResolveMeleeAttack(activeFighterIndex, defenderIndex);
    g_nLastDamage = damage;
    if (damage != 0)
        RollMonsterSpecialEffect_candidate(monsterIndex, defenderIndex, damage);  // only on a hit
}
```

So every monster attack goes through `ResolveMeleeAttack` exactly once
(the two branches are mutually exclusive on the same `==100` check, not
two different attacks) -- `special_effect_chance` doesn't gate whether a
normal attack happens at all, only whether `RollMonsterSpecialEffect_candidate`
gets a chance to also fire afterward. See "Monster special-attack
effects" below for what that function does.

`FightState+0x106C` (`activeFighterIndex` in the `FightState` struct) is
the same field `DispatchPendingAction` (`0x080100a0`, walked in full
below -- it dispatches *any* active fighter's turn, player or monster,
and is not monster-AI-specific) already reads as "whose turn it is" --
two independent call sites agreeing is
good corroboration for this field's role.

### Monster special-attack effects -- `RollMonsterSpecialEffect_candidate` (`0x08015020`), PROVEN

```c
void RollMonsterSpecialEffect_candidate(byte monsterIndex, byte targetFighterIndex, ushort damage) {
    MonsterTableEntry *m = &MonsterTable[monsterIndex];
    if (m->special_effect_chance == 100 ||
        Mt19937RandMax(99) < m->special_effect_chance) {
        TriggerBattleEffect(m->special_effect_id,
                             g_pFightState->pFighters[g_pFightState->bActiveFighterIndex].bSlotParam + 3,
                             g_pFightState->pFighters[targetFighterIndex].bSlotParam,
                             g_pFightState->bActiveFighterIndex, targetFighterIndex, damage);
        g_pFightState->pFighters[g_pFightState->bActiveFighterIndex].bSpellId = Spongify;
    }
}
```

`special_effect_id` is fed directly into `TriggerBattleEffect` -- the
same effect-script trigger player spells/cards use (see "How the
effect-id -> script trace works" above) -- so it's literally a monster's
own special-attack effect id, not a location/group tag as originally
guessed. Setting `bSpellId = Spongify` afterward is the same
"borrow a harmless zero-power spell ID for display purposes" trick
`ConfirmBattleTopMenu`'s `Informus` case uses.

Checked all 14 distinct `special_effect_id` values actually used across
the 69 monster records (`0`, `4`, `13`, `16`, `17`, `27`, `54`-`61`)
against their scripts (`tools/objscript/script_names.json`/
`data/scripts/`), and every `StatusEffect` sub-case those scripts
reference against `g_apScriptStatusEffectCaseTable` (`0x0801A650`).
Four ids carry a real, confirmed status-effect payload:

- **id `27`** (`SpecialMonsterPoisonBite`): every venomous
  Spider/Spitting Snake/Wide-mouth Toad/Bullfrog record. Script body is
  exactly `StatusEffect 5 8 0` -- case `5`, confirmed `Poisoned`.
- **id `60`** (`SpecialMonsterParalyzingBlow`): every Suit of Armor
  variant plus Lupin Werewolf. Script body is exactly
  `StatusEffect 22 25 0` -- case `22`, confirmed `ParalyzeMonster`
  (a `25`% starting escape chance, announced with text + VFX).
- **id `57`** (`SpecialMonsterHinkypunkParalyze`) and **id `59`**
  (`SpecialMonsterSkeletonParalyze`): both call `StatusEffect 23 ...`,
  case `23` (`ParalyzeMonsterChance`). Its handler
  (`0x0801A8A4`) rolls its own extra `Mt19937ChanceNoisy` chance, then
  calls the same `FUN_0801b430` paralysis-application helper the other
  `Paralyze*` cases use, sets `field_0x14a8 = 4` (the same "Harry is
  paralyzed." sub-case) but -- unlike `ParalyzeMonster` -- never
  actually shows that text (only `ParalyzeMonster`'s call site checks
  `field_0x14a8` into a real `ShowBattleMessage` call), and spawns a VFX
  via `FUN_0801b590` -- an exact structural match to the other confirmed
  `Paralyze*` cases, just gated by its own additional roll on top of
  `special_effect_chance`.

The remaining ids (`0`, `4`, `13`, `16`, `17`, `54`-`56`, `58`, `61`)
either have no `StatusEffect` opcode at all, or reference `StatusEffect`
sub-cases `0x00`/`0x01`/`0x18` (**not** `special_effect_id` values --
these are indices into the unrelated, per-script
`g_apScriptStatusEffectCaseTable` dispatch) confirmed to be pure
VFX/particle spawns (`FUN_0801b204`/`FUN_0801b2ec`/`FUN_0801b348`, and
case `0x18`'s own palette-flash calls -- none write `bStatusFlags` or
any other `BattleFighter` field). So these monsters' special attacks
are animation-only, not a hidden mechanic -- still named in
`tools/objscript/script_names.json` (e.g. `SpecialMonsterFireCrabAttack`,
`SpecialMonsterDragonflyAttack`) for completeness, just without a
gameplay-mechanical payload.

### The attack-animation dispatcher (candidate, boundary confirmed, not fully walked)

Found by walking the live call stack (mGBA gdb backtrace) up from
`ResolveMeleeAttack`. Two small functions, seeded in `functions.us.cfg`
(neither `gbadisasm` nor Ghidra discovers them -- the whole region reads
as raw, un-analyzed bytes):

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
        g_nXpAccum += MonsterTable[f->bRosterIndex].reward_xp;
        g_nGoldAccum += MonsterTable[f->bRosterIndex].reward_gold;

        f->wHp = 0;
        f->nSelectedTargetIndex = -1;
        SetFighterAttackAnimState_candidate(f->pObject, 1);
    }
}
```

`ShowBattleMessage(CriticalHit, ...)` firing here (guarded by
`bFaintMessageCount_candidate == 0`) rather than `FaintResult` is as
decompiled; not yet reconciled with why the faint path shows a
"critical hit" message code.

### XP/reward payout -- `MonsterTable+0x10`/`+0x12`, PROVEN

On a fighter fainting, `ApplyDamageToFighter` adds
`MonsterTable[fighter.bRosterIndex].reward_xp` and `.reward_gold` into two
separate running EWRAM accumulators (`g_nXpAccum` at `0x0300260E`,
`g_nGoldAccum` at `0x03002610`). The reads resolve to
`0x0804F420`/`0x0804F422` with a `0x18`-byte stride, i.e. literally
`MonsterTable + 0x10`/`+0x12` (`MonsterTable` itself is `0x0804F410`,
stride `0x18`, per `../formats/folio_bruti.md`) -- confirming the indexing
is by roster/monster index directly into `MonsterTable`.

**Live in-game observation:** defeating 2 Brown Recluse Spiders
(`MonsterTable` index `16`, `reward_xp=8`, `reward_gold=42`) awarded
exactly 16 XP -- `8*2`, matching `reward_xp` precisely. Gold was 105 with
Ron's Special Move `Wizard Cracker` active; `42*2*1.25 = 105` exactly.
`Wizard Cracker`'s own in-game move description (string ids `1725`/`2615`
in `data/text/en_us.json`) states its effect as making the target
creature drop an item, not a gold bonus -- see "`StatusEffect` sub-cases,
full case-by-case writeup" above (`ForceItemDrop`, case `0x1B`) and
[`battle-ui.md`](battle-ui.md)'s "Ron's Special Move effect ids". The source of this particular
25% gold figure is an open question: whether it's an unrelated factor
that happened to coincide with this encounter, a second undocumented
effect of `Wizard Cracker` beyond the item drop, or something else
entirely isn't determined. What consumes the two reward accumulators
after battle isn't traced further either.

**A second, independent path into these same two accumulators exists:**
`GrantMonsterKillReward` (opcode `0x83`, `../formats/object_script.md`,
US `0x0801A254`) reads a species/monster-id byte and adds
`MonsterTable[speciesId].wRewardXp`/`.wRewardGold` straight into
`g_nXpAccum`/`g_nGoldAccum`, bypassing `ApplyDamageToFighter` entirely.
Its only user is Harry's `Tempest Jinx` card (banishes a monster without
damaging it to `0`, so it needs its own reward grant in place of the
normal on-faint payout) -- not `Wizard Cracker` -- but it proves this
kind of direct, script-triggered accumulator write is a real pattern in
this codebase, not a hypothetical one. Whether `Wizard Cracker` goes
through some other, not-yet-located function shaped like this one -- as
opposed to `FightState+0x1480`'s bit `0x04`, which has no located reader
(see the `StatusEffect` sub-cases section above) -- is the open
question the 25% gold figure raises.

## `MonsterTable` -> `BattleFighter` field correspondence

`InitMonsterBattleActor` copies a monster's record into its live
`BattleFighter` field for field. The record's own layout, confidence
levels, and observed value ranges live in
[`../formats/folio_bruti.md`](../formats/folio_bruti.md); this table is
just the offset mapping, plus which function in *this* document reads
each field (the reader is what gives the field its name, so it wins if
the two ever disagree).

| `MonsterTable` | `BattleFighter` | Label | Reader |
| --- | --- | --- | --- |
| `+0x00` | `+0x08`, `+0x24` | `wHp`, `wHp_max` | `ApplyDamageToFighter` |
| `+0x02` | `+0x0E` | `bLevel` | none for a monster's own value -- see "`BattleFighter+0xE`" below |
| `+0x03` | `+0x2A` | `bStat_speed` | `BuildTurnOrder_candidate` -- see "Turn order" |
| `+0x04` | `+0x2B` | `bAccuracy` | `ResolveMeleeAttack` hit/miss roll |
| `+0x05` | `+0x2C` | `bCritChance` | `ResolveMeleeAttack` bonus-damage roll |
| `+0x06`, `+0x08` | `+0x30`, `+0x32` | `wDamageRollMin`, `wDamageRollMax` | `ResolveMeleeAttack` damage roll |
| `+0x0A`-`+0x0F` | `+0x34`-`+0x39` | `aSpellEffectiveness[6]` | `ResolveSpellAttack` |
| `+0x10`, `+0x12` | `+0x0C`, `+0x28` | `wRewardXp`, `wRewardGold` | `ApplyDamageToFighter`, `GrantMonsterKillReward` |
| `+0x14`, `+0x15` | -- | `special_effect_chance`, `special_effect_id` | `RollMonsterSpecialEffect_candidate` (read from the table directly, not copied into the fighter) |

`tools/monsters/monster_codec.py` uses these same labels.

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

**`FightState` struct fields**, from decompiling
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

### `TickPlayerActionState_candidate` (`0x0801602C`) -- second `+0x8D` dispatcher

Same structural pattern as `TickFighterAttackAnimState_candidate`: reads
`Object+0x8D`, 27-entry jump table, shared epilogue reached via
`bl`-as-branch (`0x08017B42`). Distinct case targets at 0, 1, 2, 5, 15,
21, 26; default for the rest. Found while tracing `ShowBattleMessage`'s
callers looking for the player-spell damage formula.

Case 21, **`HandleScriptedDamageEvent_candidate`** (`0x08016E64`), spans
both `0x08016E64` and `0x0801732C` -- one function, not two (the
`unaff_rX` shared-epilogue false-split pattern documented elsewhere in
this codebase). Its *tail* (`Object+0x60` status byte, 5 sub-states 1-5)
dispatches into fixed-damage crit/faint-sequence handling (`5`/`20`/`20`/
`45`, no RNG roll) -- scripted/special-event damage, not the normal
per-turn combat formula; no call to `Mt19937RandRange` appears anywhere
in this dispatcher's address range (`0x08016000`-`0x08017FFF`). Its
*head*, however (`Object+0xc` flag bits `0x40000`/`0x8000`), is the real
**Special Move trigger** -- see below.

#### Special Move dispatch (the same function's head)

`HandleScriptedDamageEvent_candidate`'s `0x40000`-flag branch is what
actually fires a character's Special Move script: for `Harry`, it reads
`(&g_abHarryCardEffectId)[DAT_03003f44]` (the currently-selected
Folio Universitas card slot) and calls `FUN_08018b70` on it -- **"Special
Move" opens the Folio Universitas for Harry**. For `Hermione`, it reads
`(&g_abHermioneLectureEffectId_candidate)[bSpellId]` (her lecture
selection, stored in the same `bSpellId` field spells use) and does the
same. **For any other fighter type (Ron, Buckbeak), this branch just
calls `FUN_08015484(unaff_r7,0)` and returns -- no `g_ab*EffectId`-style
table lookup happens here at all.** So Ron's Special Move (`Stink
Pellet`/`Wizard Cracker`/`Stink Pellet 2`, string ids `2301`-`2303` in
`data/text/en_us.json`) is **not** dispatched through this code path;
which effect id(s) it uses is unconfirmed -- `FUN_08015484` not traced.
There's a byte array right before `g_abHermioneLectureEffectId_candidate`
in ROM, `DAT_0805150a` (`0x0805150a`, read at `0x08017226` in this same
function's *separate* `0x8000`-flag branch, unconditional on fighter
type): `[44, 46, 45, 49, 51, 50, 41]` -- entries `3`-`5` (`49,51,50`) are
exactly `g_abHermioneLectureEffectId_candidate`'s 3 values, i.e.
`DAT_0805150a` and `g_abHermioneLectureEffectId_candidate` are literally
the same ROM bytes read through two differently-based pointers/branches,
not two independent tables. Whether entries `0`-`2` (`44,46,45`) are
Ron's 3 move effect ids (a tempting read, given they sit immediately
before Hermione's slice and the in-game glossary lists Hermione's and
Ron's Special Moves back-to-back) or unrelated data that happens to be
adjacent is unconfirmed -- the `0x8000` branch fires unconditional of
fighter type using `bSpellId` as the index, and whether Ron's UI ever
sets `bSpellId` into this array's range is not traced. **Left unnamed
pending that trace** -- do not assume `44`/`45`/`46` are Ron's moves
without confirming the calling context. If entries `0`-`2` do turn out
to be Ron's moves in the glossary's display order (`Stink Pellet`,
`Wizard Cracker`, `Stink Pellet 2` -- string ids `2301`-`2303`), that
would make effect id `46` `Wizard Cracker` specifically -- consistent
with [`battle-ui.md`](battle-ui.md)'s "Ron's Special Move effect ids", which resolves this
independently via the effect scripts' own `StatusEffect` content, once
this table's real meaning is traced.

The other case targets (`0x080160FC`, `0x08017A7C`, `0x080161A2`,
`0x08017ADE`, `0x0801618A`, `0x080161FE`) haven't been walked yet.

## Player spell/action damage -- `ResolveSpellAttack` (`0x08017C24`)

Found via `TickPlayerActionState_candidate`'s case `0x1A`, which calls it
as `ResolveSpellAttack(attackerIndex, targetIndex)` and stores
the result into `DAT_0300274a` -- the same scratch slot
`ResolveMeleeAttack`'s caller uses. This is the Harry/Hermione/Ron
damage path (`ResolveMeleeAttack` is proven melee-only and covers
enemies/Buckbeak instead); structurally similar in shape to
`ResolveMeleeAttack` but a genuinely different formula, not a shared
routine.

**The NPC-vs-PC split itself is now traced, PROVEN, in
`TickBattleTurnStateMachine_candidate`'s case 4** (see "Poison's per-turn
damage tick" above for that function's overview): non-`Enemy` fighters
call `DispatchPendingAction()` directly (menu-driven action resolution,
which for a normal spell cast leaves `bPendingActionKind ==
None` and sets anim state `0x1a` -- reaching `ResolveSpellAttack` via
`TickPlayerActionState_candidate`'s own case `0x1A`), while `Enemy`
fighters skip `DispatchPendingAction()` entirely and set anim state
`0x1a` directly after an AI/target-select call
(`FUN_0800e39c`) and a can't-move check (`FUN_0800ffac`, the same one
used for the menu-input gate). The reason this cashes out as "enemies
always melee, PCs always cast" isn't a per-turn decision at all: it's
which `pfnTick` callback got registered on the fighter's `Object` once,
at init -- `InitMonsterBattleActor` hardcodes
`TickFighterAttackAnimState_candidate` (`0x08015608`) into every enemy
Object's `+0x98` slot, and that dispatcher's case 0 is what calls
`ResolveMeleeAttack` (itself additionally gated on `fighterType==0xFF`
at its call site). Whatever initializes party members' Objects (not yet
found -- no "InitPlayerBattleActor" analog located) must instead wire
them to `TickPlayerActionState_candidate` (`0x0801602C`). Buckbeak
(`fighterType==3`, non-`Enemy`) is the one wrinkle worth flagging: he
goes through the same `DispatchPendingAction()`/`None` path as a normal
spellcaster (`TrackSpellFamiliarity` explicitly excludes him via
`fighterType != Buckbeak`, but the anim-state dispatch itself doesn't
special-case him) -- whether he actually reaches `ResolveSpellAttack` in
practice, or whether some other gate prevents it, isn't traced.

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
              + divsi3_thumb(g_awSpellPowerScale[idx] * attacker->bLevel, 9);

        // per-character modifier
        if (attacker->bFighterType == Hermione) power = power * 17 / 16;
        else if (attacker->bFighterType == Ron)  power = power * 15 / 16;
        // Harry: no modifier

        if (power == 0) power = 1;
        if (attacker->bStatusFlags & 0x40) power = power * 4 / 3;   // 0x40 = ProperWandTechnique
    }

    if (power == 0) return 0;

    // crit-chance scaling factor from the attacker's own stat, capped at 12
    uint critScale = attacker->bLevel < 2 ? 0
                     : min(12, (attacker->bLevel >> 1)
                               + ((attacker->bStatusFlags & 0x40) ? attacker->bLevel >> 2 : 0));

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

### `BattleFighter+0xE` (`bLevel`) -- PROVEN

`ResolveSpellAttack` reads `bLevel` twice: as the term multiplying
`g_awSpellPowerScale[idx]` (divided by 9) into base power, and
independently (`>>1`, capped at 12) as the spell crit-chance scale.
`ResolveMeleeAttack` never reads it, and no monster ever becomes
`ResolveSpellAttack`'s attacker, so a monster's own value has no
confirmed reader -- see the `MonsterTable` correspondence table above.

**`bLevel` is a level counter.** `LevelUpFighter_candidate`
(`0x080151B0`) increments it by 1 (capped at `99`) and indexes a
per-character, per-level stat table with the new value, writing each
row's values into the matching `BattleFighter` fields, full-healing
HP/MP, then calling `ApplyEquipmentStatModifiers_candidate`
(`0x08026870`) to reapply gear on top.

The three tables (`CharacterLevelEntry_candidate[100]`, 12-byte rows,
extracted to `data/levels/` -- see `tools/levels/level_codec.py`):

| Table | US address |
|---|---|
| `g_pHarryLevelTable_candidate` | `0x0804FE50` |
| `g_pRonLevelTable_candidate` | `0x08050300` |
| `g_pHermioneLevelTable_candidate` | `0x080507B0` |

Row layout (12 bytes, the last 2 always-zero padding): `wHp_max` (u16),
`wMp_max` (u16), `wXpDeltaForLevel_candidate` (u16), `bStat_speed`,
`bAccuracy`, `bDefenseFactorPercent_candidate`, `bMagicDefensePercent`
(the last two both dead -- see below).

Related functions: `RecomputeBaseStatsFromLevel_candidate`
(`0x080150B4`) does the same lookup for `bStat_speed`/defense without
incrementing the level, used when only reapplying equipment (it resets
defense/`bMagicDefensePercent` to `100` first).
`ApplyEquipmentStatModifiers_candidate` walks each of the 3 party
members' 6 equipped-item slots (`DAT_03003834`) and subtracts each
item's `nType/2` from defense%, `ItemEntry.dwMagicDefenseReduction` from
`bMagicDefensePercent`, and `nParam` from `bStat_speed` (clamped) --
heavier gear trades speed for defense.
`ApplyPendingLevelUps_candidate` (`0x0801D308`) runs
`LevelUpFighter_candidate` for all 3 party members, `N` times.

**`bMagicDefensePercent` is display-only -- PROVEN dead in damage math,
UNCONFIRMED elsewhere.** It's tracked identically to `bDefenseFactorPercent`
(reset to `100`, reduced by gear, shown as `100 - value`) and read by two
Status/Equip-screen functions -- `DrawStatusEquipStatsPanel` (`0x0803A0F0`,
the stat-list panel) and `DrawEquipItemStatComparison` (`0x080364A8`, the
equipment change screen's before/after comparison) -- both confirming the
in-game "Magic Def" label. But neither `ResolveMeleeAttack` nor
`ResolveSpellAttack` reads it anywhere; unlike `bDefenseFactorPercent`
(consumed by `ResolveMeleeAttack`'s `damage * value / 100`), no damage
formula found so far applies this stat.

**Verified against real in-game data** (Harry Lvl7, Hermione Lvl8, Ron
Lvl5, no equipment):

- `bLevel` is 0-indexed -- displayed Level `N` is table row `N-1`.
- `wHp_max`/`wMp_max` match the row directly.
- Displayed agility is `255 - bStat_speed`; the turn-order byte and
  displayed agility are inverses.
- **Two table columns never take effect**: displayed defense and
  magic-defense always read `0` (`100 - 100`), because
  `RecomputeBaseStatsFromLevel_candidate` resets both to `100`
  immediately after `LevelUpFighter_candidate` sets them from the table.
- Displayed next-level XP is the *cumulative* sum of
  `wXpDeltaForLevel_candidate` across rows `0..bLevel` -- not any single
  row, and not what `LevelUpFighter_candidate` writes into `wRewardXp`
  (a plain overwrite with the new row's delta alone). Whatever compares
  real XP against that cumulative threshold isn't located.

**Player fighters get `bLevel` from `g_pPartyMasterStats_candidate`
(`0x030024EC`), not `MonsterTable`.** `InitPlayerBattleActor_candidate`
(`0x080149C4`, called from `SetupBattleRoster_candidate`) copies a
persistent, `BattleFighter`-shaped 3-entry array (one per
Harry/Hermione/Ron) into the live roster at matching offsets: `bLevel`
(`+0xE`), `wHp`/`wHp_max` (`+8`/`+0x24`), `wMp`/`wMp_max`
(`+0xA`/`+0x26`), `bStat_speed` (`+0x2A`), `bAccuracy` (`+0x2B`), and
`bDefenseFactorPercent` (`+0x2E`) -- which settles
that last field's origin: it is a player-only stat, never populated for
monsters. Buckbeak (`fighterType == 3`, outside the 3-entry array) gets
hardcoded defaults: `wHp`/`wMp_max` 400/999, `bLevel` `0x32`,
`bStat_speed` `10`, `bAccuracy` `0x65`, `bDefenseFactorPercent` `100`.

### `BattleFighter+0x3C`/`+0x3D` -- `bSpellId` (enum `SpellId`) / `bSpellLevel`

Added to the struct at the offsets `ResolveSpellAttack` reads.
`bSpellLevel` (0-2) explains `ShowBattleMessage`'s
`SpellLevelUp` case -- spells have 3 power tiers, and that case's
`FUN_0803FF70`-driven jingle is almost certainly what plays when this
field increments.

**`SpellId` has 10 values (`0`-`9`), PROVEN directly from the Cast Spell
menu's own name-lookup code, not inferred from `ResolveSpellAttack`'s
switch.** `DrawBattleMenuText` (`0x08011520`), the function that draws
every battle-menu screen's text, has a `bMenuScreen == 2` (spell list)
case reading `GetDialogText(g_abSpellIdByCursor[...] + 0x95F)` -- i.e.
**`spellId + 0x95F` is the real in-game name for that `SpellId`**, a
direct display-time mapping, not an inference. Reading
`data/text/en_us.json` string ids `2399`-`2408` against this formula
gives the real enum, confirmed one-to-one:

| `SpellId` | Text id (`+0x95F`) | Name |
|---|---|---|
| `0` | `2399` | `Flipendo` |
| `1` | `2400` | **`Informus`** |
| `2` | `2401` | `Verdimillious` |
| `3` | `2402` | `Diffindo` |
| `4` | `2403` | `Incendio` |
| `5` | `2404` | `WingardiumLeviosa` |
| `6` | `2405` | `PetrificusTotalus` |
| `7` | `2406` | `Glacius` |
| `8` | `2407` | `Fumos` |
| `9` | `2408` | `Spongify` |

`Spongify` is `SpellId` `9`, the `9` in `g_abSpellIdByCursor`'s Ron row
(`[0,2,4,6,9,5,0]`), matching `data/text/en_us.json` string `937`:
"Harry receives Diffindo, Ron receives Spongify, and Hermione receives
Glacius!". `PetrificusTotalus = 6` is independently PROVEN via
`g_awSpellMpCost` below.

`ResolveSpellAttack`'s `aSpellEffectiveness` switch has no case for
**four** of these ids -- `1`/`6`/`8`/`9` (`Informus`,
`PetrificusTotalus`, `Fumos`, `Spongify`), all non-damage status spells
(documentation, paralysis, evasion, attack-weaken), none of which
compute a per-monster effectiveness roll.

**Do not conflate this enum with the Folio Bruti screen's spell
ordering.** That screen has its own separate 0-7 index list (see
[`../formats/folio_bruti.md`](../formats/folio_bruti.md)) which excludes
`Informus` and `Fumos` entirely, since neither has a monster resistance
stat to display; its "always 100% effective" pair (Petrificus Totalus,
Spongify) is stated in *that* list's indices, not these.

### The two base-power tables, decoded

`g_awSpellPowerBase` (`0x080538EC`) and
`g_awSpellPowerScale` (`0x08053928`), both `ushort[30]`
(`SpellId` `0`-`9`) indexed `spellId*3 + spellLevel`. `g_awSpellPowerScale`
is the term multiplied by the attacker's `bLevel` and divided
by 9 (via `divsi3_thumb`, the Thumb-mode signed-division runtime --
**not** a spell-specific scaling helper, same algorithm shape as the
already-documented `__rt_divsi3`/`udivsi3_thumb`).

| Spell | lvl0 base/scale | lvl1 base/scale | lvl2 base/scale |
|---|---|---|---|
| Flipendo | 10 / 4 | 20 / 8 | 15 / 10 |
| Informus | 0 / 0 | 0 / 0 | 0 / 0 |
| Verdimillious | 15 / 6 | 25 / 12 | 20 / 14 |
| Diffindo | 30 / 18 | 30 / 19 | 40 / 20 |
| Incendio | 23 / 8 | 35 / 16 | 45 / 18 |
| WingardiumLeviosa | 35 / 20 | 45 / 21 | 55 / 22 |
| PetrificusTotalus | 0 / 0 | 0 / 0 | 0 / 0 |
| Glacius | 30 / 18 | 40 / 20 | 45 / 20 |
| Fumos | 0 / 0 | 0 / 0 | 0 / 0 |
| Spongify | 0 / 0 | 0 / 0 | 0 / 0 |

Power generally grows with level as expected, though not always
monotonically (Flipendo's base term dips 20->15 from level 1 to 2,
offset by its scale term still growing 8->10) -- not investigated
further whether that's deliberate balancing or two independent curves
that just happen to combine this way. All four non-damage/status spells
(`Informus`, `PetrificusTotalus`, `Fumos`, `Spongify`) are `0`/`0` at
every level -- consistent, since none of them compute damage via this
path.

### Spell MP cost -- `g_awSpellMpCost` (`0x08053964`), PROVEN

`ushort[30]`, indexed `spellId*3+level`, same shape as the power tables.
Deducted directly from `BattleFighter.wMp` in
`TickPlayerActionState_candidate` case `0x1A` -- all spells share one MP
pool, no separate per-spell resource type. Confirmed against a
community-written GameFAQs guide's real per-spell MP costs (see the
attribution note near the top of this document): all 6 unambiguous
spells match exactly, and `PetrificusTotalus`'s `Uno`/`Duo` costs
(`10`/`15`) match `SpellId` value `6`'s row here, independently PROVING
`PetrificusTotalus=6`:

| Spell | lvl0/1/2 cost |
|---|---|
| Flipendo | 0/10/20 |
| Informus | 0/0/0 |
| Verdimillious | 3/15/25 |
| Diffindo | 10/0/0 |
| Incendio | 6/20/30 |
| WingardiumLeviosa | 20/30/40 |
| PetrificusTotalus | 10/15/20 |
| Glacius | 15/25/0 |
| Fumos | 8/30/0 |
| Spongify | 10/0/0 |

`Informus` costing `0` MP at every level matches its in-game description
having no MP-cost callout, unlike the other 9 spells (see the "The
following list explains what each spell does" help text above). `Spongify`
costing `10` MP at level `0` only (`Uno`) and `0`/`0` past that matches
`Diffindo`'s identical shape (`10/0/0`) -- both single-level-only spells,
see `g_abSpellMaxLevel` below.

Its companion byte array at the same index,
**`g_abSpellEffectId_candidate`** (`0x080538B0`), holds a
per-`(spellId, level)` effect-script id fed into `FUN_08018b70` -- not a
resource-type selector. All 30 entries are read and named in
`tools/objscript/script_names.json`:

| `SpellId` | Spell | Effect ids (Uno/Duo/Tria) | Max level | Script has `StatusEffect`? |
|---|---|---|---|---|
| `0` | Flipendo | 2 / 3 / 21 | 3 | no |
| `1` | Informus | 38 / 38 / 38 | 1 | yes (`BumpMonsterDocLevel`) |
| `2` | Verdimillious | 19 / 20 / 26 | 3 | no |
| `3` | Diffindo | 22 / 22 / 22 | 1 | no |
| `4` | Incendio | 23 / 24 / 25 | 3 | no |
| `5` | WingardiumLeviosa | 28 / 28 / 28 | 1 | no |
| `6` | PetrificusTotalus | 33 / 34 / 33 | 2 | yes (`Paralyze25`) |
| `7` | Glacius | 30 / 31 / 30 | 2 | no |
| `8` | Fumos | 11 / 32 / 32 | 2 | yes (`HiddenMain`/`Secondary`) |
| `9` | Spongify | 29 / 29 / 29 | 1 (aliased) | yes (`AttackWeakened`) |

Two things fall out of reading the effect-id and max-level columns
together:

- **Repeated effect ids are unreachable slots, not shared content.** A
  spell can never be cast above its `g_abSpellMaxLevel` (see "Spell
  familiarity/leveling" below), so every id at or past that level is
  dead table content: `Informus`/`Diffindo`/`WingardiumLeviosa` never
  leave `Uno`, and `PetrificusTotalus`/`Glacius`/`Fumos` never reach
  `Tria`. `Flipendo`/`Verdimillious`/`Incendio`, the three spells that
  do reach level 3, are exactly the three with genuinely distinct
  scripts per level -- so distinct-per-level content is a real
  capability the engine uses where it's reachable.
- **Only the four non-damage spells carry a `StatusEffect` opcode.**
  The other 13 scripts are pure cast animation; their damage comes from
  `ResolveSpellAttack` above, not from the bytecode. Verified directly
  against the extracted script text.

`g_awSpellMpCost` follows the same shape -- `Fumos`'s `[8,30,0]` has a
real cost for `Uno`/`Duo` and an unused `0` in the `Tria` slot it never
reaches.

### Spell familiarity/leveling -- `TrackSpellFamiliarity` (`0x08010008`), PROVEN

Every time a fighter's pending action resolves through the normal
action path (`DispatchPendingAction`, `0x080100a0`, cases `None` and
`Informus` -- see below), it calls
`TrackSpellFamiliarity(fighterType, spellId, spellLevel, pSpellProgress)`,
which implements the "spells level up with use" mechanic:

```c
void TrackSpellFamiliarity(FighterType fighterType, SpellId spellId, char spellLevel,
                            SpellProgressBlock *pSpellProgress)
{
  byte *pCastLevel = pSpellProgress->aSpellCastLevel + spellId;
  if (*pCastLevel < g_abSpellMaxLevel[spellId] && fighterType != Buckbeak) {
    byte *pUsageProgress = pSpellProgress->aSpellUsageProgress + spellId;
    *pUsageProgress += spellLevel + 1;              // casting at a higher level earns more progress
    int partySpellIndex = spellId + fighterType * 0x48;
    g_abPartySpellUsage[partySpellIndex] += spellLevel + 1;
    if (g_abSpellLevelUpThreshold[*pCastLevel] <= *pUsageProgress) {
      ShowBattleMessage(SpellLevelUp, 0, 0);
      (*pCastLevel)++;
      *pUsageProgress = 0;
      g_abPartySpellLevel[partySpellIndex]++;
      g_abPartySpellUsage[partySpellIndex] = 0;
    }
  }
}
```

**`SpellProgressBlock`** (28 bytes) is a standalone struct typed only for
this function's 4th parameter -- it is *not* embedded into `BattleFighter`
itself (that would force every other already-reviewed function's
`fighter->wHp` into a longer field-access chain for no benefit). Its
fields are `BattleFighter`'s own `wHp`/`wMp`/`wRewardXp`/`bLevel`/
`bUnk_0x0F` followed by two embedded 10-entry (one per `SpellId`, `0`-`9`)
byte arrays, added directly to `BattleFighter` itself at their real
offsets: **`aSpellCastLevel`** (`+0x10`, the fighter's current mastered
level *per spell*, distinct from `bSpellLevel` which is the level chosen
for *this turn's* cast) and **`aSpellUsageProgress`** (`+0x1A`, progress
toward that spell's next level-up). Both arrays are confirmed 10 bytes
each by `docs/formats/save.md`'s save-slot serializer, which packs
`BattleFighter+8`..`+0x23` as one contiguous 28-byte run per party
member -- `aSpellCastLevel` and `aSpellUsageProgress` sit back-to-back
with no gap between them or before `wHp_max`. The call site passes
`(SpellProgressBlock *)&fighter->wHp`, i.e. `BattleFighter+8` -- confirmed
bounded on both sides: it starts exactly at `wHp` and its last field ends
exactly at `wHp_max` (`+0x24`), with `g_abPartySpellUsage`/
`g_abPartySpellLevel`'s call-site
math (`spellId + fighterType*0x48`) additionally confirming the `0x48`
figure as `BattleFighter`'s own stride, reused for a separate persistent
(likely save-data) tracking array, one `0x48`-strided block per
`FighterType`, only the first 8 bytes of each block used (indexed by
`SpellId`).

Two small parallel tables, immediately adjacent in ROM (`g_abSpellMaxLevel`
at `0x0804e5e0`, 9 bytes; `g_abSpellLevelUpThreshold` immediately after at
`0x0804e5e9`, 3 bytes -- bounded on the far side by the already-documented
`DAT_0804e5ec` used elsewhere in `ShowBattleMessage`'s dialog dispatch):

- **`g_abSpellMaxLevel[9]`** (indexed by `SpellId`): `[3,1,3,1,3,1,2,2,2]`
  -- the max-level column in the effect-id table above. Note the table
  holds exactly 9 entries (`SpellId` `0`-`8`) before
  `g_abSpellLevelUpThreshold` begins: **`Spongify` (`SpellId` `9`) has
  no entry of its own**, and `TrackSpellFamiliarity`'s
  `g_abSpellMaxLevel[9]` read for it lands one byte past the table, on
  `g_abSpellLevelUpThreshold[0]`. That aliased value is `1`, the same cap
  `Spongify`'s single-level MP-cost shape (`10/0/0`) implies it should
  have, so it is harmless in practice -- but it is a genuine
  out-of-bounds read, not a dedicated entry.
- **`g_abSpellLevelUpThreshold[3]`**: `[1, 25, 50]`, indexed by the
  spell's *current* level. Leveling `Uno`->`Duo` takes just 1 use;
  `Duo`->`Tria` takes a real 25. The third entry (`50`) is normally
  unreachable, since `g_abSpellMaxLevel` gates the level-up check before
  a maxed-out spell's usage counter can ever reach it -- not traced
  further, flagged as likely-dead data rather than assumed meaningful.

Also confirms `fighterType != Buckbeak` is an explicit, dedicated gate
here (Buckbeak doesn't cast spells, so never tracks familiarity), not an
incidental side effect of some other check.

### `DispatchPendingAction` (`0x080100a0`), PROVEN

Reads `BattleFighter.bPendingActionKind` (`+0x3b`, enum `PendingActionKind`:
`None=0, UseItem=1, SpecialMove=2, Flee=3, Informus=4`, written by the
menu confirm handlers, see [`battle-ui.md`](battle-ui.md)) for the active fighter and starts
the corresponding animation state on that fighter's `Object`:

```c
void DispatchPendingAction(void)
{
  BattleFighter *fighter = g_pFightState->pFighters + g_pFightState->bActiveFighterIndex;
  switch (fighter->bPendingActionKind) {
  case None:
  case Informus:
    ShowBattleMessage(ActionAnnounce, 0, 0);
    TrackSpellFamiliarity(fighter->bFighterType, fighter->bSpellId, fighter->bSpellLevel, &fighter->wHp);
    SetFighterAttackAnimState_candidate(fighter->pObject, 0x1a);   // same state HandleScriptedDamageEvent_candidate handles
    break;
  case UseItem:
    ShowBattleMessage(ItemUseAnnounce, fighter->bSpellLevel, 0);
    SetFighterAttackAnimState_candidate(fighter->pObject, 0x04);
    break;
  case SpecialMove:
    if (fighter->bFighterType == Harry) fighter->bSpellId = (SpellId)g_nFolioUniversitasSlot;
    ShowBattleMessage(SpecialMoveAnnounce, fighter->bSpellId, 0);
    SetFighterAttackAnimState_candidate(fighter->pObject, 0x15);
    if (fighter->bFighterType == Hermione) g_pFightState->nHermioneLecturesKnown_candidate = 1;
    else if (fighter->bFighterType == Ron) g_pFightState->nRonMovesKnown_candidate = 1;
    break;
  case Flee:
    if (Mt19937Chance(0x4b) == 0) {
      ShowBattleMessage(EscapeBlocked, 0, 0);
      SetFighterAttackAnimState_candidate(fighter->pObject, 0x05);
    } else {
      PlaySoundById(0x9d);
      PushGameMode_candidate(8, 3, DAT_03003b50);
    }
  }
}
```

Two findings of note:

- **`SpecialMove` is not general spellcasting** -- this is exclusively the
  Special Move path (`SpecialMoveAnnounce`, anim state `0x15`, and it's
  what actually sets `nHermioneLecturesKnown_candidate`/
  `nRonMovesKnown_candidate` to `1`, closing the loop with
  the top-level menu's graying check in [`battle-ui.md`](battle-ui.md) -- using a Special
  Move once is literally what un-grays that menu entry for later turns).
  A regular `Cast Spell` selection leaves `bPendingActionKind` at `None`.
  For Harry specifically, `bSpellId` is overwritten with
  `g_nFolioUniversitasSlot` (the raw card slot, `0`-`15`) purely so the
  announce message can index by it. That value is **not** a `SpellId`
  despite the cast -- real ids stop at `9`, card slots run to `15` --
  the same field-reuse trick `HandleScriptedDamageEvent_candidate` uses
  for display elsewhere in this document.
- **`Informus` has no special-case branch here.** It shares the `None`
  case outright, driving the same anim state (`0x1a`) and the same
  `TrackSpellFamiliarity` call an ordinary spell cast does -- which is
  what a first-class `SpellId` looks like. Its whole gameplay payload
  lives in its effect script instead: `g_abSpellEffectId_candidate[1]`
  = effect id `38` (`data/scripts/SpellInformus.txt`), whose one real
  gameplay opcode is `StatusEffect` case `0xC`
  (`BumpMonsterDocLevel`), the Folio Bruti populate action -- matching
  its in-game description ("Cast upon a creature to learn about its
  strengths and weaknesses", string id `1494`) exactly. Zero base power
  and zero MP cost at every level, so it deals no damage and needs no
  resource. See [`battle-ui.md`](battle-ui.md) for the menu handler that
  sets `bSpellId = 1`.
