# Battle system -- memory map

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

This document covers battle *mechanics*: the `BattleFighter` record, turn
order, the melee and spell damage formulas, the status-effect system, and
the spell/level tables. The menu tree that selects an action, the
`ShowBattleMessage` dialog-text dispatcher, the item catalog, the
animation-state dispatchers (`TickFighterAttackAnimState_candidate`,
`TickPlayerActionState`), and the per-character Special Move
content are in [`battle-ui.md`](battle-ui.md).

## Attribution

External, unverified leads were contributed by two members of the HP3-GBA
speedrunning/TAS community and cross-checked against the disassembly
before being trusted:

- **jogotu** (BizHawk live-memory script, `hp3rng.lua`) -- source of the
  `fight_struct`/RNG findings in [`rng.md`](rng.md), and of the
  `BattleFighter` fighter-type/roster-index fields below.
- **jlun2** -- pointed at three addresses: `0x0803B3E0` (matches
  `Mt19937RandRange`), `0x0803B400` (a literal-pool constant in that same
  function, reached from a damage-roll call site), and `0x08017F70`
  (inside `ResolveEnemyAttack`'s damage-halving logic, tied to
  Hermione's "Be More Careful"). All three led directly to findings in
  this document.
- A community-written GameFAQs guide's real per-spell MP costs independently
  confirm `SpellId 6 = PetrificusTotalus` (its `Uno`/`Duo` costs match
  exactly) -- see `g_awSpellMpCost` below. `SpellId`'s full 10-value
  ordering, including `1 = Informus`, is PROVEN directly from
  `DrawBattleMenuText`'s own dialog-text lookup -- see `bSpellId` below.

Dynamic verification via mGBA's gdb stub (breakpoint at `0x08017E44`, run
through mGBA's own debug console) confirmed several findings below live
-- contrast with `krawall.md`'s "Dynamic verification attempt" section,
where the same stub was unreliable under scripted breakpoint/continue
sequencing.

## Battle round -- consolidated pseudocode

Enough to drive a full battle: roster setup, one round's turn order, and
every fighter-turn/status/damage path. Each function is detailed with
its supporting evidence in the sections below; addresses are US ROM.

```c
// ---- Setup (once per battle) ----

void SetupBattleRoster() {            // 0x0800EDD8
    // InitMonsterBattleActor (0x08014C88) / InitPlayerBattleActor (0x080149C4)
    // populate pFighters[] from MonsterTable / g_pPartyMasterStats
    JitterEnemyTurnOrder();           // 0x0800E5B8
    BuildTurnOrder();                 // 0x0800E62C
}

void JitterEnemyTurnOrder() {
    for (Fighter f : pStagingFighters)
        if (f.bFighterType == Enemy)
            f.bStat_speed = clamp(f.bStat_speed + Mt19937RandSigned(0x10), 5, 251);
    // player fighters are untouched -- speed comes straight from
    // g_pPartyMasterStats (Buckbeak: hardcoded 10)
}

void BuildTurnOrder() {
    // selection-sort pStagingFighters into pFighters ascending by
    // bStat_speed (tie-broken so equal values stay stable)
    for (Fighter f : pFighters) {
        if (f.bFighterType == Enemy) aEnemySlotTurnOrderIndex[f.bSlotParam] = f.turnOrderIndex;
        else                         aAllySlotTurnOrderIndex[f.bSlotParam] = f.turnOrderIndex;
        SpawnTurnOrderIcon(f);        // 0x08014F1C, UI only
    }
    // both arrays 0xFF-initialized per slot; aEnemySlotTurnOrderIndex = enemy UI-slot
    // -> turn-order-index, aAllySlotTurnOrderIndex = ally UI-slot -> turn-order-index
}

// ---- One round ----

void RunBattleRound() {
    for (int i = 0; i < activeFighterCount; i++) {   // FightState+0x106F
        Fighter *f = &pFighters[i];
        if (f->wHp == 0) continue;                   // fainted
        RunFighterTurn(i);
    }
    EndOfRoundStatusTick();                           // state 2, poison
}

void RunFighterTurn(int fighterIndex) {
    Fighter *f = &pFighters[fighterIndex];

    if (f->bStatusFlags & Paralyzed) {
        int r = RollFighterParalysisEscape(fighterIndex);  // 0x0800FFAC
        if (r == 1) return;                                // can't move this turn
        // r == 3: escape roll succeeded, Paralyzed cleared -- falls through and acts
    }

    if (f->bFighterType == Enemy) {
        DrawEnemyStatsUi_candidate(fighterIndex, 0);      // 0x0800e39c: portrait, HP bar, name, HP/MaxHP, level
        int target = EnemyTargetSelection_undecoded;      // selection step not decoded; feeds ResolveEnemyAttack below
        MonsterTableEntry *m = &MonsterTable[f->bRosterIndex];
        int damage = ResolveEnemyAttack(fighterIndex, target);   // 0x08017E44
        g_nLastDamage = damage;
        if (m->special_effect_chance == 100 || damage != 0)
            RollMonsterSpecialEffect(f->bRosterIndex, target, damage);  // 0x08015020
    } else {
        // bPendingActionKind/bSpellId/bSpellLevel/bSelectedActionIndex
        // already set by the battle menu -- see battle-ui.md
        DispatchPendingAction(fighterIndex);                 // 0x080100a0
    }
}

void EndOfRoundStatusTick() {                          // TickBattleTurnStateMachine state 2, 0x0800F794
    for (Fighter f : pFighters) {
        if (f.bStatusFlags & Poisoned) {
            ShowFloatingDamageNumber(f.bPoisonDamage, 4, f.index, 0);  // 0x080181AC
            ApplyStatusDamageToFighter(f.bPoisonDamage, f.index);       // 0x08018094
        }
    }
}

// ---- Enemy attack ----

int ResolveEnemyAttack(int attackerIndex, int defenderIndex) {   // 0x08017E44
    Fighter *attacker = &pFighters[attackerIndex];
    Fighter *defender = &pFighters[defenderIndex];

    int accuracy = attacker->bAccuracy;
    if (defender->bStatusFlags & Hidden) accuracy -= 25;
    if (Mt19937RandMax(99) >= accuracy) return 0;         // miss

    int damage = Mt19937RandRange(attacker->wDamageRollMin, attacker->wDamageRollMax);
    damage = damage * defender->bDefenseFactorPercent / 100;

    if (attacker->bStatusFlags & AttackWeakened)
        damage >>= (defender->bStatusFlags & DefenseBoost) ? 2 : 1;
    else if (defender->bStatusFlags & DefenseBoost)
        damage >>= 1;
    damage += 1;                                            // rounding

    if (damage != 0 && !(defender->bStatusFlags & Hidden)) {
        int roll = Mt19937RandMax(100);
        if (roll > 100 - attacker->bCritChance) {
            damage *= 2;
            damage += 999;             // sentinel: "Critical hit!", not literal damage
        }
    }

    return damage;                 // caller applies it, e.g. via ApplyDamageToFighter
}

void RollMonsterSpecialEffect(byte monsterIndex, byte targetFighterIndex, ushort damage) {  // 0x08015020
    MonsterTableEntry *m = &MonsterTable[monsterIndex];
    if (m->special_effect_chance == 100 || Mt19937RandMax(99) < m->special_effect_chance) {
        TriggerBattleEffect(m->special_effect_id,
                             pFighters[bActiveFighterIndex].bSlotParam + 3,
                             pFighters[targetFighterIndex].bSlotParam,
                             bActiveFighterIndex, targetFighterIndex, damage);
        pFighters[bActiveFighterIndex].bSpellId = Informus;  // borrowed zero-power id, display only
    }
}

// Every effect call funnels through TriggerBattleEffect (0x08018B70), which
// stages its args into the 0x03002750 area (`EffectStaging` in
// include/battle.h), spawns the effect object via CreateEffectScriptObject,
// then clears the attacker's anim state in FightState. Signature PROVEN by
// caller/callee codegen -- (u8 effectId, s32 x4, u16 damage): effectId is
// the only narrow param (u8 entry extend at 0x08018B74; params 2-4 have
// none), damage is u16 (callers extend with lsl/lsr #0x10). Returns the
// spawned Object*; no call site uses it.

// ---- Damage application (shared by both attack paths) ----

void ApplyDamageToFighter(short damage, uchar fighterIndex) {   // 0x08017F98
    Fighter *f = &pFighters[fighterIndex];
    f->wHp -= damage;
    if (f->wHp == 0 || f->wHp > f->wHp_max) {   // fainted, or underflowed past 0
        if (bFaintMessageCount == 0) ShowBattleMessage(AttackResult, fighterIndex, 2);
        g_anFaintedRosterIndices[firstFreeSlot] = f->bRosterIndex;
        g_nXpAccum   += MonsterTable[f->bRosterIndex].reward_xp;
        g_nGoldAccum += MonsterTable[f->bRosterIndex].reward_gold;
        f->wHp = 0;
        f->nSelectedTargetIndex = -1;
        SetFighterAttackAnimState(f->pObject, 1);
    }
}

// ---- Player spell/action turn ----

void DispatchPendingAction(int fighterIndex) {                  // 0x080100a0
    Fighter *f = &pFighters[fighterIndex];
    switch (f->bPendingActionKind) {
    case None: case Informus:
        ShowBattleMessage(ActionAnnounce, 0, 0);
        TrackSpellFamiliarity(f->bFighterType, f->bSpellId, f->bSpellLevel, &f->wHp);
        SetFighterAttackAnimState(f->pObject, 0x1a);    // -> ExecutePlayerAttackSequence
        break;
    case UseItem:
        ShowBattleMessage(ItemUseAnnounce, f->bSpellLevel, 0);
        SetFighterAttackAnimState(f->pObject, 0x04);
        break;
    case SpecialMove:
        if (f->bFighterType == Harry) f->bSpellId = (SpellId)g_nFolioUniversitasSlot;
        ShowBattleMessage(SpecialMoveAnnounce, f->bSpellId, 0);
        SetFighterAttackAnimState(f->pObject, 0x15);
        if (f->bFighterType == Hermione) nHermioneLecturesKnown = 1;
        else if (f->bFighterType == Ron)  nRonMovesKnown = 1;
        break;
    case Flee:
        if (Mt19937Chance(0x4b) == 0) {
            ShowBattleMessage(EscapeBlocked, 0, 0);
            SetFighterAttackAnimState(f->pObject, 0x05);
        } else {
            PlaySoundById(0x9d);
            PushGameMode(8, 3, DAT_03003b50);          // leaves the battle
        }
    }
}

// case 0x1A of TickPlayerActionState's jump table, see battle-ui.md.
// A camera windup/approach-and-return pan (a separate sub-state machine on
// Object+0x90, not modeled here) runs before this for every spell except
// Fumos. Fumos skips only that camera pan, not the cast itself -- MP
// deduction, target resolution, ResolvePlayerAttack, and its own
// TriggerBattleEffect cast VFX all still run for it below, exactly like
// any other spell (confirmed by decompiling 0x080161FE directly: its
// bSpellId==8 early-out only short-circuits the Object+0x90 state-0x21/
// 0x41 camera-pan branches, and falls through into this same shared tail).
void ExecutePlayerAttackSequence(int attackerIndex) {            // 0x080161FE
    Fighter *f = &pFighters[attackerIndex];

    // Buckbeak: the bAttackOutcomeState == 6 tail of this same case (ROM
    // 0x08016D34). No ResolvePlayerAttack, no TriggerBattleEffect, no
    // ShowDamageNumber -- and no target-resolution call here either: the
    // slot was resolved at selection time, so this tail just reads
    // aEnemySlotTurnOrderIndex[bSelectedActionIndex] (scan-to-first-live
    // in "Target redirect" below already ran for it).
    if (f->bFighterType == Buckbeak) {
        PlaySoundById(0x37);
        // Master stats, not the live pFighters copy (g_aPartyMasterStats
        // is 0x030024EC; bLevel sits at BattleFighter+0x0E).
        g_nLastDamage = (g_aPartyMasterStats[Harry].bLevel >> 1) + 30;
        SetFighterAttackAnimState(targetObject, 2);
        ShowBattleMessage(AttackResult, g_nLastDamage, 0);
        if (bPendingStatusMessageVariant != NO_PENDING_STATUS_MESSAGE_VARIANT)
            ShowBattleMessage(AttackResult, 0, bPendingStatusMessageVariant);
        ShowFloatingDamageNumber(g_nLastDamage, 0, targetSlot, 0);
        ApplyDamageToFighter(g_nLastDamage, targetSlot);
        return;
    }

    f->wMp -= g_awSpellMpCost[f->bSpellId * 3 + f->bSpellLevel];
    g_pPartyMasterStats[f->bFighterType].wMp = f->wMp;

    if (f->bSelectedActionIndex == 0xFE) {     // party-wide/self cast (any Tria except Glacius, Fumos Duo, ...)
        for (Fighter e : pFighters) if (e.bFighterType == Enemy) {
            int damage = ResolvePlayerAttack(attackerIndex, e.index);   // 0 for status-only spells, e.g. Fumos
            ShowDamageNumber(e.index, damage);
            ApplyDamageToFighter(damage, e.index);
        }
    } else {
        // Fumos targets an ally (aAllySlotTurnOrderIndex); every other spell targets
        // an enemy (aEnemySlotTurnOrderIndex) -- see "Target redirect" below
        int target = ResolveTargetIndex(f->bSpellId == Fumos, f->bSelectedActionIndex);
        int damage = ResolvePlayerAttack(attackerIndex, target);
        ShowDamageNumber(target, damage);
        ApplyDamageToFighter(damage, target);
    }

    TriggerBattleEffect(g_abSpellEffectId[f->bSpellId * 3 + f->bSpellLevel], ...);
}

int ResolvePlayerAttack(int attackerIndex, int targetIndex) {    // 0x08017C24
    Fighter *attacker = &pFighters[attackerIndex];
    Fighter *target = &pFighters[targetIndex];
    int power;

    if (g_bSpellMissStreak < 2 && Mt19937RandMax(100) >= attacker->bAccuracy) {
        g_bSpellMissStreak++;
        power = 0;
    } else {
        g_bSpellMissStreak = 0;
        int idx = attacker->bSpellId * 3 + attacker->bSpellLevel;
        power = g_awSpellPowerBase[idx]
              + __divsi3(g_awSpellPowerScale[idx] * attacker->bLevel, 9);

        if (attacker->bFighterType == Hermione) power = power * 17 / 16;
        else if (attacker->bFighterType == Ron)  power = power * 15 / 16;

        if (power == 0) power = 1;
        if (attacker->bStatusFlags & SpellPowerBoost) power = power * 4 / 3;
    }
    if (power == 0) return 0;

    uint critScale = attacker->bLevel < 2 ? 0
                     : min(12, (attacker->bLevel >> 1)
                               + ((attacker->bStatusFlags & SpellPowerBoost) ? attacker->bLevel >> 2 : 0));

    int slot;
    switch (attacker->bSpellId) {
        case Flipendo:          slot = 0; break;
        case Verdimillious:     slot = 2; break;
        case Diffindo:          slot = 5; break;
        case Incendio:          slot = 1; break;
        case WingardiumLeviosa: slot = 3; break;
        case Glacius:           slot = 4; break;
        default: return 0;   // PetrificusTotalus, Spongify -- pure status spells
    }
    int effectiveness = target->aSpellEffectiveness[slot];

    int roll = Mt19937RandMax(100);
    bool crit = (97 - critScale) < roll;
    if (crit) power *= 2;

    int damage = (effectiveness * power) / 100 + 1;
    if (crit) damage += 0x3E9;   // 1001, sentinel -> "Critical hit!"
    return damage;
}

void TrackSpellFamiliarity(FighterType fighterType, SpellId spellId, char spellLevel,
                            SpellProgressBlock *p) {              // 0x08010008
    byte *pCastLevel = p->aSpellCastLevel + spellId;
    if (*pCastLevel < g_abSpellMaxLevel[spellId] && fighterType != Buckbeak) {
        byte *pUsage = p->aSpellUsageProgress + spellId;
        *pUsage += spellLevel + 1;
        g_abPartySpellUsage[spellId + fighterType * 0x48] += spellLevel + 1;
        if (g_abSpellLevelUpThreshold[*pCastLevel - 1] <= *pUsage) {
            ShowBattleMessage(SpellLevelUp, 0, 0);
            (*pCastLevel)++;
            *pUsage = 0;
            g_abPartySpellLevel[spellId + fighterType * 0x48]++;
            g_abPartySpellUsage[spellId + fighterType * 0x48] = 0;
        }
    }
}

int RollFighterParalysisEscape(int fighterIndex) {                 // 0x0800FFAC
    Fighter *f = &pFighters[fighterIndex];
    if (!(f->bStatusFlags & Paralyzed)) return 0;             // acts normally
    if (!Mt19937ChanceNoisy(f->bParalysisEscapeChance)) {
        f->bParalysisEscapeChance += 25;                       // ratchet up
        return 1;                                              // can't move this turn
    }
    ClearParalyzedFighter(fighterIndex);                       // clears Paralyzed, sets bit 0x80
    return 3;                                                  // can move again this turn
}
```

Notes on pieces the pseudocode above elides:

- **`ResolveTargetIndex`** (the enemy target-slot redirect): confirmed at
  the raw-disassembly level (`build/us/full_disasm.s:37099-37136`).
  Before resolving any single-target cast, the game reads
  `aEnemySlotTurnOrderIndex[bSelectedActionIndex]`; a `0xFF` there (target already
  fainted, or -- Buckbeak's case -- `bSelectedActionIndex` was never a
  real enemy UI slot to begin with) triggers a linear scan of
  `aEnemySlotTurnOrderIndex` from index `0` for the first non-`0xFF` entry, whose
  index overwrites `bSelectedActionIndex`. The identical pattern exists
  once more in the same function (`full_disasm.s:37040-37098`) scanning
  `aAllySlotTurnOrderIndex` (ally slots) instead -- this is what lets Fumos always
  find a living ally target.
- **`ResolveBuckbeakTarget`** is exactly this same enemy-slot redirect.
  `OpenBattleTopMenu` (`0x080104A0`) special-cases `bFighterType ==
  Buckbeak` before normal menu setup: it sets `bPendingActionKind = None`
  and rejection-samples `Mt19937RandMax(6)` until it lands on a living,
  non-`Enemy` fighter's raw `pFighters` index, storing that into
  `bSelectedActionIndex`. Since that's a turn-order position (0-6), not a
  real enemy UI slot (0-3), `aEnemySlotTurnOrderIndex[bSelectedActionIndex]` is
  effectively always `0xFF`, so the redirect above fires every time and
  reassigns him to a real living enemy -- his own roll is discarded noise;
  the shared redirect is what actually picks his target
  (`build/us/full_disasm.s:37180-37182` confirms the `Object+8 == 3`
  branch that skips straight past the MP-deduction/`ResolvePlayerAttack`
  block into his own hardcoded-damage sub-state, `Object+0x60 == 6`).
- **Enemy target selection**, matched in `src/battle/tick_fighter_attack_anim_state.c`
  (`TickFighterAttackAnimState_candidate` case `0x1A`, `Object+0x90 == 0x21`
  sub-branch -- not case `0`, which is just the post-hit flash-clear tail):
  ```c
  if (attacker->bRosterIndex == 0x3F) {   // Lupin Werewolf only
      target = 0xFF;
      for (i = 0; i < g_pFightState->bFighterCount; i++)
          if (g_pFightState->pFighters[i].bFighterType == Buckbeak)
              target = i;
  } else {
      do {
          roll = Mt19937RandMax(g_pFightState->bFighterCount - 1);
          candidate = &g_pFightState->pFighters[roll];
      } while (candidate->bFighterType == Enemy
                || candidate->pObject == NULL
                || candidate->nSelectedTargetIndex == -1);
      target = roll;
  }
  attacker->bSelectedActionIndex = target;
  ```
  The general case is a uniform rejection sample over the whole `pFighters`
  array (allies and enemies together, `Mt19937RandMax(bFighterCount - 1)`)
  until it lands on a living ally slot -- confirmed against a live trace
  where `bFighterCount == 2` (Harry vs. a single enemy) produced
  `Mt19937RandMax(1)`. Roster index `0x3F` (Lupin Werewolf) skips the RNG
  entirely and always singles out Buckbeak when he's in the party (falling
  back to `0xFF`, i.e. no valid target, if he isn't) -- a plausible-looking
  `aSpellCastLevel[i - 0x10]` read in an earlier decompile of this same
  logic was pointer arithmetic that Ghidra couldn't resolve back to its
  real field; the byte it actually reads is `BattleFighter+0x00`
  (`bFighterType`), confirmed against `full_disasm.s` and reproduced
  byte-exact.
- Item-use resolution is `TickPlayerActionState`'s sub-state `2` (matched
  byte-exact); no `Mt19937*` calls there.

## `BattleFighter` struct (0x48-byte stride)

Live, in-battle per-fighter record. Array pointer lives at
`fight_struct+4` (`fight_struct` is `*0x030024E8`, per `rng.md`). One
record per active combatant, both allies and enemies.
`InitMonsterBattleActor` (`0x08014C88`, see
[`../formats/folio_bruti.md`](../formats/folio_bruti.md)) populates a
monster's record from `MonsterTable`; `InitPlayerBattleActor_candidate`
(`0x080149C4`) populates a party member's from
`g_pPartyMasterStats_candidate` (`0x030024EC`).

| Offset | Size | Field | Confidence |
|---|---|---|---|
| `0x00` | u8 | `bFighterType` (enum, see below) | PROVEN |
| `0x01` | u8 | `bRosterIndex` (enemy/hero index) | STRUCTURAL MATCH |
| `0x03` | u8 | `bSlotParam` -- fixed UI slot (enemy `0-3` / ally `0-2`, separate spaces) | PROVEN |
| `0x04` | u32 | `pObject` -- pointer to this fighter's sprite `Object` | PROVEN |
| `0x08` | u16 | `wHp` | PROVEN |
| `0x0A` | u16 | `wMp` | PROVEN |
| `0x0C` | u16 | `wRewardXp` (`MonsterTable+0x10`) | PROVEN |
| `0x0E` | u8 | `bLevel` -- see "`bLevel`" below | PROVEN as a field; monster-side value UNCONFIRMED (never read) |
| `0x10`-`0x19` | u8[10] | `aSpellCastLevel[SpellId]` -- mastered level per spell | PROVEN |
| `0x1A`-`0x23` | u8[10] | `aSpellUsageProgress[SpellId]` -- progress to next level | PROVEN |
| `0x24` | u16 | `wHp_max` | PROVEN |
| `0x26` | u16 | `wMp_max` | PROVEN |
| `0x28` | u16 | `wRewardGold` (`MonsterTable+0x12`) | PROVEN |
| `0x2A` | u8 | `bStat_speed` -- turn-order/initiative, lower = earlier (`MonsterTable+0x03`) | PROVEN |
| `0x2B` | u8 | `bAccuracy` | PROVEN |
| `0x2C` | u8 | `bCritChance` (`MonsterTable+0x05`) -- monster-only, never populated for player fighters | PROVEN |
| `0x2E` | u8 | `bDefenseFactorPercent`, percent (`damage = damage * this / 100`) -- player-only | PROVEN |
| `0x2F` | u8 | `bMagicDefensePercent` -- UI-displayed ("Magic Def"), no damage formula reads it | UNCONFIRMED as a formula input |
| `0x30` | u16 | `wDamageRollMin` (`MonsterTable+0x06`) | PROVEN |
| `0x32` | u16 | `wDamageRollMax` (`MonsterTable+0x08`) | PROVEN |
| `0x34`-`0x39` | u8[6] | `aSpellEffectiveness[6]` (`MonsterTable+0x0A`-`+0x0F`) | PROVEN |
| `0x3A` | u8 | `bSelectedActionIndex` -- UI slot the target-confirm menu wrote, later resolved to a real fighter (see "Target redirect" above) | STRUCTURAL MATCH |
| `0x3B` | u8 | `bPendingActionKind` (enum, `None=0/UseItem=1/SpecialMove=2/Flee=3/Informus=4`) | PROVEN |
| `0x3C` | u8 | `bSpellId` (enum `SpellId`, `0`-`9`) | PROVEN |
| `0x3D` | u8 | `bSpellLevel` (0-2, Uno/Duo/Tria) | PROVEN |
| `0x3E` | u8 | `bUnk_0x3E`, set to `0xff` on init | UNCONFIRMED, no reader traced |
| `0x42` | u8 | `bStatusFlags` bitfield, see below | PROVEN |
| `0x43` | u8 | `bPoisonDamage` -- per-turn poison tick damage | PROVEN; monster fighters' value origin unknown (not copied from `MonsterTable`) |
| `0x44` | u8 | `bParalysisEscapeChance` -- starting/ratcheting escape % | PROVEN |

`InitMonsterBattleActor` also wires each fighter's sprite `Object`
(anim table, effect-channel pointers) and hardwires `pObject->pfnTick =
TickFighterAttackAnimState_candidate` -- the reason every `Enemy`
resolves via `ResolveEnemyAttack` rather than `ResolvePlayerAttack`; see
"The NPC-vs-PC split" below.

### `BattleFighter+0x00` (`bFighterType`) -- enum `FighterType`, PROVEN

`Harry=0, Hermione=1, Ron=2, Buckbeak=3, Enemy=0xFF`. Backed by an exact
string match: "Harry"/"Hermione"/"Ron" at `0x8ec`-`0x8ee`, "Buckbeak" at
`0xa3d`; independently corroborated by six `ShowBattleMessage` cases (2,
4, 7, 8, 0xD, 0xE).

### The NPC-vs-PC split -- which damage formula a fighter uses, PROVEN

Not a per-turn decision: it's which `pfnTick` callback got registered on
the fighter's `Object` at init. `InitMonsterBattleActor` hardcodes
`TickFighterAttackAnimState_candidate` (`0x08015608`) into every enemy
`Object`; its case `0x1A` calls `ResolveEnemyAttack` (additionally gated
on `bFighterType == 0xFF` at the call site). `InitPlayerBattleActor_candidate`
(`0x080149C4`) hardwires `pObject->pfnTick = TickPlayerActionState`
(`0x0801602D`) unconditionally for every non-enemy fighter, including
Buckbeak -- so Buckbeak's turn runs the same state machine as the three
spellcasters, but his damage bypasses `ResolvePlayerAttack` entirely (see
"Buckbeak" above): he's driven by the shared player dispatcher, but with
a fully separate, level-scaled damage sub-state (`Object+0x60 == 6`) no
other fighter type reaches.

**`TickBattleTurnStateMachine`'s case 4** confirms this at the
dispatch level: non-`Enemy` fighters call `DispatchPendingAction()`
directly (menu-driven), while `Enemy` fighters skip it and set anim state
`0x1a` directly after `DrawEnemyStatsUi_candidate`/a can't-move check
(`RollFighterParalysisEscape`).

Both `TickFighterAttackAnimState_candidate` (enemy) and
`TickPlayerActionState` (player) are 27-case animation-state
dispatchers with a shared-tail `bl`-as-branch idiom; their full case
tables and every non-mechanical callee live in
[`battle-ui.md`](battle-ui.md), since they're orchestration/animation,
not combat math.

### `InitPlayerBattleActor` (`0x080149C4`), PROVEN

`(BattleFighter *fighter, s32 fighterType, s32 battleSlotIndex)` returns the
fighter's new `Object *`. Allocates via `AllocDefaultObject`, records
`wFighterType`/`bUnk_0x7C = 0`, sets `bGfxSlotAndFlags = (v & ~0xC) | 4`,
positions with `SnapObjectPosition`/`StartObjectMove` at
`(0xD4 - slot*36) << 16`, `slot*0x40000 + 0x6E0000`, then
`sub_08003A44(pObject, 0, 0x400, 0xC)`, `bUnk16 = 0x40`, `dwUnk_0x28 = 1`,
`dwFlags = 0x20006011`, attack-anim state `0xF`, `bAnimFrameDelay = 1`,
`pfnTick = TickPlayerActionState`. Copies the 10 spell slots
(`i <= 9`) and, outside Folio Universitas returns, the party stats from
`g_pPartyMasterStats_candidate` for `type < 3` (Buckbeak gets `bLevel 50`,
`wHp 400`, `wMp/wMp_max 999`, `bStat_speed 10`, `bAccuracy 101`, both
defenses `100`) plus a backup `memcpy` of the record into slot 3
(`0x030025C4`). `wHp == 0` takes the faint branch (fainted anim table,
`dwFlags &= ~0x10`, re-snap, `nSelectedTargetIndex = -1`), else the live
branch (anim data row `type * 0x244`, cursor `base + slot*4 + 2`).
`bSelectedActionIndex` inits to `0xFF` at `+0x3A`, which is why that offset
is the action index and `+0x3C` the spell id. The decompilation
(`src/battle/init_player_battle_actor.c`, byte-identical) folds the flag
update through the mask temp itself (`mask &= maskVal`); a separate dest
pseudo would tie to the loaded value in regmove and steal `r0` from the
mask. No JP row exists for this range, so the JP bytes here are unverified
against that source.

### `InitMonsterBattleActor` (`0x08014C88`), PROVEN

`(BattleFighter *fighter, s32 monsterIndex, s32 battleSlotIndex)` returns
the fighter's main `Object *` (despite the `void` prototype floating
around: the ROM ends in `adds r0,r6,#0`, same as the player counterpart).
`wFighterType` is `monsterIndex + 4`; positioning is `(slot*36 + 0xCC)` /
`(0x4E - slot*4)` with a `+0x18` restructure for the move; `dwFlags` is
`0x20006019` (`0x6019` for the companion) and `bUnk16` is `-0x40`. Types
3/29/26 get extra `sub_08003A30`/`sub_08003A44` calls on the main object;
types 45-47 additionally spawn a shadow `Object` (own anim tables at
`0x0804EF54`/`0x08053850`) cross-linked at `+0xA0`/`+0xA8`. The
`BattleFighter` is filled field-for-field from `MonsterTable` (stride
`0x18`); `wHp`/`wHp_max` share one load, `bRosterIndex` is the monster
index, `bFighterType` is `Enemy`, `unk3E` is assigned `-1` directly (no
read-modify-write), and there is no faint branch. The decompilation
(`src/battle/init_monster_battle_actor.c`, byte-identical) holds the
cursor addresses in two temps to reproduce ROM's computation order, and
writes the slot doubling as `slot + slot` (`slot * 2` splits the copy and
shift across `r3`/`r0`).

## `ResumeBattleAfterSubmode_candidate` (`0x0800F5F0`), PROVEN

Called unconditionally at the tail of both `InitializeBattle` branches
(fresh battle and submode-return), immediately after the room's battle
background/palette load. Three cases on `g_PrevGameModeCtx`:

- **`FolioUniversitas`** (a Special Move card was just selected there,
  `g_GameModeArg2 < 0xff`): tags the active fighter's
  `bPendingActionKind = SpecialMove`, then dispatches on
  `g_aCardTargetingMeta[g_GameModeArg2][0]` -- **already a named, matched
  global** (`extern u8 g_aCardTargetingMeta[][2]`, `0x080514DE`,
  `include/battle.h:374`), used from `TickPlayerActionState`'s own
  Special-Move-resolution case in `src/battle/tick_player_action_state.c`.
  Indexed by the raw Folio Universitas card slot `0`-`15`; `[0]` is the
  target-type byte this function reads, `[1]` is a second, independently
  read boolean -- gates an extra `sub_080129F4()` cleanup call across
  several post-hit `bAttackOutcomeState` cases in
  `TickPlayerActionState`, not yet named/understood further. `[0]`'s
  values: `0` = no target menu -- immediate self/party cast,
  `bSelectedActionIndex = 0x2a`, `bMenuScreen = 0`; `1` =
  `OpenEnemyTargetMenu_candidate` (`0x08012B98`, `bMenuScreen = 6`,
  confirm handler `ConfirmEnemyTargetMenu`) -- matches
  `TickPlayerActionState`'s own `cardMeta != 0` branch, which resolves an
  enemy target the same way; `2` = `OpenAllyTargetMenu` (`0x080107BC`,
  `bMenuScreen = 8`) -- matches its `cardMeta == 2` branch; `3` =
  `OpenPendingFighterMenu_candidate` (`0x0801319C`, `bMenuScreen = 9`,
  confirm handler `ConfirmPendingFighterMenu_candidate` -- see
  "`bMenuScreen = 9`" below) -- matches its `cardMeta == 3` branch, which
  indexes `pPendingFighters_candidate[ACTIVE_FIGHTER.bSelectedActionIndex]`
  directly, the same field this menu's confirm handler writes. Every case
  but `0` also sets `bBattleState = 3`.
- **fresh battle** (neither `FolioUniversitas` nor `HelpTopicScreen`):
  resets per-round state -- `wBattleStateTimer = 0`, `bActiveFighterIndex
  = 0xff`, `bMenuFighterIndex = 0xff` unless a fighter with a live pending
  spell cast is found by scanning `aSpellCastLevel`/`aSpellUsageProgress`
  -- pushes battle state `2`, and sets `bScreenShakeTimer_candidate =
  0x1e` (the screen-shake `UpdateBattle` ticks down before the turn state
  machine gets its first tick).
- **`HelpTopicScreen`**: falls straight into the shared tail below.

Shared tail (`FolioUniversitas`'s branch returns before reaching it; the
fresh-battle branch also returns before it): if `bMenuScreen == 1`,
reopens the top battle menu -- `OpenBattleTopMenu(idx, 6)` when returning
from `HelpTopicScreen`, `OpenBattleTopMenu(idx, 1)` when the active
fighter had a pending `SpecialMove` (cleared back to `None` here), else
`OpenBattleTopMenu(idx, 5)`.

### `InitializeBattle`'s scene-setup helpers, PROVEN

Called from `InitializeBattle` (`0x0800DBAC`, matched in
`src/battle/initialize_battle.c`) ahead of `ResumeBattleAfterSubmode_candidate`
above; all four are visual/Object plumbing, no combat-mechanical state:

- **`InitBattleBackground_candidate`** (`0x0800EBAC`): VBlank callback,
  VRAM clear, loads both battle background layers (room-indexed table at
  `0x0804E09C`, with a fixed boss-room blob substituted when
  `g_abQuestEventState[0x1a]` is set and the room id is `8`-`15`), camera/BG
  scroll init, and the battle dialog-box palette block.
- **`RestoreFighterObjects_candidate`** (`0x0800F16C`): only called on the
  submode-return path, not for a fresh battle. Rebuilds every fighter's
  sprite `Object` from the `0x128`-byte backup image `FightState` stashed
  at `+0x834` per fighter (Battle's own `Object`s get torn down while
  `FolioUniversitas`/`HelpTopicScreen` is active), spawns/links animated
  shadow `Object`s for monster types `>= 4` that have one, and re-applies
  the `Paralyzed`/`Poisoned` visual pose and status-particle attachment
  from each `BattleFighter.bStatusFlags`.
- **`GetBattleBackgroundData_candidate`** (`0x08012AC0`): the same
  room -> background-blob selection `InitBattleBackground_candidate`
  inlines for its first layer, factored out standalone so
  `InitializeBattle` can also feed the blob into
  `LoadEmbeddedPalette_candidate` to pull its embedded palette.
- **`LoadEmbeddedPalette_candidate`** (`0x08007800`, `(u8 *blob, s32
  paletteRowOffset, s32 rowCount)`): reads `blob[0]` as a flags byte --
  bit `0` set means `blob` holds a raw palette block starting at
  `blob+2`, loaded via `SetPaletteColorsThunk_candidate`; bit `1` (with
  bit `0` clear) loads one fixed 16-color row instead; neither bit is a
  no-op. Not battle-specific -- also called from
  `InitializeLupinPotionCutscene`, `InitializeFolioCardDetailScreen`,
  `InitializeDebugCollectorCardsMenu`, `PlaySpecialSceneEffect`, and
  three other non-battle sites, confirming it as a general graphics-blob
  palette loader, not something written for `InitializeBattle`.

### `bMenuScreen = 9` -- the pending-fighter target menu, PROVEN

`OpenPendingFighterMenu_candidate` (`0x0801319C`) is structurally
parallel to `OpenEnemyTargetMenu_candidate`/`OpenAllyTargetMenu` (same
8-frame screen-wipe-transition preamble, same `DrawFighterStatsUi_candidate`
call, same `bMenuCursor = 0` reset) but targets a third, separate fighter
pool: `FightState->pPendingFighters_candidate` (`+8`, up to 3 slots,
`bPendingFighterCount_candidate` at `+0x1491`), not `pFighters`. Its
cursor-move handler, `TogglePendingFighterCursor_candidate`
(`0x0801310C`, `TickBattleMenuInput` case `9`), only ever offers a binary
choice: `bMenuCursor ^= 1` when `bPendingFighterCount_candidate != 1`,
else forced to `0`. Its confirm handler,
`ConfirmPendingFighterMenu_candidate` (`0x0801320C`), writes
`bSelectedActionIndex = bMenuCursor` directly -- unlike the enemy/ally
menus, with no `aEnemySlotTurnOrderIndex`/`aAllySlotTurnOrderIndex`
translation, consistent with indexing straight into the separate pending
pool. `RestoreFighterObjects_candidate` (`0x0800F16C`) spawns this pool's
`Object`s the same way it does for `pFighters`, and `TickPlayerActionState`
(matched, `src/battle/tick_player_action_state.c`) pans every
`pPendingFighters_candidate[i].pObject` alongside the regular roster
during the Special Move windup/return camera move (`bActionState == 0x1a`,
`bActionFlags == 0x21`/`0x40` cases) -- pending fighters are real,
on-screen `Object`s, not placeholder data.

`TickPlayerActionState`'s own Special-Move-resolution case confirms
`bMenuScreen = 9` is reached exactly when `g_aCardTargetingMeta[slot][0]
== 3`, and on confirm it calls `TriggerBattleEffect` with
`pPendingFighters_candidate[ACTIVE_FIGHTER.bSelectedActionIndex].bSlotParam`
as the target slot -- i.e. this menu really does let the player pick
which pending fighter a card's effect targets. What populates
`pPendingFighters_candidate`/`bPendingFighterCount_candidate` in the first
place is not yet traced (not `SetupBattleRoster`), so which specific
card(s) use `cardMeta[0] == 3` and what a "pending fighter" represents
narratively (a held-in-reserve ally, most plausibly) is still
UNCONFIRMED -- but that it is a live, targetable, on-screen fighter pool,
not a placeholder concept, is now PROVEN via this matched call.

## Turn order -- `bStat_speed`, PROVEN


`MonsterTable+0x03` / `BattleFighter+0x2A` is a turn-order/initiative
value, lower = earlier turn. `bStat_speed` clusters `178-254` across the
53 real Folio Bruti monster rows (mostly act after the player), while
dangerous ones act early (Lupin Werewolf `=20`, Draco `=60`). Buckbeak is
hardcoded to `10`.

- **`JitterEnemyTurnOrder`** (`0x0800E5B8`, matched byte-exact,
  `src/battle/jitter_enemy_turn_order.c`) adds `Mt19937RandSigned(0x10)` to
  each `Enemy`'s `bStat_speed`, clamped to `[5, 251]`. Player fighters are
  untouched -- `bStat_speed` comes straight from
  `g_pPartyMasterStats[fighterType]` for Harry/Hermione/Ron. Runs on
  `pStagingFighters`, ahead of `SetupBattleRoster`'s compaction/copy into
  `pFighters`.
- **`BuildTurnOrder`** (`0x0800E62C`, matched byte-exact,
  `src/battle/build_turn_order.c`) selection-sorts `pStagingFighters` into
  `pFighters` ascending by `bStat_speed`. Each of the first `bFighterCount-1`
  passes scans the whole staging array for the lowest `bStat_speed` still
  above the previous pick (a fainted fighter, `wHp == 0`, is marked
  `nSelectedTargetIndex = -1` and skipped); a fighter tying the running-best
  speed that hasn't been picked yet (`nSelectedTargetIndex == 0`) has its own
  `bStat_speed` nudged up by 1, breaking ties deterministically. A final pass
  moves whichever staging entry is still unpicked (`nSelectedTargetIndex ==
  0`) into the last `pFighters` slot, or marks it faint if `wHp == 0`. Each
  placed fighter's `nSelectedTargetIndex` is overwritten with
  `bEnemyScalePercent_candidate * (turnPosition + 2)`, reusing the same
  field `InitializeBattle` writes the enemy visual-scale percent into
  (`0x40`/`0x30`/`0x20`) -- PROVEN as written, but no reader of this
  numeric value (as opposed to the `-1`/fainted sentinel value, which
  `TickFighterAttackAnimState` does read) has been traced; its purpose is
  UNCONFIRMED. A last pass over `pFighters` writes each `Object`'s
  `bFighterIndex`, spawns its turn-order icon (`SpawnTurnOrderIcon`,
  `0x08014F1C`, UI only, still raw incbin), and populates
  `aEnemySlotTurnOrderIndex[bSlotParam] = turnOrderIndex` for every `Enemy`
  (4-byte array, one per enemy seat) and `aAllySlotTurnOrderIndex[bSlotParam] =
  turnOrderIndex` for every ally (3-byte array) -- both `0xFF`-initialized
  at roster setup, both later read by target resolution (see "Target
  redirect" above).
- **`ReviveFighter_candidate`** (`0x0800E890`) restores a revived
  fighter's `wHp`/`wMp` to max and re-sorts the queue by `bStat_speed` to
  reinsert them (`0xff` marks "already acted this round"). Called by
  opcode `0x97` sub-case `0x1C` (`Revive`) with `g_bEffectTargetIndex` as
  the target -- Harry's `Revive` card is the only script using it.

## `BattleFighter+0x42` (`bStatusFlags`), PROVEN

All 8 bits are claimed by a combat-mechanical effect, each set by one of
opcode `0x97`'s (`StatusEffect`) sub-cases, run by the object/spell
behavior-script interpreter (`0x08018cf8`, see
[`../formats/battle_scripts.md`](../formats/battle_scripts.md)).

| Bit | Name | Read by | Effect |
|---|---|---|---|
| `0x01` | `Hidden` | `ResolveEnemyAttack` (on defender) | `-25` to attacker's accuracy; also gates the bonus-damage/crit check off |
| `0x02` | `Poisoned` | `EndOfRoundStatusTick` | per-turn `bPoisonDamage` tick |
| `0x04` | `PoisonImmune` | opcode `0x97` case `5`'s own gate | blocks re-applying `Poisoned` |
| `0x08` | `AttackWeakened` | `ResolveEnemyAttack` (on attacker) | halves computed damage (stacks with `0x20`, see below) |
| `0x10` | `Paralyzed` | `RunFighterTurn` / `RollFighterParalysisEscape` | skips the fighter's turn until an escape roll succeeds -- gates action selection, not damage |
| `0x20` | `DefenseBoost` | `ResolveEnemyAttack` (on defender) | halves computed damage (stacks with `0x08`) |
| `0x40` | `SpellPowerBoost` | `ResolvePlayerAttack` | `x4/3` power, plus a crit-chance boost |
| `0x80` | (unnamed) | `FUN_0801b430`'s `0x90` gate | blocks (re-)applying `Paralyzed`, mirroring `PoisonImmune`'s role for `Poisoned`. UNCONFIRMED source |

The two halving bits stack multiplicatively: neither set -> no change;
exactly one set -> `damage >>= 1`; both set -> `damage >>= 2`.

Sources, where identified:

- **`Hidden`**: Hermione-exclusive **Fumos** (`SpellId` `8`). `Uno`
  (one ally) applies the "open a fresh message box" variant directly;
  `Duo` (whole party) applies it to the caster and spawns per-target
  copies using the other variant.
- **`Poisoned`**: opcode `0x97` case `5`, gated on
  `(bStatusFlags & 0x06) == 0`. No `SpellId`/card source of its own --
  only confirmed source is the monster-attack table (`Poisoned Bite`,
  see "Monster special-attack effects" below).
- **`PoisonImmune`**: opcode `0x97` case `7`. Source: **Harry's `Poison
  Immunity`** card.
- **`AttackWeakened`**: opcode `0x97` case `6`, matches
  `ShowBattleMessage(AttackWeakened,...)`. Source: **`Spongify`**
  (`SpellId` `9`).
- **`Paralyzed`**: see "The paralysis mechanic" below.
- **`DefenseBoost`**: opcode `0x97` case `0xb`, silent. Source:
  **Hermione's "Be More Careful"** lecture. A second script (effect id
  `36`) also sets it but isn't attributable to any specific card/spell.
  Harry's `Girding All` card (index `7`) was the leading candidate by
  elimination but its script contains no `StatusEffect` opcode at all --
  it applies its defense boost some other way (plausibly a direct write
  to `bDefenseFactorPercent`), not traced further.
- **`SpellPowerBoost`**: opcode `0x97` case `0x13`, silent. Source:
  **Hermione's "Proper Wand Technique"** lecture. No second source found.
- **bit `0x80`**: no spell/card identified; by symmetry with
  `PoisonImmune` a generic "paralysis immunity" is the natural guess, but
  unconfirmed.

### The paralysis mechanic, PROVEN

Every source of `Paralyzed` goes through one helper, `FUN_0801b430`,
called from five `StatusEffect` sub-cases. It sets the bit only when
`bStatusFlags & 0x90 == 0` (not already paralyzed, bit `0x80` clear);
otherwise it may announce `ImmuneToParalysis`.

| Sub-case | Name | Start escape % | Gated on `g_wEffectContextValue`? | Feedback on success |
|---|---|---|---|---|
| `0x0A` | `Paralyze25` | 25 | yes | none |
| `0x11` | `Paralyze99` | 99 | no | none |
| `0x12` | `Paralyze80` | 80 | no | none |
| `0x16` | `ParalyzeMonster` | script operand | yes (same gate as `0x0A`) | VFX + "is paralyzed" text |
| `0x17` | `ParalyzeMonsterChance` | script operand | own extra `Mt19937ChanceNoisy` roll first | VFX only, silent |

The escape-chance parameter (`bParalysisEscapeChance`,
`BattleFighter+0x44`) is a *starting escape chance*, not a duration: it
ratchets `+25` per failed escape roll (see `RollFighterParalysisEscape`
in the consolidated pseudocode above), so `Paralyze25` frees a fighter by
the 4th attempt at the latest, while `Paralyze99`/`Paralyze80` almost
always end on the very next turn -- mechanically closer to "skip one
turn" than a real lockout. `ClearParalyzedFighter_candidate` (called both
on a successful escape and by `CureAilments`) is the one shared cleanup
path for both.

`ParalyzeMonsterChance` stacks three independent RNG layers for one
effect: whether the attack lands, whether paralysis takes at all (its
own roll), and whether/when the target breaks free.

**Sources.** `PetrificusTotalus` (`SpellId` `6`, both `Uno`/`Duo`
scripts) applies `Paralyze25` unconditionally. Harry's `Snitch` card uses
`Paralyze80`. Ron's `Stink Pellet`/`Stink Pellet 2` use `Paralyze99` (see
[`battle-ui.md`](battle-ui.md)). `ParalyzeMonster`/`ParalyzeMonsterChance`
are monster-special-attack only (Suits of Armor/Lupin Werewolf, and
Hinkypunk/Skeleton respectively -- see "Monster special-attack effects").
`PetrificusTotalus` never reaches a `Tria` cast in play -- `g_abSpellMaxLevel`
caps it at level `2`.

### Poison's per-turn tick, PROVEN

`TickBattleTurnStateMachine`'s state-2 handler
(`EndOfRoundStatusTick` above) is end-of-round processing. Both reads
(`bPoisonDamage`) and the HP write go through
`ApplyStatusDamageToFighter_candidate` (`0x08018094`) --
`ApplyDamageToFighter`'s sibling for this path: same HP-underflow/faint
check and animation-state write, but **no XP/gold reward payout** (a
status tick, not a kill-credited attack). `ShowFloatingDamageNumber_candidate`
(`0x080181AC`) is the floating popup: `"Miss!"` when both its damage and
a fourth flag argument are `0`, otherwise the formatted amount.

### `StatusEffect` sub-cases (opcode `0x97`), PROVEN

All 29 sub-cases (`g_apScriptStatusEffectCaseTable`, `0x0801A650`) are
identified, cross-checked against every real script that reaches each
case. The mechanically-live ones (status-flag-setting, resource-restoring,
reward-flag) are below; see
[`../formats/battle_scripts.md`](../formats/battle_scripts.md) for the
opcode format itself.

| Case | Name | Effect |
|---|---|---|
| `0x00`, `0x01`, `0x15` | `SpawnEffectA/B/C` | particle/VFX spawn only, no `BattleFighter` write |
| `0x02` | `ExtraExpBonus` | sets `FightState->bBonusRewardFlags` bit `0x01` -- Harry's `Extra EXP` |
| `0x03` | `GrantExtraXp` | sets `FightState->bBonusRewardFlags` bit `0x02` -- Hermione's "Good Study Habits" |
| `0x04` | `UnusedWinoutWrite` | writes GBA `WINOUT` directly; no real script reaches it |
| `0x05` | `Poisoned` | see bitfield table above |
| `0x06` | `AttackWeakened` | see bitfield table above |
| `0x07` | `PoisonImmune` | see bitfield table above |
| `0x08`, `0x09` | `HiddenSecondary`/`HiddenMain` | see bitfield table above (`Hidden`) |
| `0x0A` | `Paralyze25` | see "The paralysis mechanic" |
| `0x0B` | `DefenseBoost` | see bitfield table above |
| `0x0C` | `BumpMonsterDocLevel` | `Informus`'s payload: bumps `g_abMonsterDocLevel_candidate[speciesId]` to `4` if `< 3` -- the Folio Bruti "analyzed" threshold, see [`../formats/folio_bruti.md`](../formats/folio_bruti.md) |
| `0x0D`, `0x0E` | `SetPostActionFlashFlag`/`Clear...` | temporary post-action visual flag on already-acted fighters, no gameplay effect |
| `0x0F` | `CurePoison` | clears `Poisoned`, zeroes `bPoisonDamage`, refreshes palette (undoes poison discoloration). Used by Harry's Poison Antidote |
| `0x10` | `ToggleUltimateVisual` | operand `0`: glow-in visual only. Non-zero: sets the target's all 10 `aSpellCastLevel` entries to `g_abSpellMaxLevel[i]` -- Harry's `Ultimate MP` card's real payload (grants every spell at max level) |
| `0x11` | `Paralyze99` | see "The paralysis mechanic" |
| `0x12` | `Paralyze80` | see "The paralysis mechanic" |
| `0x13` | `SpellPowerBoost` | see bitfield table above |
| `0x14` | `CureAilments` | `CurePoison` + lifts `Paralyzed` (sets bit `0x80`, resets `bParalysisEscapeChance` to `100`). Player fighters only get the palette/particle cleanup; enemies take a different, untraced path. Used by Remove Jinx (single target) and Reparifors (party) |
| `0x16` | `ParalyzeMonster` | see "The paralysis mechanic". Monster-special-attack only |
| `0x17` | `ParalyzeMonsterChance` | see "The paralysis mechanic". Monster-special-attack only |
| `0x18` | (unnamed) | palette-flash calls only, no `BattleFighter` write |
| `0x19` | `ReplenishPartySp` | every active non-fainted fighter: `wSp = wSp_max` |
| `0x1A` | `ReplenishTargetMp` | `g_bEffectTargetIndex`'s fighter: `wMp = wMp_max` |
| `0x1B` | `ForceItemDrop` | sets `FightState->bBonusRewardFlags` bit `0x04` -- Ron's `Wizard Cracker`. PROVEN, see below |
| `0x1C` | `Revive` | `ReviveFighter_candidate`, see "Turn order" above |

### `FightState->bBonusRewardFlags` -- bonus-reward flags, PROVEN

A 3-bit "bonus reward for this encounter" byte, written by the three
cases above. `ExitBattle` (`0x0800DE50`, `Battle`'s `pDestroyFn` in
`g_pGameModeDispatchTable`) snapshots it into
`g_dwBattleRewardFlagsSnapshot` right before `FightState` is freed. Bits
`0x01`/`0x02` (`ExtraExpBonus`/`GrantExtraXp`) scale the XP shown by
`InitializeVictoryXpScreen` (x3/x1.5). Bit `0x04` (`ForceItemDrop`) is
read in `InitializeVictoryDropScreen` (`0x0801456C`, the victory
screen's second phase) for a `25%` gold bonus (`gold += gold >> 2`,
matching the `42*2*1.25 = 105` figure recorded earlier), and again in
`RollBattleItemDrops` (`0x080147C0`, matched in
`src/battle/roll_battle_item_drops.c`): for up to 4 fainted monsters
(`g_anFaintedRosterIndices`, sentinel `-1`), one roll per monster, each
rolling `0`-`99` against `g_pMonsterDropTable[rosterIndex]`'s two
`(chance, itemId)` slots (adjacent ranges on the same roll, mutually
exclusive -- `chance` is a single byte, not the `u16` its own table's
authoring type declares), but this bit forces the roll to `0`, guaranteeing
a hit on any slot with nonzero chance -- Ron's `Wizard Cracker` really
does force an item drop, via a rigged roll rather than a stored `100%`
value (and always lands on slot0, since slot0's chance is never 0 --
slot1 is unreachable while the bit is set). The first two hits across the
4 monsters are written to the caller's two output item ids; a 3rd+ hit is
discarded. Granted rewards (gold, items, Folio Universitas cards) go through
`GrantBattleReward` (`0x08026DE0`).

### `FightState+0x1054`/`+0x1058`: write-only, purpose unknown

Incremented/mirrored by the object-script interpreter's opcode `0x30`
(tracks `Object+0x60`, also read by
`TickFighterAttackAnimState_candidate` as an attack-outcome state value)
and reset to zero at several attack-boundary transitions
(`TriggerBattleEffect`, `ShowItemUseResult`, inside `ExecutePlayerAttackSequence`).
Nothing reads either field's accumulated value; checked every literal
occurrence of both constants, which is not proof no reader exists by
another addressing path.

## Monster special-attack effects

`RollMonsterSpecialEffect_candidate` feeds `special_effect_id` directly
into `TriggerBattleEffect` -- the same effect-script trigger player
spells/cards use -- so it's a monster's own special-attack effect id, not
a location/group tag. Of the 14 distinct ids used across the 69 monster
records, four carry a confirmed status-effect payload:

| `special_effect_id` | Name | Script | Effect |
|---|---|---|---|
| `27` | `SpecialMonsterPoisonBite` | `StatusEffect 5 8 0` | `Poisoned` -- every venomous Spider/Spitting Snake/Wide-mouth Toad/Bullfrog |
| `60` | `SpecialMonsterParalyzingBlow` | `StatusEffect 22 25 0` | `ParalyzeMonster`, 25% starting escape -- every Suit of Armor variant plus Lupin Werewolf |
| `57` | `SpecialMonsterHinkypunkParalyze` | `StatusEffect 23 ...` | `ParalyzeMonsterChance` -- Hinkypunk |
| `59` | `SpecialMonsterSkeletonParalyze` | `StatusEffect 23 ...` | `ParalyzeMonsterChance` -- Skeleton |

The remaining ids (`0`, `4`, `13`, `16`, `17`, `54`-`56`, `58`, `61`)
either have no `StatusEffect` opcode, or reference sub-cases
`0x00`/`0x01`/`0x18` (pure VFX/particle spawns) -- animation-only, no
gameplay-mechanical payload.

## `MonsterTable` -> `BattleFighter` field correspondence

`InitMonsterBattleActor` copies a monster's record into its live
`BattleFighter` field for field. Record layout, confidence levels, and
observed value ranges are in
[`../formats/folio_bruti.md`](../formats/folio_bruti.md); this is just
the offset mapping, plus which function in this document reads each
field (the reader is what gives the field its name).

| `MonsterTable` | `BattleFighter` | Label | Reader |
| --- | --- | --- | --- |
| `+0x00` | `+0x08`, `+0x24` | `wHp`, `wHp_max` | `ApplyDamageToFighter` |
| `+0x02` | `+0x0E` | `bLevel` | none for a monster's own value |
| `+0x03` | `+0x2A` | `bStat_speed` | `BuildTurnOrder` |
| `+0x04` | `+0x2B` | `bAccuracy` | `ResolveEnemyAttack` |
| `+0x05` | `+0x2C` | `bCritChance` | `ResolveEnemyAttack` |
| `+0x06`, `+0x08` | `+0x30`, `+0x32` | `wDamageRollMin`, `wDamageRollMax` | `ResolveEnemyAttack` |
| `+0x0A`-`+0x0F` | `+0x34`-`+0x39` | `aSpellEffectiveness[6]` | `ResolvePlayerAttack` |
| `+0x10`, `+0x12` | `+0x0C`, `+0x28` | `wRewardXp`, `wRewardGold` | `ApplyDamageToFighter`, `GrantMonsterKillReward` |
| `+0x14`, `+0x15` | -- | `special_effect_chance`, `special_effect_id` | `RollMonsterSpecialEffect_candidate` (read from the table directly, not copied) |

`MonsterTableRow` (`include/battle.h`) uses these same labels.

## XP/reward payout -- `MonsterTable+0x10`/`+0x12`, PROVEN

On a fighter fainting, `ApplyDamageToFighter` adds
`MonsterTable[fighter.bRosterIndex].reward_xp`/`.reward_gold` into two
running EWRAM accumulators, `g_nXpAccum` (`0x0300260E`) and
`g_nGoldAccum` (`0x03002610`). Confirmed live: defeating 2 Brown Recluse
Spiders (`reward_xp=8`, `reward_gold=42`) awarded exactly `16` XP
(`8*2`). Gold was `105` with Ron's `Wizard Cracker` active
(`42*2*1.25 = 105` exactly) -- the source of that `25%` gold figure isn't
determined (`Wizard Cracker`'s own description states an item-drop
effect, not a gold bonus; see `FightState->bBonusRewardFlags` above).
`g_nXpAccum` is consumed by `InitializeVictoryScreen` (see "End-of-battle
flow" below); what consumes `g_nGoldAccum` isn't traced.

A second, independent path exists: `GrantMonsterKillReward` (object-script
opcode `0x83`, `0x0801A254`) adds a species' `wRewardXp`/`wRewardGold`
straight into the same accumulators, bypassing `ApplyDamageToFighter`
entirely -- used by Harry's `Tempest Jinx` (banishes a monster without
dealing damage, so it needs its own reward grant).

## End-of-battle flow, PROVEN

`UpdateBattle` (`0x0800DDB0`, `Battle`'s `pUpdateFn`, matched in
`src/battle/update_battle.c`) is the per-frame entry into all of this:
unless the previous mode was `FolioUniversitas` or
`HelpTopicScreen` (returning from a card-detail/help screen
opened mid-battle), it decrements `FightState->bScreenShakeTimer_candidate`
while nonzero (nudging the BG scroll/priority each tick via `sub_0802D640`
and `g_aBgScrollState[0x25]`), and the tick that timer reaches `0` it
resets every fighter's `Object` (`sub_080039E8`) instead of ticking the
turn state machine that frame. Every other case (timer already `0`, or the
previous-mode skip) calls `TickBattleTurnStateMachine` (`0x0800F794`).

`TickBattleTurnStateMachine`, matched in
`src/battle/tick_battle_turn_state_machine.c`, drives
`FightState->bBattleState` (0x1061, an 8-case dispatch) directly:
every state transition inlines the same guard (refuse to leave states
`6`/`7`, stash the state being left into `bSavedBattleState`) rather than
calling through a shared helper. `CheckBattleVictory` (`0x080186E0`,
from the enemy attack-anim tick) pushes state `7` once every `Enemy`
fighter's HP is `0`. `CheckBattleDefeat` (`0x08018304`, from
`PostActionBattleCheck` (`0x08018ACC`), run after every HP-affecting
action, and also called directly from state `2`'s post-poison-tick
check) pushes state `6` once every non-`Enemy` fighter's HP is `0`
(Buckbeak-only encounters check only Buckbeak). Defeat also fully heals
the party and sets `FightState->bDefeatWarpTarget` from a table indexed
by `g_abQuestEventState[0x10]`, resetting index `0` to `0x1F` -- new
territory for [`../formats/save.md`](../formats/save.md)'s
`abQuestEventState`, which so far only covers index `25` and `~224`-`254`.

State `6` calls `PushGameMode_2(Overworld, 0, bDefeatWarpTarget)` after a
150-tick delay; state `7` calls `PushGameMode(VictoryScreen)` after a
30-tick delay. `VictoryScreen` (`GameMode` `0x2C`) is an INIT/TICK/EXIT
mode-dispatch entry (`GameModeDispatchEntry_ARRAY_08065cbc`, stride
`0xC`) with two internal phases, both driven by `UpdateVictoryScreen`'s
(`0x080138F4`) own state byte: an XP phase (`InitializeVictoryXpScreen`/
`TickVictoryXpCounter`, rolling XP counter with level-up sound/animation)
then a drop phase (`InitializeVictoryDropScreen`, "The fleeing enemy
dropped:" plus up to 2 items from `RollBattleItemDrops` and the gold
total, see `bBonusRewardFlags` above). `ExitVictoryScreen`
(`0x080148A8`) returns to `Battle` mode. `g_dwBattleRewardFlagsSnapshot`
is set by `ExitBattle` (`0x0800DE50`, `Battle`'s mode-EXIT handler,
previously misidentified as a draw function), which tears down
`g_pFightState`. Reward granting itself goes through `GrantBattleReward`
(`0x08026DE0`).

### `TickBattleTurnStateMachine`'s 8 states

Each state's own handler follows the same one-shot-entry idiom: a
`dwStateJustEntered` flag (0x1064) is consumed on the tick a state is
first reached, and `wBattleStateTimer` (0x1068, u16) is a per-state
countdown whose meaning is local to that state.

- **0 -- idle.** Clears `dwStateJustEntered` and returns; a resting
  state with no timer of its own.
- **1 -- per-fighter turn-order advance.** On entry, calls
  `sub_080130B4(bActiveFighterIndex)`, advances
  `bActiveFighterIndex`, and starts a 16-tick timer; once it expires,
  waits for every fighter's `Object+0xA4` (UNCONFIRMED field) to clear,
  then transitions to state `2` once every fighter has acted, otherwise
  to state `4` (`Enemy`) or `3` (player) for the next active fighter.
- **2 -- end-of-round status tick, PROVEN as `EndOfRoundStatusTick`**
  (see "Poison's per-turn tick" below): on entry, ticks poison damage for
  every `Poisoned` fighter and starts a delay timer; once expired,
  resets `bActiveFighterIndex` to `0` and transitions to state `4`
  (`Enemy`) or `3` (player) for the round's first fighter.
- **3 -- player turn.** On entry, calls `RollFighterParalysisEscape`;
  if the fighter can't act, shows the escape/still-paralyzed message and
  transitions to state `5`, otherwise opens the battle menu
  (`OpenBattleTopMenu`). Once `TickBattleMenuInput` reports the menu
  selection resolved (`bMenuInputPending_candidate` clears), transitions
  to state `4`.
- **4 -- resolve the active fighter's action.** `Enemy` fighters draw the
  enemy panel (`DrawEnemyStatsUi_candidate`) and call `RollFighterParalysisEscape` (paralysis failure
  shows a message and transitions to state `5`), then set the fighter's
  animation state to `0x1a` (attack windup, see `TickPlayerActionState`'s
  own case `0x1a`); non-`Enemy` fighters call
  `DispatchPendingAction(bFighterType)` directly. Both paths transition
  to state `0`.
- **5 -- message-wait.** Waits 30 ticks (or until `0x01` (A) is set in
  `g_wKeysPressed`, `0x030034F0`, a fast-forward/skip input -- see
  `docs/memory-map/input.md`), then swaps `bBattleState` with
  `bSavedBattleState` -- resuming whichever state transitioned here.
- **6 -- defeat.** After a 150-tick delay, pushes `PushGameMode_2(Overworld,
  0, bDefeatWarpTarget)`.
- **7 -- victory.** After a 30-tick delay, pushes `PushGameMode(VictoryScreen)`.

## Player spell/action damage -- `ResolvePlayerAttack` (`0x08017C24`)

The Harry/Hermione/Ron damage path; `ResolveEnemyAttack` is proven
enemy-only. Named for the attacker side (all three cast spells, keyed off
`bSpellId`/`bSpellLevel`) rather than "melee vs. spell", which is the
split actually enforced in code.

### `BattleFighter+0xE` (`bLevel`), PROVEN

Read twice by `ResolvePlayerAttack`: as the term multiplying
`g_awSpellPowerScale[idx]` (divided by 9) into base power, and (`>>1`,
capped at 12) as the spell crit-chance scale. `ResolveEnemyAttack` never
reads it; no monster ever becomes `ResolvePlayerAttack`'s attacker, so a
monster's own value has no confirmed reader.

**Leveling.** `LevelUpFighter_candidate` (`0x080151B0`) increments
`bLevel` (capped at `99`), indexes a per-character, per-level stat table
with the new value, writes each row into the matching `BattleFighter`
fields, full-heals HP/MP, then calls
`ApplyEquipmentStatModifiers_candidate` (`0x08026870`) to reapply gear.
`RecomputeBaseStatsFromLevel_candidate` (`0x080150B4`) does the same
lookup for `bStat_speed`/defense without incrementing level (used when
only reapplying equipment; resets defense/`bMagicDefensePercent` to `100`
first). `GrantPartyLevelUps` (`0x0801D308`, PROVEN: its one caller is
identified) runs `LevelUpFighter_candidate` for all 3 party members,
`N` times, where `N` is a room-script opcode operand -- see
[`../formats/room_scripts.md`](../formats/room_scripts.md)'s opcode
`0x57`. A room script triggers party level-ups explicitly (e.g. a story
event), not an automatic threshold check against accumulated XP.

Three `CharacterLevelEntry[100]` tables, 12-byte rows, matched
byte-exact as curated C source (`src/data/harry_levels.c`,
`src/data/ron_levels.c`, `src/data/hermione_levels.c`):

| Table | US address |
|---|---|
| `g_pHarryLevelTable` | `0x0804FE50` |
| `g_pRonLevelTable` | `0x08050300` |
| `g_pHermioneLevelTable` | `0x080507B0` |

Row layout (12 bytes, last 2 always-zero padding): `wHp_max` (u16),
`wMp_max` (u16), `wXpDeltaForLevel` (u16), `bSpeed`,
`bAccuracy`, `bDefenseFactorPercent`,
`bMagicDefensePercent` (last two both dead in damage math -- see below).

`ApplyEquipmentStatModifiers_candidate` walks each party member's 6
equipped-item slots (`DAT_03003834`) and subtracts each item's
`nDefenseX2/2` (Def) from defense%, `dwMagicDefense` (M.Def)
from `bMagicDefensePercent`, and `nAgility` (Agi, signed) from
`bStat_speed` (clamped) -- heavier gear trades speed for defense. See
[`../formats/items.md`](../formats/items.md)'s "Equipment stats" section
for the full item-record field layout, including `nCharacterMask`, the
per-character equip-eligibility mask `CanFighterEquipItem` reads.

**Verified against real in-game data** (Harry Lvl7, Hermione Lvl8, Ron
Lvl5, no equipment):

- `bLevel` is 0-indexed -- displayed Level `N` is table row `N-1`.
- `wHp_max`/`wMp_max` match the row directly; displayed agility is
  `255 - bStat_speed`.
- **Displayed defense and magic-defense always read `0`**
  (`100 - 100`): `RecomputeBaseStatsFromLevel_candidate` resets both to
  `100` immediately after `LevelUpFighter_candidate` sets them from the
  table -- both table columns never take effect.
- Displayed next-level XP is the *cumulative* sum of
  `wXpDeltaForLevel` across rows `0..bLevel`, not any single
  row and not what `LevelUpFighter_candidate` writes into `wRewardXp` (a
  plain overwrite with the new row's delta alone). What compares real XP
  against that cumulative threshold isn't located.

**`bMagicDefensePercent` is display-only in damage math.** Tracked
identically to `bDefenseFactorPercent` (reset to `100`, reduced by gear,
shown as `100 - value`) and read by `DrawStatusEquipStatsPanel`
(`0x0803A0F0`) and `DrawEquipItemStatComparison` (`0x080364A8`) for the
"Magic Def" UI label, but neither damage formula reads it -- unlike
`bDefenseFactorPercent`, which `ResolveEnemyAttack` consumes directly.

**Player fighters get `bLevel` from `g_pPartyMasterStats_candidate`
(`0x030024EC`), not `MonsterTable`.** `InitPlayerBattleActor_candidate`
copies a persistent, `BattleFighter`-shaped 3-entry array (Harry/
Hermione/Ron) into the live roster: `bLevel`, `wHp`/`wHp_max`,
`wMp`/`wMp_max`, `bStat_speed`, `bAccuracy`, `bDefenseFactorPercent` --
settling that last field as player-only, never populated for monsters.
Buckbeak (`fighterType == 3`, outside the 3-entry array) gets hardcoded
defaults: `wHp`/`wMp_max` 400/999, `bLevel 0x32`, `bStat_speed 10`,
`bAccuracy 0x65`, `bDefenseFactorPercent 100`.

### `BattleFighter+0x3C`/`+0x3D` -- `bSpellId` (enum `SpellId`) / `bSpellLevel`

`bSpellLevel` (0-2) explains `ShowBattleMessage`'s `SpellLevelUp` case --
spells have 3 power tiers.

**`SpellId` has 10 values, PROVEN directly from the Cast Spell menu's own
name-lookup code** (`DrawBattleMenuText`, `0x08011520`: `spellId + 0x95F`
is the real dialog-text id for that spell, cross-checked against
`data/text/en_us.json` `2399`-`2408`):

| `SpellId` | Name |
|---|---|
| `0` | `Flipendo` |
| `1` | `Informus` |
| `2` | `Verdimillious` |
| `3` | `Diffindo` |
| `4` | `Incendio` |
| `5` | `WingardiumLeviosa` |
| `6` | `PetrificusTotalus` |
| `7` | `Glacius` |
| `8` | `Fumos` |
| `9` | `Spongify` |

`ResolvePlayerAttack`'s `aSpellEffectiveness` switch has no case for four
of these ids -- `Informus`/`PetrificusTotalus`/`Fumos`/`Spongify`, all
non-damage status spells, none of which compute a per-monster
effectiveness roll.

Do not conflate this enum with the Folio Bruti screen's own separate 0-7
spell ordering (see
[`../formats/folio_bruti.md`](../formats/folio_bruti.md)), which excludes
`Informus`/`Fumos` entirely since neither has a monster-resistance stat
to display.

### Spell power tables, decoded

`g_awSpellPowerBase` (`0x080538EC`) and `g_awSpellPowerScale`
(`0x08053928`), both `ushort[30]`, indexed `spellId*3 + spellLevel`.
`g_awSpellPowerScale` is multiplied by the attacker's `bLevel` and
divided by 9 (Thumb-mode signed division).

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

All four non-damage spells are `0`/`0` at every level, consistent with
never computing damage through this path.

### Spell MP cost -- `g_awSpellMpCost` (`0x08053964`), PROVEN

`ushort[30]`, same indexing. Deducted directly from `wMp` in
`ExecutePlayerAttackSequence` -- all spells share one MP pool. Matches a
community-written GameFAQs guide's real per-spell MP costs exactly,
including `PetrificusTotalus`'s `Uno`/`Duo` costs (`10`/`15`), which
independently proves `PetrificusTotalus = 6`.

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

`Informus` costing `0` at every level matches its in-game description
having no MP-cost callout. `Spongify`'s `10/0/0` matches `Diffindo`'s
identical shape -- both single-level-only spells (see `g_abSpellMaxLevel`
below).

Its companion byte array at the same index, `g_abSpellEffectId_candidate`
(`0x080538B0`), holds a per-`(spellId, level)` effect-script id fed into
`TriggerBattleEffect`. All 30 entries are named in
`tools/battle_scripts/script_names.json`:

| `SpellId` | Spell | Effect ids (Uno/Duo/Tria) | Max level | Has `StatusEffect`? |
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
| `9` | Spongify | 29 / 29 / 29 | 1 (see below) | yes (`AttackWeakened`) |

A spell can never be cast above its `g_abSpellMaxLevel`, so every effect
id at or past that level is dead table content: `Informus`/`Diffindo`/
`WingardiumLeviosa` never leave `Uno`; `PetrificusTotalus`/`Glacius`/
`Fumos` never reach `Tria`. Only the four non-damage spells carry a
`StatusEffect` opcode -- the other 13 scripts are pure cast animation;
their damage comes from `ResolvePlayerAttack`, not the bytecode.

### Spell familiarity/leveling -- `TrackSpellFamiliarity` (`0x08010008`), PROVEN

Called from `DispatchPendingAction`'s `None`/`Informus` cases (see
consolidated pseudocode above). `aSpellCastLevel`/`aSpellUsageProgress`
(`BattleFighter+0x10`/`+0x1A`, 10 bytes each, one per `SpellId`) are
confirmed bounded by `docs/formats/save.md`'s save-slot serializer, which
packs `BattleFighter+8`..`+0x23` as one contiguous 28-byte run per party
member. `g_abPartySpellUsage`/`g_abPartySpellLevel` are a separate
persistent (save-data) tracking array, one `0x48`-strided block (matching
`BattleFighter`'s own stride) per `FighterType`, only the first 8 bytes
of each block used (indexed by `SpellId`).

Two adjacent, non-overlapping tables in ROM: `g_abSpellMaxLevel` at
`0x0804e5e0`, 10 bytes; `g_abSpellLevelUpThreshold` immediately after at
`0x0804e5ea`, 2 bytes.

- **`g_abSpellMaxLevel[10]`** (indexed by `SpellId`):
  `[3,1,3,1,3,1,2,2,2,1]`. All 10 spells have a real entry, including
  `Spongify` (`SpellId` `9`, cap `1`, matching the single-level shape its
  MP cost implies -- `10/0/0`). `FUN_08012994` (the Ultimate MP
  unlock-all-spells payload) loops `spellId` `0`-`9` reading this table
  to populate every `aSpellCastLevel` entry at once.
- **`g_abSpellLevelUpThreshold[2]`**: `[25, 50]`, indexed by
  `aSpellCastLevel[spellId] - 1` (`TrackSpellFamiliarity`'s disassembly
  subtracts 1 from `*pCastLevel` before the table-base add). A spell
  starts at cast level `1` (Uno) automatically, no threshold needed to
  reach it; `Uno`->`Duo` takes 25
  uses, `Duo`->`Tria` takes 50.

`fighterType != Buckbeak` is an explicit gate in `TrackSpellFamiliarity`
-- Buckbeak never casts spells, so never tracks familiarity.

## `DispatchPendingAction` (`0x080100a0`), PROVEN

See the consolidated pseudocode above for the full switch. Two points of
note:

- **`SpecialMove` is not general spellcasting** -- it's exclusively the
  Special Move path (anim state `0x15`), and it's what sets
  `nHermioneSpecialMoveUsed`/`nRonSpecialMoveUsed` to `1`,
  disabling that menu entry for later turns (see
  [`battle-ui.md`](battle-ui.md)). A regular `Cast Spell` selection
  leaves `bPendingActionKind` at `None`. For Harry, `bSpellId` is
  overwritten with `g_nFolioUniversitasSlot` (the raw card slot, `0`-`15`)
  purely so the announce message can index by it -- not a real `SpellId`
  despite the field reuse (real ids stop at `9`, card slots run to `15`).
- **`Informus` has no special-case branch** -- it shares the `None` case
  outright, driving the same anim state and `TrackSpellFamiliarity` call
  an ordinary spell cast does. Its whole gameplay payload lives in its
  effect script: `g_abSpellEffectId_candidate[1]` = effect id `38`
  (`StatusEffect` case `0xC`, `BumpMonsterDocLevel`, the Folio Bruti
  populate action). Zero base power and zero MP cost at every level, so
  it deals no damage and needs no resource.
