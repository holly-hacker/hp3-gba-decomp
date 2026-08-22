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
| `0x2A` | u8 | **`bStat_speed`** (`MonsterTable+0x03`) | **PROVEN** -- turn-order/initiative value, not defense; see "Turn order" below | -- |
| `0xE` | u8 | **`bLevel`** | **PROVEN as a struct field** -- read by `ResolveSpellAttack` as the caster's spell power scale term and spell crit-chance term (see below), sourced from `g_pPartyMasterStats_candidate` for player casters. For monster records (`MonsterTable+0x02`), **UNCONFIRMED** -- monsters never reach `ResolveSpellAttack` as attacker, and `ResolveMeleeAttack` doesn't read this offset | -- |
| `0x2B` | u8 | **accuracy** | **PROVEN** -- see "Attack resolution" below | jlun2 (led here) |
| `0x2C` | u8 | **`bCritChance`** (`MonsterTable+0x05`) | **PROVEN** -- read as a roll threshold in the bonus-damage check, see below. Monster-only: never populated for player fighters | jlun2 (led here) |
| `0x2E` | u8 | defense scaling, percent (`damage = damage * this / 100`) | PROVEN as a formula input; **origin not traced** -- `InitMonsterBattleActor` never writes it from `MonsterTable`, so monster records may rely on a default/zero here, or it's set by a separate (player-only?) code path not yet found | jlun2 (led here) |
| `0x30` | u16 | **base damage roll, min** (`MonsterTable+0x06`) | **PROVEN** -- fed directly into `Mt19937RandRange` as the attack's damage roll | jlun2 (led here) |
| `0x32` | u16 | **base damage roll, max** (`MonsterTable+0x08`) | **PROVEN** | jlun2 (led here) |
| `0x3A` | u8 | selected action/spell index for this turn | STRUCTURAL MATCH -- used across multiple AI/dispatch functions (e.g. `DispatchPendingAction`, `0x080100a0`) | -- |
| `0x42` | u8 | status-flags bitfield | PROVEN as a formula input, bits below | jlun2 (led here) |
| `0xC` | u16 | `wRewardXp` (`MonsterTable+0x10`) | PROVEN | `InitMonsterBattleActor` |
| `0x28` | u16 | `wRewardGold` (`MonsterTable+0x12`) | PROVEN | `InitMonsterBattleActor` |
| `0x3E` | u8 | `bUnk_0x3E`, set to `0xff` on init | UNCONFIRMED, no reader traced | `InitMonsterBattleActor` |

`InitMonsterBattleActor` also spawns and wires the fighter's sprite
`Object`(s); several previously-unnamed `Object` fields are now typed
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
  analog found yet, same gap as `bDefenseFactorPercent_notFromMonsterTable`).
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
5's sub-dispatch; see the case-5 row in the dialog-text table below).
Defaults to `0x12` (18, "none"). Opcode `0x97`'s status-applying cases
set it to a specific sub-case value right where they set the
corresponding bit -- this is the evidence behind bits `0x02`/`0x10`
below (`0x04`/`0x08`/`0x01` are PROVEN via a direct adjacent
`ShowBattleMessage` call instead, not `field_0x14a8`).

- **bit `0x01`** = **Hidden** status. PROVEN: opcode `0x97` cases 8/9
  (`0x0801a7b6`/`0x0801a7e8`) OR this bit in, then call
  `ShowBattleMessage(Hidden, argA, targetIndex)` -- byte-for-byte
  identical apart from `argA` (`0` for case `8`, `1` for case `9`).
  Inside `ShowBattleMessage`'s `Hidden` case, `argA` gates a single
  call: `argA == 1` calls `PrepareBattleMessageDisplay_candidate()`
  (opens a fresh message box) before drawing "Harry is hidden from
  view!"-style text; `argA == 0` skips it and draws straight into
  whatever message box is already open. So case `9`/`HiddenMain`
  opens its own box (a standalone announcement), while case
  `8`/`HiddenSecondary` assumes one is already open and just appends to
  it -- matching the
  root-cast-opens-the-box / spawned-copies-append-to-it pattern below.
  Read on the
  *defender* in `ResolveMeleeAttack`: reduces the attacker's effective
  accuracy by 25, and gates the bonus-damage/crit check further down
  (must be clear for that check to run) -- consistent with "target is
  hidden from view." **Confirmed spell: Fumos**, a `bSpellId`-8 spell
  exclusive to Hermione (`g_abSpellIdByCursor`'s Hermione row is the only
  one containing `8`; see "Spell familiarity/leveling" below for the full
  trace from her spell-cast menu through to its two scripts). Fumos makes
  a target harder to hit (`Uno`: one ally, effect id `11`, script
  `SpellFumosUno`; `Duo`: the whole party, effect id `32`, script
  `SpellFumosDuo`), matching bit `0x01`'s accuracy-reduction effect
  exactly -- `SpellFumosUno` applies `StatusEffect` case `9`
  (`HiddenMain`) directly; `SpellFumosDuo` applies the same case `9`
  on its root cast and recursively spawns copies of itself
  (`SpawnEffect 32`) for the rest of the party, each spawned copy taking
  case `8` (`HiddenSecondary`) instead via the `bScriptLocalA`
  root-vs-spawn idiom (see
  "The script-local bytes" in `../formats/object_script.md`).
- **bit `0x02`** = **Poisoned**. PROVEN: opcode `0x97` case 5
  (`0x0801a71c`), gated on `(bStatusFlags & 0x06) == 0` (i.e. not
  already `Poisoned` or `PoisonImmune`), sets the bit alongside
  `FUN_0801b590` (a particle/VFX spawn) and `field_0x14a8 = 3` -- sub-case
  `3` of `ShowBattleMessage`'s case-5 dispatch is "Harry is poisoned."
  (see the dialog-text table below). Not read by either damage-resolution
  function directly -- **but its per-turn damage tick is now located**,
  see the new section below.

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
        ShowFloatingDamageNumber_candidate(fighters[i].bPoisonDamage_candidate, 4, i, 0);   // floating damage-number popup
        ApplyStatusDamageToFighter_candidate(fighters[i].bPoisonDamage_candidate, i);        // apply the damage
        field_0x1068 = 0x3c;   // (re-)arm a delay timer
    }
}
```

Both calls read a newly-identified field, **`BattleFighter+0x43`
(`bPoisonDamage_candidate`)**, immediately after `bStatusFlags` -- not
copied from `MonsterTable` by `InitMonsterBattleActor` (which never
touches this offset), so its value's origin for monster fighters is
still unknown; likely written by the same status-effect opcode that sets
the `Poisoned` bit itself (case 5, `0x0801a71c`, not fully walked past
its bit-set/VFX call), not traced further here.

This decompiles through a mistyped pointer as
`aSpellEffectiveness[iVar10+0xe]`/`[iVar10+0xf]` -- **not** a real read
of the 6-byte effectiveness array (`+0x34`-`+0x39`); `iVar10` is
`fighterIndex * 0x48` (`BattleFighter`'s own stride) and the constant
offsets `+0xe`/`+0xf` land at absolute `+0x42`/`+0x43`
(`bStatusFlags`/`bPoisonDamage_candidate`), well past the declared
array's bounds. Ghidra's decompiler expresses this literally because the
underlying pointer is typed to `aSpellEffectiveness`'s element type; the
real semantics are the two fields above, not spell-effectiveness data at
all.

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
  weakened.") exactly. **`Spongify` causes this bit -- PROVEN,
  `SpellId` `9`** (not `1`, see the `bSpellId` writeup above):
  `g_abSpellEffectId_candidate[9*3+level]` is `[29,29,29]`
  (`data/scripts/SpellSpongify.txt`, effect id `29`), whose only
  gameplay opcode is exactly `StatusEffect 6 0 0`. This is the "6
  unambiguous spells" identification this doc's `g_awSpellMpCost` writeup
  already relied on, now traced all the way to the real applying case.
  `Poisoned` has no `SpellId`/lecture/card source of its own -- its only
  confirmed source is the monster-attack table (effect id `27`,
  `SpecialMonsterPoisonBite`, see "Monster special-attack effects"
  below).
- **bit `0x10`** = **Paralyzed**. PROVEN: applied through a dedicated
  helper, `FUN_0801b430` (`0x0801b430`), called from five opcode `0x97`
  cases (`10`/`Paralyze25`, `0x11`/`Paralyze99`,
  `0x12`/`Paralyze80`, `0x16`/`ParalyzeMonster`,
  `0x17`/`ParalyzeMonsterChance` -- the last confirmed via the monster
  special-attack writeup below, gated by its own extra
  `Mt19937ChanceNoisy` roll before calling this same helper). It only sets the bit
  if `bStatusFlags & 0x90 == 0` (i.e. not already paralyzed, nor bit
  `0x80` set); otherwise it fires `ShowBattleMessage(ImmuneToParalysis,
  ...)` when its `param_2` is nonzero. Case `0x16`'s call site sets
  `field_0x14a8 = 4` on success -- sub-case `4` of `ShowBattleMessage`'s
  case-5 dispatch is "Harry is paralyzed."/"The opponent is paralyzed!"
  (same `field_0x14a8` mechanism as `Poisoned` above). Not read by
  `ResolveMeleeAttack`/`ResolveSpellAttack` (paralysis instead gates
  action/turn selection, see the escape-chance mechanic just below).

  **The third parameter to `FUN_0801b430` (`0x19`/`0x63`/`0x50`/... per
  call site) is a starting escape-chance percentage, not a duration --
  PROVEN.** It's stored into a new `BattleFighter` field,
  `bParalysisEscapeChance_candidate` (`+0x44`, right after
  `bPoisonDamage_candidate`). Every battle turn,
  `TickBattleTurnStateMachine_candidate`'s menu-input/enemy-turn-start
  cases (`3`/`4`) call `RollFighterParalysisEscape_candidate`
  (`0x0800FFAC`) before letting a fighter act:

  ```c
  int RollFighterParalysisEscape_candidate(uint fighterIndex) {
      BattleFighter *f = &g_pFightState->pFighters[fighterIndex];
      if (!(f->bStatusFlags & Paralyzed)) return 0;               // not paralyzed, acts normally
      if (!Mt19937ChanceNoisy(f->bParalysisEscapeChance_candidate)) {
          f->bParalysisEscapeChance_candidate += 25;               // failed roll: chance goes up for next turn
          return 1;                                                 // can't move this turn
      }
      ClearParalyzedFighter_candidate(fighterIndex);                 // broke free: clears Paralyzed, sets Unk_0x80
      return 3;                                                       // "can move again"
  }
  ```

  (`Mt19937ChanceNoisy(n)` succeeds when a `0-99` roll is `<= n`, i.e.
  `n` is literally a percent-out-of-100 chance -- confirmed against its
  own decompile.) So `bParalysisEscapeChance_candidate` is the *current*
  per-turn chance to break free, re-rolled every turn the fighter would
  otherwise act, ratcheting up by `25` on every failure until it
  eventually succeeds -- not a countdown timer. `TickBattleTurnStateMachine_candidate`'s
  caller shows `ShowBattleMessage(CanMoveAgain, ...)` on a `3` return and
  `ShowBattleMessage(CantMove, ...)` on a `1` return, which is where
  "Harry can move again!"/"Harry can't move." actually come from each
  turn -- not from the `StatusEffect` case's own one-time message.
  `ClearParalyzedFighter_candidate` is `FUN_0800ea68`, the same
  `Paralyzed`-clearing half `CureAilments` (case `0x14`) calls -- so
  breaking free naturally and being manually cured (Remove Jinx/
  Reparifors) go through the identical cleanup path.

  **Case `10`/`Paralyze25` is conditionally gated, cases
  `0x11`/`0x12` (`Paralyze99`/`Paralyze80`) are not** --
  confirmed by reading each call site's `param_2` (`FUN_0801b430`'s 2nd
  arg): case `10` (`0x0801a818`) passes `0` (or `1` only if the target
  fighter's roster byte reads `0xFF`, a sentinel case), while cases
  `0x11`/`0x12` (`0x0801a83e`/`0x0801a84a`) hardcode `1`. Inside
  `FUN_0801b430`, the whole apply-or-skip block is additionally gated by
  `(g_wEffectContextValue != 0 && g_wEffectContextValue != 0x3e9) || param_2 != 0` -- i.e.
  with `param_2 == 0` (case `10`'s normal path), paralysis only applies
  when `g_wEffectContextValue` (written only by `FUN_08018b70`'s `param_6`, the
  effect-trigger's caller-supplied 6th argument -- not traced further)
  holds some other value; cases `0x11`/`0x12`'s `param_2 == 1`
  unconditionally satisfies the `||`, skipping that check entirely. So
  case `10` is genuinely conditional on external state (a real
  "chance"/context gate) while `0x11`/`0x12` always apply (subject only
  to the immunity-bit check both paths share). `Paralyze25`'s escape
  chance starts at `0x19` (`25`, ratcheting up by 25 each failed turn --
  free by the 4th attempt at the latest); `Paralyze99`/
  `Paralyze80` start at `0x63`/`0x50` (`99`/`80`, both escaping on
  the very next turn almost every time), matching their fire-and-forget,
  no-message-and-no-VFX-on-success code shape: they're a much lighter
  version of the status, mechanically closer to "skip one turn" than a
  real lockout. **PROVEN source:
  PetrificusTotalus** -- `SpellId` `6`'s effect ids
  (`g_abSpellEffectId_candidate` `[33,34,33]`, indexed `spellId*3 +
  castLevel`) trace to opcode `0x97` case `10` -- **confirmed directly
  against the extracted script text** for *both* effect ids `33` and `34`
  (`data/scripts/SpellPetrificusTotalusUno.txt`/`SpellPetrificusTotalusDuo.txt`,
  see `docs/formats/object_script.md`): both unconditionally contain a
  `StatusEffect 10 0 0` instruction, so both apply the same
  conditionally-gated paralysis. The two scripts differ only in animation
  timing (effect id `34` has an extra root-vs-spawned-copy branch skipping
  an initial flash animation, and uses different animation-frame operand
  values), not in whether/how paralysis is applied.

  Effect id `33` is `SpellPetrificusTotalusUno`, effect id `34` is
  `SpellPetrificusTotalusDuo` (the in-game names for cast levels `0`/`1`):
  castLevel `1` (`Duo`) is uniquely effect id `34`, while castLevel `2`
  (`Tria`) reuses castLevel `0` (`Uno`)'s effect id `33` verbatim. **Now
  resolved, PROVEN**: `PetrificusTotalus` has no player-reachable `Tria`
  cast at all -- see `g_abSpellMaxLevel` in "Spell familiarity/leveling"
  below, which caps this spell at level `2` (`Duo`); a player can never
  reach `Tria` through normal leveling, so effect id `33`'s reuse at the
  `Tria` slot is simply dead/unreachable table content, not evidence of
  a real third cast. `g_awSpellMpCost`'s row for this spell (`10/15/20`)
  having a distinct nonzero `Tria` value is table-completeness, not proof
  of reachability.
  `PetrificusTotalus` and `Spongify` share
  `SpellId` values `6`/`1` in a way that isn't decidable from
  `ResolveSpellAttack`'s effectiveness switch alone (both spells are
  absent from it identically) -- `g_awSpellMpCost` below is what pins
  `PetrificusTotalus=6` specifically, and this bit's opcode `0x97` case
  `10` (not case `0xc`/`0xd`, which is what `SpellId` `1` traces to
  instead) is the corroborating evidence: only the `6`/`10` pairing
  produces a paralysis effect, matching what `PetrificusTotalus` is
  known to do. **Second source, now PROVEN by name: Harry's `Snitch`
  card** (index `13` of 16 in `g_abHarryCardEffectId`, effect
  id `47`) -- its script also contains opcode `0x97` case `0x12`
  (`Paralyze80`), another bare `FUN_0801b430()` call, this time
  the unconditional-apply variant, and matches the in-game Card Combo
  Glossary's own description word for word: "Snitch causes opponent to
  lose a turn." See "Harry's 16 Folio Universitas cards" below for how
  all 16 cards were named.

  **Cases `0x16`/`ParalyzeMonster` and `0x17`/`ParalyzeMonsterChance`
  (monster-attack only) add feedback on top of the same `FUN_0801b430`
  call, and differ from each other and from
  `10`/`0x11`/`0x12`:**
  - Both pass a *script-supplied* `param_3` (the caller reads the
    effect script's own operand `2` for the starting escape chance,
    rather than one of the hardcoded constants `10`/`0x11`/`0x12` use).
  - Both set `field_0x14a8 = 4` on a successful apply -- the
    "Harry is paralyzed."/"The opponent is paralyzed!" sub-case of
    `ShowBattleMessage`'s case-5 dispatch (same mechanism `Poisoned`
    uses) -- which `10`/`0x11`/`0x12` never set.
  - `0x16` reuses `10`'s `param_2` gate (`1` only when the target
    fighter's roster byte reads `0xFF`) and, after a successful apply,
    checks that same roster byte again: if it's `0xFF` it returns with
    no further effect; otherwise it spawns the paralysis VFX
    (`FUN_0801b590`) *and* fires `ShowBattleMessage(CriticalHit, 0, 4)`
    (the field-`0x14a8`-driven text). `0x17` instead hardcodes
    `param_2 = 0` (so it can never show `ImmuneToParalysis` on a failed
    apply, unlike every other case), and on a successful apply always
    spawns the VFX with no roster-byte check and never calls
    `ShowBattleMessage` at all -- so `0x17`'s paralysis announcement is
    silent (VFX only), while `0x16`'s is announced with text. `0x17`
    also rolls its own `Mt19937ChanceNoisy(operand 3)` chance *before*
    even calling `FUN_0801b430`, entirely separate from the
    `g_wEffectContextValue` gate inside it *and* separate from the
    per-turn escape-chance roll `bParalysisEscapeChance_candidate` drives
    afterward -- three independent RNG layers stacked for this one
    effect (whether the attack lands, whether paralysis takes at all,
    then whether/when the target breaks free), matching its
    monster-special-attack-only usage (Hinkypunk/Skeleton, which
    additionally gate on `special_effect_chance`, see "Monster
    special-attack effects" below).
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
  script (effect id `36`) also applies this same bit -- **now confirmed
  to genuinely not be any of Harry's 16 cards** (the real, complete
  16-entry `g_abHarryCardEffectId` table, decoded below, simply
  doesn't contain `36`), so this second source stays unattributed to any
  specific card or spell; not investigated further. **Harry's
  `Girding All`** card (index `7`, effect id `35`, "Increases all party
  members' physical defense") was the leading candidate for this bit by
  elimination, but its own script contains **no** opcode `0x97` call at
  all -- it must apply its defense boost some other way (plausibly a
  direct write to `BattleFighter+0x2E`,
  `bDefenseFactorPercent_notFromMonsterTable`, rather than the
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

**Poison Immunity, PROVEN source.** `g_abHarryCardEffectId`
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
`LAB_0801ab2a`), not a `bStatusFlags` write. Harry's **`Extra EXP`**
card (index `11` of 16 in `g_abHarryCardEffectId`, effect id
`14` -- name and mapping now PROVEN, see below) uses the same family
(case `2`, `ExtraExpBonus`, `field_0x1480 |= 1`) -- it **does**
share a mechanism with Hermione's move, just `field_0x1480` (an
unidentified `FightState` field) rather than `bStatusFlags`. A third case
in the same family, `ForceItemDrop` (case `0x1B`/`27`, `field_0x1480 |=
4`), is Ron's Wizard Cracker card (see "Ron's Special Move effect ids"
below) -- per the move's own in-game description text (string ids
`1725`/`2615` in `data/text/en_us.json`, both "...makes [the target]
drop an item"), this bit's real effect is causing the target creature to
drop an item, not a gold bonus. So `field_0x1480` is at least a 3-bit
flag byte covering three different "bonus reward on this encounter" end
effects: extra XP (two independent sources/bits), and an item drop.
**`field_0x1480` has no reader among code either tool currently
recognizes.** The three writes above (cases `2`/`3`/`0x1B`) generate the
`0x1480` offset via a `movs Rd, #imm8; lsls Rd, Rd, #shift` pair rather
than a literal-pool constant (saves a pool slot for a mid-size offset);
`0x1480` has exactly three 8-bit-immediate/shift-amount pairs that
produce it (`0xA4<<5`, `0x52<<6`, `0x29<<7`). Every occurrence of all
three immediate values in `gbadisasm`'s on-disk US disassembly was
checked (`0xA4`: 7 sites, `0x52`: 2 sites, `0x29`: 0 sites) -- the only
ones followed by a matching shift and used as a `FightState`-relative
offset are the three writes already covered above; the rest are
unrelated immediates (a different struct's `+0x148`-ish offsets, or
plain non-shifted arithmetic) at unrelated addresses. A direct `ldr Rd,
=0x1480` literal-pool load (the encoding a one-off far-away read would
more likely use) also doesn't appear. Ghidra's own auto-analysis was
checked too, with the same result. Neither result is proof of absence:
`gbadisasm`'s on-disk output only covers code reachable from the
functions currently seeded in `functions.us.cfg`, and a reader living in
still-unseeded territory (dumped as opaque bytes) wouldn't show up in
either search -- this is the same class of gap as `FightState+0x1054`/
`+0x1058` below, not a stronger claim than that one. So the in-game
item-drop behind `Wizard Cracker` (and whatever separately consumes the
two extra-XP bits) isn't confirmed to run through this byte; `case 0x1B`
merely being the one `StatusEffect` call in `Wizard Cracker`'s effect
script is the only evidence tying it to the item grant, not a traced
code path to an actual item being added to the player's inventory.
Where that inventory-add itself happens isn't located -- searching for
named or callable "add item"/"inventory"-style functions in Ghidra
turned up nothing beyond the existing, unrelated
`g_pBattleItems_candidate` catalog and its *consumption* (not granting)
functions `ConsumeBattleItemSlot`/`IsBattleItemSlotUsable`, subject to
the same seeding/auto-analysis caveat.

### `StatusEffect` sub-cases, full case-by-case writeup, PROVEN

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
  real ID, see the `bSpellId` writeup above). Reads `BattleFighter+1` (a
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
  zeroes `bPoisonDamage_candidate` and the Object's blink-flag halfword
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
  `bParalysisEscapeChance_candidate` (`BattleFighter+0x44`) to `100`
  (see the `Paralyzed` bit writeup above for what this field actually
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

`FightState.field_0x1054` (`void*`) and `field_0x1058` (`byte`) -- kept
unnamed/`field_`-prefixed rather than describing a purpose, since nothing
below actually pins one down. Found via the object-script interpreter's
opcode `0x30` (`opcode_30`, not confidently named either, see
`../formats/object_script.md`): it increments a byte at its target
`Object+0x60`, mirrors the result into `field_0x1058`, and latches the
`Object` pointer into `field_0x1054` the first time it's called (guarded on
that field being `0`). `TickFighterAttackAnimState_candidate` (`0x08015608`)
reads and branches on the same `Object+0x60` byte as a small state value
(checked against `1`/`2`/`4`) to steer attack-outcome handling, and zeroes
`Object+0x60` together with both `FightState` fields once an attack
sequence fully resolves.

Every other site touching `+0x1054`/`+0x1058` (found by searching the ROM
for their two literal-pool constants, `0x1054`/`0x1058`, and checking each
hit) is the same reset-to-zero pattern, at a different start/end-of-attack
transition point: `TriggerBattleEffect` (`0x08018B70`, right after it spawns
the effect script object), `ShowItemUseResult` (`0x08015F50`, on entry), and
several state transitions inside the spell-resolution state machine
`FUN_080161FE` (`0x080161FE`-`0x08016E47`, the caster-side counterpart to
`TickFighterAttackAnimState_candidate`). None of these sites, nor any other
found this way, reads `field_0x1058`'s accumulated value or `field_0x1054`'s
latched pointer for anything -- every occurrence is either `opcode_30`'s own
increment/latch or one of these resets. Both fields appear to be write-only:
tracked by the script interpreter and reset at attack boundaries, but with
no confirmed consumer anywhere in the disassembly, so no known in-game
effect. This is a search over every occurrence of the two literal constants,
not a proof that no reader exists by some other addressing path.

### Harry's 16 Folio Universitas cards, PROVEN

Found via the game's own **Card Combo Glossary** text
(`data/text/en_us.json`, decoded per `../formats/text.md`): string ids
`1144`-`1159` are a 16-entry list of card-combo *names*, immediately
followed by a matching 16-entry list of short *descriptions* at
`1160`-`1175` -- both lists line up positionally, 1:1, with
`g_abHarryCardEffectId`'s 16 real table entries (read directly
from ROM at `0x080514c8`):

| Index | Effect id | Card name | Description (in-game) |
|---|---|---|---|
| 0 | 15 | `Horklump Spores` | Horklump spores appear and blast opponent with pollen. |
| 1 | 5 | `Tempest Jinx` | Causes a gust of wind to blow one opponent off-screen. |
| 2 | 10 | `Cracker Jinx` | Causes Wizard Crackers to go off and give heavy damage to all opponents and some damage to player's party. |
| 3 | 42 | `Poison Antidote` | Removes any poison affecting a party member. |
| 4 | 52 | `Remove Jinx` | Removes any jinx affecting a party member. |
| 5 | 18 | `Poison Immunity` | Gives all party members immunity to poison for one magical encounter. |
| 6 | 37 | `Revive` | Revive an unconscious member of your party. |
| 7 | 35 | `Girding All` | Increases all party members' physical defense. |
| 8 | 53 | `Reparifors` | Cancels any magical ailments affecting the party. |
| 9 | 48 | `Replenish MP` | Sets a party member's Magic Points (MP) to maximum. |
| 10 | 40 | `Replenish SP` | Sets all party members' Stamina Points (SP) to maximum. |
| 11 | 14 | `Extra EXP` | Gain bonus Experience (EXP) Points after successfully completing a magical encounter. |
| 12 | 41 | `Bludgers` | Causes Bludgers to rain down on opponent for low damage. |
| 13 | 47 | `Snitch` | Snitch flies around opponent's head, distracting them. Opponent loses a turn. |
| 14 | 39 | `Sonorous Charm` | Creates a magnified roar that disrupts all in its path. |
| 15 | 43 | `Ultimate MP` | Selected party member gains all spell abilities. |

Confidence: **PROVEN** for the index<->effect-id<->name correspondence
as a whole -- three of these (index `5`/`Poison Immunity`, index
`11`/`Extra EXP`, index `13`/`Snitch`) were already independently
confirmed by this doc through opcode-content tracing alone, *before*
the glossary text was consulted, and all three land on the exact same
slot the glossary gives them; that three-way agreement is what makes
the positional correspondence trustworthy for the other 13 cards too,
not just an assumption. Each script's content was additionally spot-
checked against its description (e.g. `Poison Antidote`/`Remove Jinx`
both call the not-yet-named opcode `0x97` cases `0xF`/`0x14`
respectively on a single target, matching "a party member" in both
descriptions; `Reparifors` calls case `0x14` three times, matching
"the party" plural). The one exception is **`Girding All`** (index `7`),
whose script has no `StatusEffect` opcode at all -- see the `DefenseBoost`
bit writeup above; its mapping to effect id `35` is solid (by position
and elimination) but its actual defense-boost mechanism is not.

All 16 are now named in `tools/objscript/script_names.json` as
`SpecialHarry<CardName>` (matching the `SpecialHermione*`/`SpecialRon*`
convention already used for the other two characters' Special Moves),
e.g. `SpecialHarryHorklumpSpores`, `SpecialHarrySnitch`,
`SpecialHarryUltimateMp`. See `../formats/object_script.md`'s Future
Work section (now marked done) for the prior open questions this
resolved.

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
effect-id tables (`g_abSpellEffectId_candidate` for the 10 real `SpellId`
values,
`g_abHermioneLectureEffectId_candidate` for Hermione's 3 moves,
`g_abHarryCardEffectId` for Harry's 16 cards) then map a
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
  exactly this path (see the dialog-text table below).
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
below -- **not** monster-AI-specific despite this doc's earlier guess;
it dispatches *any* active fighter's turn, player or monster) already
reads as "whose turn it is" -- two independent call sites agreeing is
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
        g_nXpAccum += MonsterTable[f->bRosterIndex].reward_xp;
        g_nGoldAccum += MonsterTable[f->bRosterIndex].reward_gold;

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
"Ron's Special Move effect ids" below. The source of this particular
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

## Corrections to `../formats/folio_bruti.md`

The formulas above directly read several `BattleFighter` fields that
`../formats/folio_bruti.md` had labeled from `MonsterTable` content shape
and (weak, self-described-as-a-guess) player memory of one boss fight, not
from a traced reader. Now that a real reader exists, those labels are
corrected:

- `MonsterTable+0x04` (`BattleFighter+0x2B`): relabel **`accuracy`**,
  PROVEN (see "Attack resolution" below).
- `MonsterTable+0x03` (`BattleFighter+0x2A`): relabel **`bStat_speed`**,
  PROVEN -- see "Turn order" above.
- `MonsterTable+0x02` (`BattleFighter+0xE`, `bLevel`): see the
  `BattleFighter+0xE` section above -- the field is a confirmed level
  counter for player-sourced values, but a monster's own value here has
  no confirmed reader.
- `MonsterTable+0x06`/`+0x08` (`BattleFighter+0x30`/`+0x32`): **not**
  "level-range min/max" -- relabel **`damage_min`/`damage_max`**, PROVEN
  (fed directly into the damage roll). The old "monotonic with tier"
  evidence for a level-range reading is equally consistent with a
  damage-range reading, so this isn't a contradiction, just a correction
  now that a real reader settles it.
- `MonsterTable+0x05` (`BattleFighter+0x2C`): relabel **`bCritChance`**,
  PROVEN -- bonus-damage roll threshold gating the confirmed "Critical
  hit!" message path.

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
with "Ron's Special Move effect ids" below, which resolves this
independently via the effect scripts' own `StatusEffect` content, once
this table's real meaning is traced.

The other case targets (`0x080160FC`, `0x08017A7C`, `0x080161A2`,
`0x08017ADE`, `0x0801618A`, `0x080161FE`) haven't been walked yet.

### The top-level battle menu, PROVEN via `data/text/en_us.json`

Decoding the dialog string table directly (see `../formats/text.md`)
finds the real, un-truncated top-level battle menu labels as consecutive
string ids `2288`-`2293`: **`Cast Spell`, `Special Move`, `Use Item`,
`Flee`, `Folio Bruti`, `Help`**, with `Informus` (string id `2400`, also
`2755`) a separate top-level entry not adjacent to this block.
`Informus`'s own trigger/effect path -- `SpellId` `1` is `Informus`'s own
real ID (this string, `2400`, is exactly `spellId + 0x95F`'s formula for
`SpellId` `1`, see the `bSpellId` writeup below), and its own effect
script (id `38`)'s `StatusEffect` case `0xC` (`BumpMonsterDocLevel`) is
the actual Folio Bruti write -- see "`DispatchPendingAction`... and the
answer to 'does Informus have a script?'" below for the full trace.
String ids
`2298`-`2300` (`Be More Careful`, `Good Study Habits`, `Proper Wand
Technique`) exactly match Hermione's three named lecture scripts
word-for-word, independently confirming that identification;
`2301`-`2303` (`Stink Pellet`, `Wizard Cracker`, `Stink Pellet 2`) are
Ron's three Special Move item names -- see above for their unconfirmed
effect-id mapping.

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
which for a normal spell cast leaves `bPendingActionKind_candidate ==
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

### `BattleFighter+0xE` (`bLevel`) -- PROVEN as a field, UNCONFIRMED for `MonsterTable+0x02`

`ResolveSpellAttack` reads `attacker->bLevel` (offset `0xE`) twice:
once as the term multiplying `g_awSpellPowerScale[idx]` (divided by 9)
into the spell's base power, and once (independently, `>>1` capped at
12) as the spell crit-chance scale.

`attackerIndex` in `ResolveSpellAttack` is only ever a *player* fighter.
`InitMonsterBattleActor` hardwires every monster `Object`'s `pfnTick` to
`TickFighterAttackAnimState_candidate` (the melee-only dispatcher, see
"Turn order" above and its own section below) -- a monster's `Object`
never ticks through `TickPlayerActionState_candidate`, so a monster
never becomes `ResolveSpellAttack`'s attacker. `ResolveMeleeAttack`
(the formula monsters do use) doesn't read `bLevel` at all. So
`MonsterTable+0x02`'s value has no confirmed reader in either formula,
even though the same struct offset is confirmed as the fighter's level
for player-sourced values.

**`bLevel` is a level counter, PROVEN.** `LevelUpFighter_candidate`
(`0x080151B0`) increments a party member's `bLevel` by 1 (capped at
`99`) and uses the new value to index a per-character, per-level stat
table (`g_pHarryLevelTable_candidate`/`g_pHermioneLevelTable_candidate`/
`g_pRonLevelTable_candidate`, `CharacterLevelEntry_candidate[100]`,
12-byte rows: `wHp_max`, `wMp_max`, `wXpToNextLevel_candidate`,
`bStat_speed`, `bAccuracy`, `bDefenseFactorPercent_candidate`,
`bUnk_0x09`), writing the row's values into the matching
`BattleFighter` fields, then full-healing HP/MP and calling
`ApplyEquipmentStatModifiers_candidate` (`0x08026870`) to reapply gear
bonuses on top. `RecomputeBaseStatsFromLevel_candidate` (`0x080150B4`)
does the same table lookup for `bStat_speed`/defense without
incrementing the level, used when only reapplying equipment (resets
defense/`bUnk_0x2F` to `100`, i.e. unmodified, first).
`ApplyEquipmentStatModifiers_candidate` walks each of the 3 party
members' 6 equipped-item slots (`DAT_03003834`) and subtracts each
item's `nType/2` from defense%, `dwUnk0C` from `bUnk_0x2F`, and
`nParam` from `bStat_speed` (clamped) -- heavier gear trading speed for
defense. `ApplyPendingLevelUps_candidate` (`0x0801D308`) calls
`LevelUpFighter_candidate` for all 3 party members together, `N` times.

**Verified against real in-game data** (Harry Lvl7, Hermione Lvl8, Ron
Lvl5, all no equipment): `bLevel` is 0-indexed (Level `N` = table row
`N-1`). `wHp_max`/`wMp_max` match the row directly. Displayed agility =
`255 - bStat_speed` (the turn-order byte and displayed agility are
inverses). Displayed defense/magic-def are always `0` (`100 - 100`, not
the row's own value) because `RecomputeBaseStatsFromLevel_candidate`
resets both to `100` immediately after `LevelUpFighter_candidate` sets
them from the table -- so those two table columns never actually take
effect. Displayed next-level XP is the sum of
`wXpDeltaForLevel_candidate` across rows `0..bLevel`, not any single
row's value and not what `LevelUpFighter_candidate` itself writes into
`wRewardXp` (a plain overwrite with just the new row's delta) -- whatever
compares real XP against this cumulative threshold isn't located yet.

**Player fighters get `bLevel` from `g_pPartyMasterStats_candidate`
(`0x030024EC`), not `MonsterTable`.** `InitPlayerBattleActor_candidate`
(`0x080149C4`, the player-fighter counterpart to
`InitMonsterBattleActor`, called from `SetupBattleRoster_candidate`)
copies a persistent, `BattleFighter`-shaped 3-entry array (one per
Harry/Hermione/Ron) into the live roster, field-for-field at matching
offsets: `bLevel` (`+0xE`), `wHp`/`wHp_max` (`+8`/`+0x24`),
`wMp`/`wMp_max` (`+0xA`/`+0x26`), `bStat_speed` (`+0x2A`), `bAccuracy`
(`+0x2B`), and **`bDefenseFactorPercent_notFromMonsterTable`
(`+0x2E`)** -- resolving that field's origin (see `ResolveMeleeAttack`
above): it's a player-only stat, never populated for monsters.
Buckbeak (`fighterType==3`, outside the 3-entry array) gets hardcoded
defaults instead (`wHp`/`wMp_max`=400/999, `bLevel`=0x32,
`bStat_speed`=10, `bAccuracy`=0x65, `bDefenseFactorPercent`=100).

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

**`Informus` is `SpellId` `1` in its own right, not a "borrowed"
`Spongify` slot -- correction to this doc's own earlier framing.**
`Informus`'s top-level menu action (see "the answer to 'does Informus
have a script?'" below) sets `bSpellId = 1`, which really is `Informus`'s
own real ID. **`Spongify` is `SpellId` `9`** -- previously assumed to be
`1`, and previously the source of `g_abSpellIdByCursor`'s Ron row
(`[0,2,4,6,9,5,0]`) showing an "unexplained `9`"; that `9` is real and is
exactly `Spongify` (matches `data/text/en_us.json` string `937`: "Harry
receives Diffindo, Ron receives Spongify, and Hermione receives
Glacius!" -- `Spongify` is Ron's spell). `ResolveSpellAttack`'s own
`aSpellEffectiveness` switch has no case for **four** values, not two:
`1`/`6`/`8`/`9` (`Informus`, `PetrificusTotalus`, `Fumos`, `Spongify`) --
all four are non-damage/status spells (documentation, paralysis, evasion,
attack-weaken respectively), none compute a per-monster effectiveness
roll. `PetrificusTotalus=6` is independently PROVEN via `g_awSpellMpCost`
below; `folio_bruti.md`'s "always 100% effective" pair (Petrificus
Totalus, Spongify) is that screen's own separate spell-index list (0-7,
excluding `Informus`/`Fumos` entirely, since neither has a monster
resistance stat to display) -- not the same ordering as `SpellId`, don't
conflate the two.

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
`g_abSpellEffectId_candidate` (`0x080538B0`), is a per-`(spellId,level)`
animation/VFX id fed into `FUN_08018b70` (the same anim-trigger function
used throughout this code) -- not a resource-type selector.

**All 30 entries read and named** (`tools/objscript/script_names.json`):
`[2,3,21, 38,38,38, 19,20,26, 22,22,22, 23,24,25, 28,28,28, 33,34,33,
30,31,30, 11,32,32, 29,29,29]`, confirming the spellId row order above
(`Informus`'s `[38,38,38]`, `PetrificusTotalus`'s `[33,34,33]`, and
`Spongify`'s new `[29,29,29]` row all land exactly where expected). The
table is 10 rows (`spellId` `0`-`9`) -- the last two rows, `[11,32,32]`
and `[29,29,29]`, are `Fumos` (`SpellFumosUno`/`SpellFumosDuo`, `spellId`
`8`; see the `Hidden` status bullet above) and `Spongify`
(`data/scripts/SpellSpongify.txt`, effect id `29`, `spellId` `9`; see the
`AttackWeakened` bit-`0x08` writeup above) respectively.
`g_awSpellMpCost` (the parallel MP-cost array documented just above) is
likewise 30 `ushort` entries; `Fumos`'s row is `[8,30,0]` -- an MP cost
for `Uno`/`Duo` and an unused `0` for the `Tria` slot it never reaches.
None of the 13 remaining scripts described below (`SpellFlipendoUno`/
`Duo`/`Tria`, `SpellVerdimilliousUno`/`Duo`/`Tria`, `SpellDiffindo`,
`SpellIncendioUno`/`Duo`/`Tria`, `SpellWingardiumLeviosa`,
`SpellGlaciusUno`/`Duo`) contain a `StatusEffect` (`0x97`) instruction --
checked directly against the extracted script text -- so unlike
`PetrificusTotalus`, `Fumos`, `Informus`, and `Spongify` (all four of
which do), these are purely cast-animation triggers; their actual
damage is computed separately by
`ResolveSpellAttack` above, not by this bytecode. `Flipendo`/
`Verdimillious`/`Incendio` have three genuinely distinct scripts (one per
cast level) -- real evidence that a spell's `Uno`/`Duo`/`Tria` levels
*can* each carry distinct content, which is what makes
`PetrificusTotalus`/`Glacius` reusing the same script for `Uno` and `Tria`
notable rather than just "the table only has two real values."
`Diffindo`/`WingardiumLeviosa` use one shared script for all three
levels, like `Informus` and `Spongify` -- **explained**: `Informus`/
`Diffindo`/`WingardiumLeviosa` (`SpellId` `1`/`3`/`5`) have
`g_abSpellMaxLevel == 1` (see below), meaning none of them can ever level
past `Uno` in the first place, so a Duo/Tria-specific script would be
genuinely unreachable content -- the engine simply doesn't need one.
`Spongify` fits the same pattern via its `g_abSpellMaxLevel` alias (see
below). `Fumos` also fits (`Duo` and `Tria` share effect id `32`), and
does have a real dedicated entry (`g_abSpellMaxLevel[8] == 2`, see
below) despite capping at `2` rather than `1` -- its `Tria` slot is
simply unreachable for the same "never levels that far" reason, one
level later than the `== 1` group.

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

**`SpellProgressBlock`** (26 bytes) is a standalone struct typed only for
this function's 4th parameter -- it is *not* embedded into `BattleFighter`
itself (that would force every other already-reviewed function's
`fighter->wHp` into a longer field-access chain for no benefit). Its
fields are `BattleFighter`'s own `wHp`/`wMp`/`bLevel`/`bUnk_0x0F`
followed by two previously-unmapped embedded 8-entry (one per `SpellId`)
byte arrays discovered here, now also added directly to `BattleFighter`
itself at their real offsets: **`aSpellCastLevel`** (`+0x10`, the
fighter's current mastered level *per spell*, distinct from `bSpellLevel`
which is the level chosen for *this turn's* cast) and
**`aSpellUsageProgress`** (`+0x1A`, progress toward that spell's next
level-up). The call site passes `(SpellProgressBlock *)&fighter->wHp`,
i.e. `BattleFighter+8` -- confirmed bounded on both sides: it starts
exactly at `wHp` and its last field ends two bytes before `wHp_max`
(`+0x24`), with `g_abPartySpellUsage`/`g_abPartySpellLevel`'s call-site
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
  for `Flipendo, Informus, Verdimillious, Diffindo, Incendio,
  WingardiumLeviosa, PetrificusTotalus, Glacius, Fumos`. This is the real,
  data-driven answer to two things this doc previously only inferred from
  script content: `Informus`/`Diffindo`/`WingardiumLeviosa` (max `1`) can
  never level past `Uno`, and `PetrificusTotalus`/`Glacius` (max `2`) can
  never reach `Tria` -- both now cross-checked against, and matching,
  those spells' script-sharing patterns above. The table has room for
  exactly 9 entries (`SpellId` `0`-`8`) before `g_abSpellLevelUpThreshold`
  starts -- `Spongify` (`SpellId` `9`) has no entry of its own;
  `TrackSpellFamiliarity`'s `g_abSpellMaxLevel[9]` read for it actually
  lands on `g_abSpellLevelUpThreshold[0]` (`1`), one byte past the real
  table. That aliased value happens to be `1` -- the same cap `Spongify`'s
  own single-level MP-cost shape (`10/0/0`, matching `Diffindo`'s) implies
  it should have -- so this reads as harmless in practice, but it is a
  genuine out-of-declared-bounds read, not a real dedicated entry.
- **`g_abSpellLevelUpThreshold[3]`**: `[1, 25, 50]`, indexed by the
  spell's *current* level. Leveling `Uno`->`Duo` takes just 1 use;
  `Duo`->`Tria` takes a real 25. The third entry (`50`) is normally
  unreachable, since `g_abSpellMaxLevel` gates the level-up check before
  a maxed-out spell's usage counter can ever reach it -- not traced
  further, flagged as likely-dead data rather than assumed meaningful.

Also confirms `fighterType != Buckbeak` is an explicit, dedicated gate
here (Buckbeak doesn't cast spells, so never tracks familiarity), not an
incidental side effect of some other check.

### `DispatchPendingAction` (`0x080100a0`), PROVEN -- and the answer to "does Informus have a script?"

Reads `BattleFighter.bPendingActionKind_candidate` (`+0x3b`, enum `PendingActionKind_candidate`:
`None=0, UseItem=1, SpecialMove=2, Flee=3, Informus=4`, written by the
menu confirm handlers documented above) for the active fighter and starts
the corresponding animation state on that fighter's `Object`:

```c
void DispatchPendingAction(void)
{
  BattleFighter *fighter = g_pFightState->pFighters + g_pFightState->bActiveFighterIndex;
  switch (fighter->bPendingActionKind_candidate) {
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
  `OpenBattleTopMenu`'s graying check documented above -- using a Special
  Move once is literally what un-grays that menu entry for later turns).
  A regular `Cast Spell` selection leaves `bPendingActionKind_candidate` at `None`.
  For Harry specifically, `bSpellId` gets overwritten with
  `g_nFolioUniversitasSlot` (the raw Folio Universitas card
  slot, `0`-`15`) purely so the announce message can index by it --
  `g_nFolioUniversitasSlot` is **not** itself a `SpellId`
  despite the cast shown here (real `SpellId` values only go up to `9`,
  see the `bSpellId` writeup above; card slots go to `15`, well past
  that) -- a similar field-reuse trick to how `HandleScriptedDamageEvent_candidate`
  reads this same overloaded `bSpellId` for display purposes elsewhere in
  this doc, just for indexing rather than triggering an effect.
- **`Informus`'s dispatch.** It is given *no* special-case branch here at
  all -- it shares the `None` case outright, driving the exact same anim
  state (`0x1a`, `HandleScriptedDamageEvent_candidate`'s state) and the
  exact same `TrackSpellFamiliarity` call a completely ordinary spell
  cast would. That's expected, not a repurposing: `Informus` **is** a
  real, dedicated `SpellId` (`1`, see the `bSpellId` writeup above, PROVEN
  via the Cast Spell menu's own `spellId + 0x95F` name-lookup formula),
  so `Informus`'s menu confirm handler (`ConfirmBattleTopMenu` case 2,
  documented above) setting `bSpellId = 1` is just setting `Informus`'s
  own ID, the same way any other menu screen sets `bSpellId` to the
  spell it selected -- not a "borrow a harmless slot" trick. Its effect
  script is `g_abSpellEffectId_candidate[1]` = effect id `38`
  (`data/scripts/SpellInformus.txt`), whose one real gameplay opcode,
  `StatusEffect` case `0xC` (`BumpMonsterDocLevel`, see the sub-cases
  writeup above), **is** the Folio Bruti populate action -- matching
  `Informus`'s own in-game description ("Cast upon a creature to learn
  about its strengths and weaknesses", string id `1494`) exactly. It
  still has zero base power (`g_awSpellPowerBase[1] == 0` at every
  level) and costs `0` MP, so it deals no damage and needs no resource --
  both real properties of `Informus`'s own row in those tables, not
  inherited from `Spongify`.

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

## The battle menu itself -- PROVEN

Found by walking backward from the top-level menu label table (see below),
not from `GetDialogText`'s callers directly (170+ call sites, mostly
unrelated dialog text elsewhere in the ROM -- not a practical starting
point on its own). The real entry point was a byte-pattern search for the
raw bytes of `0x8f0` (`2288`, `Cast Spell`'s string id) as 32-bit literal
data, which landed on a 7-entry table at `0x0804d808` referenced from
`FUN_08011520` -- the menu's own label-drawing function.

### Menu/UI state machine, `FightState` fields

- **`field_0x1070`** (u8): which menu *screen* is currently active. Values
  found: `1` = top-level 7-item menu, `2` = per-character spell list
  (`Cast Spell`), `4` = 3-item Special Move/Lecture list (Hermione's 3
  lectures and Ron's 3 moves share this one screen), `5` = spell
  cast-level list (Uno/Duo/Tria, inferred from `FUN_080101d0`'s case 5
  reading `pBVar6->aSpellEffectiveness[bSpellId-0x24]` as an item count,
  not walked further), `6` = target-select/confirm screen, `7` = item
  list, `8`/`9` = further submenus (not walked). `0` = no menu open.
- **`field_0x147c`** (u8): the current menu cursor index within whichever
  screen `field_0x1070` selects.
- Both consumed by **`FUN_08011520`** (`0x08011520`), called after every
  cursor move: draws the currently-highlighted entry's label (and, for
  the spell-level screen, its MP cost) via `GetDialogText`/`DrawTextLines`
  -- this is the menu's own label-draw routine, not a generic dialog
  drawer.

### Top-level menu, PROVEN

**`0x0804d808`**, a 7-entry `int32[7]` table of dialog-text ids, read as
`table[field_0x147c]` by `FUN_08011520`'s `field_0x1070==1` case:

```
[0x8f0, 0x8f1, 0x960, 0x8f2, 0x8f3, 0x8f4, 0x8f5]
= [2288, 2289, 2400, 2290, 2291, 2292, 2293]
= [Cast Spell, Special Move, Informus, Use Item, Flee, Folio Bruti, Help]
```

This directly settles where `Informus` (string id `2400`, not adjacent to
the `2288`-`2293` block in the *string table*) actually sits in the *menu
order*: index `2`, between `Special Move` and `Use Item` -- exactly the
order the user-facing glossary lists it in. All 7 items the user asked
about are accounted for by this one table.

**`FUN_080104a0`** (`OpenBattleMenu_candidate`, `0x080104a0`) opens this
screen for a given fighter: sets `field_0x1070=1`, builds a local 7-entry
enabled/grayed array (all `1` by default), then:

- grays index `1` (`Special Move`) if the active fighter is Hermione with
  `field_0x148c==0` or Ron with `field_0x1488==0` -- these two fields are
  the natural "lectures known" / "special moves known" counts (not
  independently confirmed by name, but exactly gate the one menu item
  that needs at least one unlocked move to be usable).
- grays index `2` (`Informus`) **and** index `4` (`Flee`) together, in the
  same branch, when `DAT_03003f24 == 0xff` -- matching the user's
  "Informus/Flee grayed out for bosses" fact exactly; `DAT_03003f24` is
  the natural "is this a boss fight" flag/index candidate (not
  independently named further here).

**`FUN_08011bec`** (`0x08011bec`) is the confirm (A-button) handler for
this screen, `switch(field_0x147c)` with 7 cases matching the table above
1:1:

- **case 0, Cast Spell**: `field_0x1070 = 2` (spell-list screen), then
  builds the list via `FUN_08011abc(1, i, fighterType, 1)` for
  `i` in `[0, pFighter->bUnk_0x0F)` -- **`bUnk_0x0F` is the fighter's
  known-spell count**, directly confirming "only unlocked spells for that
  character" from the task description.
- **case 1, Special Move**: if the active fighter is Harry, saves the
  current mode-stack context and pushes game mode `0x26` via
  `FUN_0802c7e0(0x26, 1, 0)` -- **this is the Folio Universitas**,
  matching `DAT_03003f3c == 0x26` already read by `FUN_0800f5f0` earlier
  in this doc (that function consumes the *result* of a completed card
  selection, not the menu itself -- the two findings now connect).
  Otherwise (Hermione/Ron) calls **`FUN_080105d8`** (see below) -- one
  shared 3-item-list screen for both, not per-character screens.
- **case 2, Informus**: gated by `DAT_03003f00 != 0xff` (a second,
  independent boss-style check from the graying check above -- same
  "boss" concept, different flag/slot). Sets the active fighter's
  `bSelectedActionIndex=0`, **`bSpellId=1`** (`Informus`'s own real
  `SpellId`, see the `bSpellId` writeup above -- not borrowed from
  `Spongify`), `field_0x3b=4`, `bSpellLevel=0`, then `field_0x1070=6`
  (the same target-select screen spellcasting uses). `field_0x3b` is
  `BattleFighter+0x3B`, i.e. **`bPendingActionKind_candidate`** itself
  (`None`=`0`/`UseItem`=`1`/`SpecialMove`=`2`/`Flee`=`3`/`Informus`=`4`)
  -- the same field `DispatchPendingAction`'s top-level switch reads --
  so `field_0x3b=4` is simply this menu tagging the pending action as
  `Informus`, exactly like `Flee`/`UseItem`/`SpecialMove` each tag their
  own screens; a regular `Cast Spell` selection leaves it at `None` (`0`)
  instead (see `field_0x1070==2` above). There is no `Spongify`-borrowing
  or cast-disambiguation happening here at all -- `Informus` is a
  first-class pending-action kind with its own real `SpellId`.
- **case 3, Use Item**: `field_0x1070 = 7` (item-list screen), calls
  `FUN_08010660` to build the list.
- **case 4, Flee**: gated by `DAT_03003f24 != 0xff` (the same flag
  `FUN_080104a0` already used to gray this entry -- re-checked here
  too), sets `field_0x1070=0` (closes the menu) and `field_0x3b=3`.
- **case 5, Folio Bruti**: calls `FUN_0802c7c4(0x2d)` -- a mode-push,
  presumably to the Folio Bruti screen (not walked further here; see
  `../formats/folio_bruti.md`).
- **case 6, Help**: saves mode-stack context and pushes game mode `0x44`
  via `FUN_0802c800(0x44, ...)` -- matches `DAT_03003f3c == 0x44`, the
  other mode value `FUN_0800f5f0` branches on, consistent with "opens a
  menu similar to the pause menu" from the user's description (not
  walked further).

Cursor movement and A/B dispatch both live in **`FUN_080101d0`**
(`0x080101d0`): reads a button-state bitmask `DAT_030034f0` (`0x10`=Down,
`0x20`=Up move the cursor by +-1 with wraparound via `FUN_08012e38`;
`0x01`=A/confirm, `0x02`=B/cancel dispatch through two 11-entry function-
pointer tables indexed by `field_0x1070`: confirm table at `0x0804e2ec`,
cancel table at `0x0804e318`). `field_0x1070`'s per-screen confirm
handlers: `1`->`0x08011bec` (above), `2`->`0x08012e54`, `4`->`0x08011eb8`
(below), `5`->`0x08011fa0`, `6`->`0x080120ec`, `7`->`0x08012eac`,
`8`->`0x08012178`, `9`->`0x0801320c` (all now walked below except `9`,
which has no function defined at that address at all -- `field_0x1070`
is never observed being set to `9` anywhere in this whole tree, so this
slot looks unreachable/dead from battle, not a tracing gap).

### The rest of the menu tree, PROVEN, and where the effect calls actually live

Walking every remaining `field_0x1070` confirm handler completes the
picture -- and the headline result is structural: **none of the menu's
own confirm handlers call the effect-trigger function
(`FUN_08018b70`) directly.** Every screen in this tree does the same
thing: write a handful of `BattleFighter` fields (`bSpellId`,
`bSpellLevel`, `bSelectedActionIndex`, `field_0x3b`, `bSlotParam`) and
set `field_0x1070 = 0` to close the menu. The actual effect calls all
happen afterward, in the object-tick execution layer this doc already
covers in depth (`TickPlayerActionState_candidate`'s case `0x1a` =
`HandleScriptedDamageEvent_candidate`, and its `0x40000`/`0x8000`
`Object+0xc` flag branches) -- the menu and the effect system are fully
decoupled through these struct fields, confirming the split this doc
warned about at the top (menu-construction vs. action-execution are
genuinely two separate layers, not just two ends of one function).

- **`field_0x1070==2`** (`FUN_08012e54`, confirm handler for the
  per-character spell list opened by `Cast Spell`): `bSpellId =
  g_abSpellIdByCursor[fighterType*7 + cursor]` -- **`g_abSpellIdByCursor`
  (`0x0804e084`, named this session, previously `DAT_0804e084`) is a
  per-character cursor-position -> real `SpellId` remap table** (already
  independently referenced by `FUN_08011520`'s label-draw code for this
  same screen), needed because not every character's spell list shows
  the same `SpellId`s in the same menu order/count -- Harry's row is
  `[0,2,4,6,3,5,0]`, Ron's is `[0,2,4,6,9,5,0]`, and **Hermione's row,
  `[0,2,4,8,6,7,5]`, is the only one containing `8`** (cursor `3`): this
  is the actual `Fumos`-is-Hermione-only mechanism, confirmed at the
  menu-selection level rather than inferred from spell content alone.
  Ron's row is the only one containing `9` (cursor `4`) -- this is the
  actual `Spongify`-is-Ron-only mechanism (see the `bSpellId` writeup
  above), matching `data/text/en_us.json` string `937`: "Harry receives
  Diffindo, Ron receives Spongify, and Hermione receives Glacius!".
  `bSpellLevel=0`, `bPendingActionKind_candidate=None` (`field_0x3b=0`). Then
  `FUN_080106ec(fighterIdx, cursor)` builds the next screen's list before
  an (unrecovered, but structurally `field_0x1070=5`) jump.
- **`field_0x1070==5`** (`FUN_08011fa0`, spell cast-level list --
  Uno/Duo/Tria): confirms the **spell cast-level list from the task
  description** and gates it on affordability --
  `fighter.wSp < g_awSpellMpCost[spellId*3+cursor]` beeps/refuses (SP,
  not MP, despite the field name -- consistent with `ShowBattleMessage`'s
  `SpCost`/`MpCost` case split elsewhere in this doc). Also refuses
  casting `Spongify` (`bSpellId==1`) while `DAT_03003f24==0xff` (the same
  boss-flag candidate used to gray `Informus`/`Flee`) -- **a boss fight
  blocks Spongify specifically**, a new, concrete behavioral fact. Sets
  `bSpellLevel = cursor`; most spell/level combinations proceed to a
  target-select screen (`field_0x1070=6`), except a few that execute
  immediately with `bSelectedActionIndex=0xfe` (self/no-target): `Fumos`
  (`bSpellId==8`) at level-1 (`Duo`, its party-wide cast, effect id `32`
  -- see the `Hidden` status bullet above), `bSpellId==6`
  (`PetrificusTotalus`) + level-1, and (generically) any spell's level-2
  (`Tria`) cast **except `Glacius`** (`bSpellId==4`) -- i.e. by default a
  `Tria` cast doesn't need a target, with `Glacius` special-cased back
  into needing one. Not fully explained; flagged rather than
  over-interpreted.
- **`field_0x1070==6`** (`FUN_080120ec`, the enemy target-select
  confirm): after a vsync wait and some UI cleanup calls, simply writes
  `bSelectedActionIndex = cursor` and `field_0x1070 = 0`. Reads
  `field_0x1059` elsewhere in this doc's other target-select code
  (`g_pFightState->field_0x1059`, an array already used as an
  enemy-roster-index list by `ResolveSpellAttack`'s callers) --
  **this screen targets enemies.** Used by: `Informus`, Ron's `Stink
  Pellet`/`Wizard Cracker`, the spell target-select path above, and
  Hermione's non-self lectures.
- **`field_0x1070==7`** (`FUN_08012eac`, item-list confirm): checks
  `FUN_08026f34(cursor)` (item usable/available -- refuses with a beep if
  not), then `field_0x3b=1`, `bSpellLevel = cursor + 0x38` (matches
  `FUN_08011520`'s item-name text lookup, `FUN_08026b8c(cursor+0x38)`) --
  **items are addressed by the same `bSpellLevel` field spell levels
  use, offset by `0x38`** into `g_pBattleItems_candidate` (the 78-entry
  item database documented above). Then calls `FUN_080107bc` (below) to
  pick a target.
- **`FUN_080107bc`** (`0x080107bc`), the shared **ally**-target-select
  *opener*: sets `field_0x1070 = 8` and reads `field_0x105d` (a
  different array from state 6's `field_0x1059`) for its list --
  **`field_0x1070==8` targets allies, not enemies.** Called from three
  places in this tree: `Use Item` (above), Hermione's non-"Proper Wand
  Technique" lectures (`Be More Careful`, `Good Study Habits` --
  consistent with them needing an ally target rather than an enemy), and
  the `bSpellId==8` special case inside the spell-level confirm above.
- **`field_0x1070==8`** (`FUN_08012178`, the ally target-select
  confirm): same shape as state 6's confirm -- vsync wait, writes
  `bSelectedActionIndex = cursor`, `field_0x1070 = 0` -- plus, if
  `field_0x3b==1` (the `Use Item` marker set above), calls
  `FUN_08026e2c(itemIndex, 1)` (presumably consumes/decrements the used
  item; not traced further).

`Use Item`'s actual effect resolution happens later, in
`TickPlayerActionState_candidate`'s `Object+0x60` sub-state `2`
(`FUN_08015f50`, `0x08015f50`): it only formats and shows the
already-computed damage/heal number (`DAT_0300274a`) via
`ShowBattleMessage`/`ShowFloatingDamageNumber_candidate` -- **it does not itself call
`FUN_08018b70` or compute an item's effect**, so an item's actual
gameplay effect (heal amount, stat boost, etc.) is set by something else
entirely, not walked here. This lines up with `g_pBattleItems_candidate`'s
`dwType`/`dwParam` fields still being undecoded (noted above) -- item
effects plausibly come from there rather than from the
`g_apEffectScripts_candidate`/opcode-`0x97` system spells and Special
Moves use.

### Special Move submenu (Hermione's 3 Lectures / Ron's 3 Special Moves), PROVEN

**`FUN_080105d8`** (`0x080105d8`) is the shared opener for both
characters' 3-item Special Move list: sets `field_0x1070=4`, builds
exactly 3 entries via `FUN_08011abc(3, i, fighterType, 1)` for `i` in
`0..2`. `FUN_08011520`'s `field_0x1070==4` case picks the label text base
by fighter type -- `fighterType==Hermione`: `textId = cursor + 0x8fa`
(`2298`-`2300`, already known to be `Be More Careful`/`Good Study
Habits`/`Proper Wand Technique`'s *string* ids in that order, per the
`g_abHermioneLectureEffectId_candidate` table elsewhere in this doc);
else (Ron): `textId = cursor + 0x8fd` (`2301`-`2303`, i.e. **cursor 0 =
Stink Pellet, cursor 1 = Wizard Cracker, cursor 2 = Stink Pellet 2**,
exactly the string-id order already on record).

**`FUN_08011eb8`** (`0x08011eb8`), this screen's confirm handler:

```c
BattleFighter *f = ...;
f->bSpellId = field_0x147c;   // the selected list index, 0-2
f->bPendingActionKind_candidate = SpecialMove;   // field_0x3b = 2
if (fighterType == Hermione) {
    if (f->bSpellId != 1)          // not "Proper Wand Technique"
        goto target_select;         // FUN_080107bc
} else /* Ron */ {
    if (f->bSpellId != 2)          // not "Stink Pellet 2"
        goto target_select;         // field_0x1070 = 6, same screen Informus uses
}
// self-cast, no target needed:
f->bSelectedActionIndex = 0xfe;
field_0x1070 = 0;                   // close menu, execute immediately
```

So **Ron's `bSpellId` is set directly from the menu cursor (0/1/2)**, the
same field spells use, and **cursor index 2 (`Stink Pellet 2`) is the one
self-cast/no-target move** -- `Stink Pellet`(0) and `Wizard Cracker`(1)
both require picking a target first.

### Ron's Special Move effect ids, resolved: `44`/`46`/`45`

`HandleScriptedDamageEvent_candidate`'s separate `Object+0xc` bit-`0x8000`
branch (already documented above as reading `DAT_0805150a[bSpellId]`
"unconditional of fighter type") is the actual trigger: since the menu
above proves `bSpellId` is set to the selected Special-Move cursor index
(0-2) for Ron exactly as it is for Hermione's lectures, and
`DAT_0805150a`'s entries `3`-`5` are already independently proven
identical to `g_abHermioneLectureEffectId_candidate` (same array, two
access paths), the natural reading of entries `0`-`2` -- previously left
unnamed pending this trace -- is now backed by the same mechanism that
resolves Hermione's:

```
DAT_0805150a = [44, 46, 45, 49, 51, 50, 41]
                0    1   2  <- Ron, indexed by his menu cursor (bSpellId)
```

i.e. **`Stink Pellet` = effect id `44`, `Wizard Cracker` = effect id
`46`, `Stink Pellet 2` = effect id `45`**.

Cross-checked against the actual extracted script content
(`data/scripts/Effect44.txt`/`Effect45.txt`/`Effect46.txt`, currently
named `Effect44`/`45`/`46` in `tools/objscript/script_names.json`):

- **Effect `44`**: a single unconditional `StatusEffect 17 0 0`
  (opcode `0x97` case `0x11`, "Paralyzed", the *unconditional*-apply
  variant per this doc's `bit 0x10` section) after a throw-style
  animation -- matches a single-target "throws a stink pellet, paralyzes
  them" move, consistent with `Stink Pellet` needing a chosen target.
- **Effect `45`**: branches on a script-local parameter
  (`GotoIfLocalANotEqual 0 50`) between the same simple throw-and-
  paralyze sequence (label `50`, structurally identical to effect `44`)
  and an extended sequence applying `StatusEffect 17 0 0` **three times**
  in a loop -- consistent with `Stink Pellet 2` being an
  enhanced/multi-target version of the same paralysis effect, and with it
  being the one move that skips target selection (the multi-apply branch
  presumably walks all enemies itself, script-side).
- **Effect `46`**: fires only one `StatusEffect`, using **case `0x1B`
  (`27`), `ForceItemDrop`** -- see the "`StatusEffect` sub-cases, full
  case-by-case writeup" section below: it ORs bit `0x04` into
  `FightState+0x1480`, the exact same byte/family `ExtraExpBonus`
  (case `2`, bit `0x01`) and `GrantExtraXp` (case `3`, bit `0x02`) use.
  Mechanically distinct from both Stink Pellet variants (which both use
  the paralysis case `0x11`), confirming `Wizard Cracker` as a distinct,
  non-paralysis effect -- exactly the kind of "not paralysis" outlier
  the ordering evidence predicted. `Wizard Cracker`'s own move
  description text (`data/text/en_us.json` string ids `1725`/`2615`)
  states its effect as making the target creature drop an item; what
  reads `FightState+0x1480`'s bit `0x04` to grant that item is not
  traced.

Confidence: the menu-order/mechanism chain above (7-item table ->
confirm dispatch -> Special Move submenu -> `bSpellId` -> `0x8000`-branch
table read) is **PROVEN**; the specific `44`/`45`/`46` <-> move-name
assignment is **STRUCTURAL MATCH**, corroborated by both position
(matches the string-id order exactly) and content (the mechanically odd
one out, effect `46`, lands on `Wizard Cracker`, the mechanically odd one
out by gameplay behavior) -- not yet a live/dynamic confirmation the way
`ResolveMeleeAttack` got one.
