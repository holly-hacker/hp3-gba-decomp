#include "types.h"
#include "background.h"
#include "color.h"
#include "combat_fighter.h"
#include "combat_fx.h"
#include "sound.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "modes.h"
#include "items.h"
#include "pscreen_folio_universitas.h"
#include "combat.h"
#include "mode7.h"

// Certain bAttackOutcomeState (Actor+0x60) values. States 1-5 stay numeric:
// their tails differ between cases 0x1a and 0x15, so no one name fits both.
typedef enum {
    AttackOutcome_None = 0,    // idle/reset: nothing pending
    AttackOutcome_Buckbeak = 6, // Buckbeak's level-scaled damage tail
} AttackOutcomeState;

static inline void PlayActionWindupFlash(Actor *actor)
{
    const u16 *ptr;
    s32 paletteBank;
    if ((actor->bActionFlags & 1) == 0)
        return;
    if (actor->wActionVariant == 1) {
        SetPlayerActorAnim(actor, 7);
        paletteBank = actor->oam.paletteNum;
        ptr = &g_aFighterAnimTable[actor->wActorType].aRecords[7].pPalette->aColors[1];
        QueueObjPaletteLoad(ptr, (paletteBank << 4) + 1, 0xf);
    } else if (actor->wActionVariant == 2) {
        SetPlayerActorAnim(actor, 6);
        paletteBank = actor->oam.paletteNum;
        ptr = &g_aFighterAnimTable[actor->wActorType].aRecords[6].pPalette->aColors[1];
        QueueObjPaletteLoad(ptr, (paletteBank << 4) + 1, 0xf);
    } else {
        SetPlayerActorAnim(actor, 0);
    }
    actor->bActionFlags &= 0xfe;
}

static inline void WaitForMoveThenApplyDamageNumber(Actor *actor)
{
    if (actor->vel.x != 0)
        return;
    if (actor->vel.y != 0)
        return;
    SetActorActionState(actor, 0);
}

static inline void ApplyDamageNumberAnimState(Actor *actor)
{
    if (actor->bActionFlags & 1) {
        sub_08018B14(actor->modeState.actor.wStagedDamage, (u8)actor->wActorType);
        PlaySoundById(0x9b);
        SetPlayerActorAnim(actor, 4);
        actor->bActionFlags &= 0xfe;
    }

    // Damage remains staged until the hit animation signals completion.
    if ((actor->dwFlags & ActorFlagActionAnimDone) == 0)
        return;

    SetActorActionState(actor, 0);
    ApplyDamageToAllyFighter(actor->modeState.actor.wStagedDamage, actor->bFighterIndex);
}

static inline void PlayFighterImpactSound(Actor *actor)
{
    if ((actor->bActionFlags & 1) == 0)
        return;
    switch (actor->wActorType) {
    case 0: PlaySoundById(0xa1); break;
    case 1: PlaySoundById(0xa7); break;
    case 2: PlaySoundById(0xa4); break;
    case 3: PlaySoundById(0x39); break;
    }
    SetPlayerActorAnim(actor, 8);
    actor->bActionFlags &= 0xfe;
    PlaySoundById(0x9c);
}

static inline void ReturnFighterToPosition(Actor *actor)
{
    if (actor->bActionFlags & 1) {
        actor->bActionFlags &= 0xfe;
        actor->dwStateTimer = 0x1e;
        SetActorFlippedX(actor, 1);
        return;
    }
    actor->dwStateTimer -= 1;
    if (actor->dwStateTimer != 0)
        return;
    ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
    SetActorFlippedX(actor, 0);
    SetActorActionState(actor, 0);
    PushBattleState(1);
}

void TickPlayerActionState(Actor *actor)
{
    u8 state;
    s32 var_8 = -1;  // unconditionally initialized at entry (real: str r0,[sp,#8] right after prologue); only case 0x1a ever reads it back

    if (g_pFightState->bScreenShakeTimer_candidate == 0) {
        ClearActorOrbit(actor);
    } else {
        if (g_pFightState->bScreenShakeTimer_candidate > 0xf)
            SetActorFlippedX(actor, 1);
        else
            SetActorFlippedX(actor, 0);
    }

    state = actor->bActionState;
    switch (state) {
    /* physical ROM order matters here: agbcc emits case bodies in source
     * order, not numeric case-value order, so this switch's case labels are
     * deliberately listed in the same order their bodies appear in the real
     * ROM (0, 0xf, 2, 0x1a, 0x15, 4, 1, 5), not ascending by value. */
    case 0:
        PlayActionWindupFlash(actor);
        return;
    case 0xf:
        WaitForMoveThenApplyDamageNumber(actor);
        return;
    case 2:
        ApplyDamageNumberAnimState(actor);
        return;
    case 0x1a: // ExecutePlayerAttackSequence?
    {
        // bAttackOutcomeState tails, checked in order below: 1 shows the
        // damage number, 2 resolves item use, 3 applies staged damage,
        // 4 sweeps faints and victory, 5 latches the target and finishes.
        // Buckbeak rides this same dispatch but bypasses the spell machinery
        // at four carve-outs (marked below): no special-move effect, state
        // Buckbeak instead of ResolvePlayerAttack, no cast VFX trigger, and
        // level-scaled damage in the state-Buckbeak tail.
        s16 flags;
        u8 phase, delay, i;
        // Real loads *g_pFightState once before testing bActionFlags and uses
        // that value in both the 0x21 and 0x41 arms, so it is a single local.
        FightState *fs = g_pFightState;

        flags = actor->bActionFlags;
        if (flags == 0x21) {
            if (fs->dwPlayerActionActive_candidate == 0)
                sub_08012A38();
            DrawFighterStatsUi_candidate(ACTIVE_FIGHTER.bFighterType, 0);
            if (ACTIVE_FIGHTER.bSpellId == Fumos) {
                actor->bActionFlags = 1;
                return;
            }
            g_pFightState->bActionDelayCounter_candidate = 0x12;
            for (i = 0; i < g_pFightState->bFighterCount; i++) {
                if (g_pFightState->pFighters[i].bFighterType != Enemy)
                    SetActorVelocity(g_pFightState->pFighters[i].pActor, 0xFFFF0000, 0x25000);
                else
                    SetActorVelocity(g_pFightState->pFighters[i].pActor, 0x8000, 0x15000);
            }
            for (i = 0; i < g_pFightState->bPendingFighterCount_candidate; i++)
                SetActorVelocity(g_pFightState->pPendingFighters_candidate[i].pActor, 0xFFFF0000, 0x25000);
            actor->bActionFlags &= 0xfe;
            SetFloorForwardSpeed(0x250);
        } else if (flags == 0x41) {
            if (fs->pFighters[fs->bActiveFighterIndex].bSpellId == Fumos) {
                actor->bActionState = 0;
                actor->bActionFlags |= 1;
                fs->pFighters[fs->bActiveFighterIndex].bSelectedActionIndex = 0xff;
                PostActionBattleCheck();
                return;
            }
            fs->bActionDelayCounter_candidate = 0x13;
            StartActorMove(actor, g_pFightState->savedPos.x, g_pFightState->savedPos.y, 3);
            actor->bActionFlags &= 0xfe;
        }

        flags = actor->bActionFlags;
        phase = flags & 0x20;
        // The phase!=0 chain re-reads bActionDelayCounter_candidate from the
        // struct at each comparison; only the flags&0x40 chain below keeps it
        // in the delay local. Caching it here too puts delay in r1 function-
        // wide and mismatches the flags&0x40 reread (real r0, 0x08016528).
        if (phase != 0) {
            g_pFightState->bActionDelayCounter_candidate -= 1;
            if (g_pFightState->bActionDelayCounter_candidate > 4) {
                SetFloorHeading((u8)(g_FloorEffect.bHeading - 1));
                g_BgState.aLayers[1].scroll.x += 0xFFFD0000;
                g_pFightState->bWallEndLine += 1;
            } else if (g_pFightState->bActionDelayCounter_candidate == 4) {
                SetFloorForwardSpeed(0);
            } else if (g_pFightState->bActionDelayCounter_candidate == 3) {
                for (i = 0; i < g_pFightState->bFighterCount; i++) {
                    SetActorVelocity(g_pFightState->pFighters[i].pActor, 0, 0);
                    ClearActorOrbit(g_pFightState->pFighters[i].pActor);
                }
                for (i = 0; i < g_pFightState->bPendingFighterCount_candidate; i++) {
                    SetActorVelocity(g_pFightState->pPendingFighters_candidate[i].pActor, 0, 0);
                    ClearActorOrbit(g_pFightState->pPendingFighters_candidate[i].pActor);
                }
                // Real emits an 8-byte block move (ldr/ldr/str/str off one
                // base each side), not two independent field stores.
                g_pFightState->savedPos = actor->pos;
                StartActorMove(actor, 0xb00000, 0x720000, 3);
                return;
            } else if (g_pFightState->bActionDelayCounter_candidate != 0) {
                return;
            } else {
                SetActorVelocity(actor, 0, 0);
                actor->bActionFlags = 1;
                return;
            }
        } else if (flags & 0x40) {
            g_pFightState->bActionDelayCounter_candidate -= 1;
            delay = g_pFightState->bActionDelayCounter_candidate;
            if (delay > 0xe) {
                return;
            } else if (delay == 0xe) {
                SnapActorPosition(actor, g_pFightState->savedPos.x, g_pFightState->savedPos.y);
                actor->wMoveDuration = 0;
                actor->wTimedMoveTicks = 0;
                for (i = 0; i < g_pFightState->bFighterCount; i++) {
                    if (g_pFightState->pFighters[i].bFighterType != Enemy) {
                        SetActorVelocity(g_pFightState->pFighters[i].pActor, 0x10000, 0xFFFDB000);
                        SetActorOrbitX(g_pFightState->pFighters[i].pActor, 0, (s16)0xFFFFFC00, 0xc);
                    } else {
                        SetActorVelocity(g_pFightState->pFighters[i].pActor, 0xFFFF8000, 0xFFFEB000);
                        SetActorOrbitX(g_pFightState->pFighters[i].pActor, 0, (s16)0xFFFFFC00, 0xc);
                    }
                }
                for (i = 0; i < g_pFightState->bPendingFighterCount_candidate; i++) {
                    SetActorVelocity(g_pFightState->pPendingFighters_candidate[i].pActor, 0x10000, 0xFFFDB000);
                    SetActorOrbitX(g_pFightState->pPendingFighters_candidate[i].pActor, 0, (s16)0xFFFFFC00, 0xc);
                }
                SetFloorForwardSpeed((s16)0xFFFFFDB0);
                actor->bActionFlags &= 0xfe;
            } else if (delay == 0) {
                for (i = 0; i < g_pFightState->bFighterCount; i++) {
                    SetActorVelocity(g_pFightState->pFighters[i].pActor, 0, 0);
                    ClearActorOrbit(g_pFightState->pFighters[i].pActor);
                }
                for (i = 0; i < g_pFightState->bPendingFighterCount_candidate; i++) {
                    SetActorVelocity(g_pFightState->pPendingFighters_candidate[i].pActor, 0, 0);
                    ClearActorOrbit(g_pFightState->pPendingFighters_candidate[i].pActor);
                }
                SetFloorForwardSpeed(0);
                actor->bActionState = 0;
                actor->bActionFlags |= 1;
                PostActionBattleCheck();
                if (ACTIVE_FIGHTER.bSpellId == Informus)
                    PushGameMode_2(FolioBruti, 0, g_bInformusTargetMonster);
                ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
                return;
            } else {
                SetFloorHeading((u8)(g_FloorEffect.bHeading + 1));
                g_BgState.aLayers[1].scroll.x += 0x30000;
                g_pFightState->bWallEndLine -= 1;
            }
        } else if (flags & 1) {
            SetPlayerActorAnim(actor, 1);
            actor->bActionFlags &= 0xfe;
            if (ACTIVE_FIGHTER.bSpellId == Fumos) {
                if (g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]].stats.wHp == 0) {
                    i = 0;
                    while (g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[i]].stats.wHp == 0 ||
                           g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[i]].bFighterType == Enemy)
                        i++;
                    ACTIVE_FIGHTER.bSelectedActionIndex = i;
                }
            } else {
                if (g_pFightState->aEnemySlotTurnOrderIndex[
                        ACTIVE_FIGHTER.bSelectedActionIndex] == 0xff) {
                    i = 0;
                    while (g_pFightState->aEnemySlotTurnOrderIndex[i] == 0xff)
                        i++;
                    ACTIVE_FIGHTER.bSelectedActionIndex = i;
                }
            }
        }

        if (actor->dwFlags & 0x8000) {
            // Buckbeak carve-out 1/4: skips the special-move effect; the flag
            // clear below still runs.
            if (actor->wActorType != Buckbeak)
                TriggerBattleEffect(1, ACTIVE_FIGHTER.bSlotParam,
                                    0, g_pFightState->bActiveFighterIndex, 0, 0);
            actor->dwFlags &= 0xffff7fff;
        }
        if (actor->dwFlags & 0x40000) {
            actor->dwFlags &= 0xfffbffff;
            if (actor->wActorType != Buckbeak) {
                var_8 = g_abSpellEffectScriptId[ACTIVE_FIGHTER.bSpellId][ACTIVE_FIGHTER.bSpellLevel];
                ACTIVE_FIGHTER.stats.wMp -= g_awSpellMpCost[ACTIVE_FIGHTER.bSpellId][ACTIVE_FIGHTER.bSpellLevel];
                g_aPartyMasterStats[ACTIVE_FIGHTER.bFighterType].stats.wMp = ACTIVE_FIGHTER.stats.wMp;
                if (ACTIVE_FIGHTER.bSelectedActionIndex != 0xfe)
                    // apply player attack
                    g_nLastDamage = ResolvePlayerAttack(
                        g_pFightState->bActiveFighterIndex,
                        g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
                DrawFighterStatsUi_candidate(g_pFightState->pFighters[g_pFightState->bMenuFighterIndex].bFighterType, 0);
            } else {
                // Buckbeak carve-out 2/4: Buckbeak does not roll the normal damage formula
                actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_Buckbeak;
            }

            if (ACTIVE_FIGHTER.bSpellId == Fumos) {
                TriggerBattleEffect(var_8, ACTIVE_FIGHTER.bSlotParam, ACTIVE_FIGHTER.bSelectedActionIndex,
                                    g_pFightState->bActiveFighterIndex,
                                    g_pFightState->aAllySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex],
                                    g_nLastDamage);
            } else if (actor->wActorType != Buckbeak) {
                // Buckbeak carve-out 3/4: Fumos has no fighter check, so it still
                // triggers; every other spell skips the cast VFX for Buckbeak.
                if (ACTIVE_FIGHTER.bSelectedActionIndex != 0xfe)
                    TriggerBattleEffect(var_8, ACTIVE_FIGHTER.bSlotParam, (u8)(ACTIVE_FIGHTER.bSelectedActionIndex + 3),
                                        g_pFightState->bActiveFighterIndex,
                                        g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex],
                                        g_nLastDamage);
                else
                    TriggerBattleEffect(var_8, ACTIVE_FIGHTER.bSlotParam, (u8)(ACTIVE_FIGHTER.bSelectedActionIndex + 3),
                                        g_pFightState->bActiveFighterIndex, 0, 0);
            }
        }

        // Real re-reads the attack outcome byte at every test rather than
        // caching it in one register, so this chain must not use a local.
        if (actor->scriptState.bytes.bAttackOutcomeState == 1) {
            g_pFightState->pAttackAnimActor_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            if (g_nLastDamage == 0)
                return;
            ShowDamageNumber_candidate(g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex],
                         g_nLastDamage);
            return;
        }
        if (actor->scriptState.bytes.bAttackOutcomeState == 2) {
            ShowItemUseResult(actor, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
            return;
        }
        if (actor->scriptState.bytes.bAttackOutcomeState == 3) {
            g_pFightState->pAttackAnimActor_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            actor->bActionFlags = 0x41;
            ApplyDamageToEnemyFighter(g_nLastDamage,
                                 g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
            g_bLastTargetIndex = ACTIVE_FIGHTER.bSelectedActionIndex;
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            return;
        }
        if (actor->scriptState.bytes.bAttackOutcomeState == 4) {
            g_pFightState->pAttackAnimActor_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            g_pFightState->bFaintMessageCount_candidate = 0;
            for (i = 0; i < g_pFightState->bFighterCount; i++) {
                if (g_pFightState->pFighters[i].bFighterType != Enemy)
                    continue;
                g_nLastDamage = ResolvePlayerAttack(g_pFightState->bActiveFighterIndex, i);
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = g_nLastDamage;
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bEffectId = (u8)((Actor *)g_pFightState->pFighters[i].pActor)->wActorType;
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bFlag = 0;
                g_pFightState->bFaintMessageCount_candidate += 1;
                SetActorActionState(g_pFightState->pFighters[i].pActor, 2);
                if (g_nLastDamage > 999) {
                    g_nLastDamage -= 999;
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 3, i, 0); // crit
                } else if (g_nLastDamage != 0) {
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, i, 0); // normal
                } else {
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 2, i, 0); // miss
                }
                ApplyDamageToEnemyFighter(g_nLastDamage, i);
            }
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            actor->bActionFlags = 0x41;
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            if (g_pFightState->dwBattleResultPending != 0)
                return;
            ShowBattleMessage(FaintResult, 0, 0);
            return;
        }
        if (actor->scriptState.bytes.bAttackOutcomeState == 5) {
            g_pFightState->pAttackAnimActor_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            actor->bActionFlags = 0x41;
            g_bLastTargetIndex = ACTIVE_FIGHTER.bSelectedActionIndex;
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            return;
        }
        // Buckbeak carve-out 4/4: level-scaled damage, computed here rather
        // than in ResolvePlayerAttack: (HarryLevel >> 1) + 30, x4/3 under
        // SpellPowerBoost. Presented via the attack-result message plus a
        // floating number, never ShowDamageNumber.
        if (actor->scriptState.bytes.bAttackOutcomeState == AttackOutcome_Buckbeak) {
            PlaySoundById(0x37);
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;

            g_nLastDamage = (g_aPartyMasterStats[Harry].stats.bLevel >> 1) + 30;
            if (ACTIVE_FIGHTER.bStatusFlags & SpellPowerBoost)
                g_nLastDamage = (g_nLastDamage * 4) / 3;

            SetActorActionState(
                g_pFightState->pFighters[g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]].pActor,
                2);

            ShowBattleMessage(AttackResult, g_nLastDamage, 0);

            if (g_pFightState->bPendingStatusMessageVariant_candidate != NO_PENDING_STATUS_MESSAGE_VARIANT)
                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant_candidate);

            ShowFloatingDamageNumber_candidate(g_nLastDamage, 0,
                         g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);

            actor->bActionFlags = 0x41;

            ApplyDamageToEnemyFighter(g_nLastDamage,
                                 g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);

            g_bLastTargetIndex = ACTIVE_FIGHTER.bSelectedActionIndex;
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
        }
        return;
    }
    case 0x15: // HandleScriptedDamageEvent_candidate?
    {
        FighterType fighterType;
        u8 activeIdx, cardMeta, effectId, slotParam, selActionIdx, targetIdx;
        u8 i;

        if (actor->bActionFlags & 1) {
            SetPlayerActorAnim(actor, 2);
            actor->bActionFlags &= 0xfe;
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            if (ACTIVE_FIGHTER.bFighterType == Harry)
                actor->dwStateTimer = 0x3c;
            else
                actor->dwStateTimer = 0x28;
        }
        if (actor->dwStateTimer != 0) {
            actor->dwStateTimer -= 1;
            if (actor->dwStateTimer == 0) {
                if (ACTIVE_FIGHTER.bFighterType == Harry)
                    ShowBattleMessage(SpecialAbilityText, g_nFolioUniversitasSlot & 0xffff, 0);
                else
                    ShowBattleMessage(SpecialAbilityText, ACTIVE_FIGHTER.bSpellId, 0);
            }
        }
        if (actor->dwFlags & 0x40000) {
            actor->dwFlags &= 0xfffbffff;
            fighterType = ACTIVE_FIGHTER.bFighterType;
            if (fighterType == Harry) {
                if (g_pFightState->bFolioComboFirstCard != 0xff) {
                    DecrementFolioUniversitasCard(g_pFightState->bFolioComboFirstCard);
                    DecrementFolioUniversitasCard(g_pFightState->bFolioComboFirstCard + 1);
                }
                SetPlayerActorAnim(actor, 0);
                /* Throughout this case: the real code re-reads
                 * g_pFightState->bActiveFighterIndex (and the fighter fields
                 * indexed by it) at each use instead of caching the index in a
                 * register across the calls, so ACTIVE_FIGHTER is spelled out
                 * per use rather than routed through `activeIdx`. */
                cardMeta = g_aCardTargetingMeta[g_nFolioUniversitasSlot][0];
                if (cardMeta == 2) {
                    selActionIdx = g_pFightState->pFighters[g_pFightState->bActiveFighterIndex].bSelectedActionIndex;
                    if (g_pFightState->aAllySlotTurnOrderIndex[selActionIdx] == 0xff) {
                        i = 0;
                        while (g_pFightState->aAllySlotTurnOrderIndex[i] == 0xff)
                            i++;
                        ACTIVE_FIGHTER.bSelectedActionIndex = i;
                    }
                    TriggerBattleEffect(g_abHarryCardEffectId[g_nFolioUniversitasSlot],
                                         ACTIVE_FIGHTER.bSlotParam,
                                         ACTIVE_FIGHTER.bSelectedActionIndex,
                                         g_pFightState->bActiveFighterIndex,
                                         g_pFightState->aAllySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex],
                                         0);
                    activeIdx = g_pFightState->bActiveFighterIndex;
                } else if (cardMeta == 3) {
                    TriggerBattleEffect(g_abHarryCardEffectId[g_nFolioUniversitasSlot],
                                         ACTIVE_FIGHTER.bSlotParam,
                                         g_pFightState->pPendingFighters_candidate[ACTIVE_FIGHTER.bSelectedActionIndex].bSlotParam,
                                         g_pFightState->bActiveFighterIndex,
                                         ACTIVE_FIGHTER.bSelectedActionIndex, 0);
                } else {
                    if (cardMeta != 0) {
                        activeIdx = g_pFightState->bActiveFighterIndex;
                        selActionIdx = g_pFightState->pFighters[activeIdx].bSelectedActionIndex;
                        if (g_pFightState->aEnemySlotTurnOrderIndex[selActionIdx] == 0xff) {
                            i = 0;
                            while (g_pFightState->aEnemySlotTurnOrderIndex[i] == 0xff)
                                i++;
                            ACTIVE_FIGHTER.bSelectedActionIndex = i;
                        }
                    }
                    effectId = g_abHarryCardEffectId[g_nFolioUniversitasSlot];
                    slotParam = ACTIVE_FIGHTER.bSlotParam;
                    TriggerBattleEffect(effectId, slotParam, (u8)(ACTIVE_FIGHTER.bSelectedActionIndex + 3),
                                         g_pFightState->bActiveFighterIndex,
                                         g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
                }
            } else if (fighterType == Hermione) {
                activeIdx = g_pFightState->bActiveFighterIndex;
                selActionIdx = g_pFightState->pFighters[activeIdx].bSelectedActionIndex;
                if (g_pFightState->aAllySlotTurnOrderIndex[selActionIdx] == 0xff) {
                    i = 0;
                    while (g_pFightState->aAllySlotTurnOrderIndex[i] == 0xff)
                        i++;
                    ACTIVE_FIGHTER.bSelectedActionIndex = i;
                }
                TriggerBattleEffect(g_abHermioneLectureEffectId[ACTIVE_FIGHTER.bSpellId],
                                     ACTIVE_FIGHTER.bSlotParam,
                                     ACTIVE_FIGHTER.bSelectedActionIndex,
                                     g_pFightState->bActiveFighterIndex,
                                     g_pFightState->aAllySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex],
                                     0);
            } else {
                SetPlayerActorAnim(actor, 0);
            }
        }
        if (actor->dwFlags & 0x8000) {
            selActionIdx = ACTIVE_FIGHTER.bSelectedActionIndex;
            if (g_pFightState->aEnemySlotTurnOrderIndex[selActionIdx] == 0xff) {
                i = 0;
                while (g_pFightState->aEnemySlotTurnOrderIndex[i] == 0xff)
                    i++;
                ACTIVE_FIGHTER.bSelectedActionIndex = i;
            }
            actor->dwFlags &= 0xffff7fff;
            TriggerBattleEffect(g_abSpecialMoveEffectId[ACTIVE_FIGHTER.bSpellId],
                                 ACTIVE_FIGHTER.bSlotParam,
                                 (u8)(ACTIVE_FIGHTER.bSelectedActionIndex + 3),
                                 g_pFightState->bActiveFighterIndex,
                                 g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
        }
        if (actor->scriptState.bytes.bAttackOutcomeState == 1) {
            g_pFightState->pAttackAnimActor_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            if (ACTIVE_FIGHTER.bFighterType == Harry &&
                g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
                StopBgTileAnimationsAfterCard_candidate();
            sub_08012B40();
            PostActionBattleCheck();
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            SetActorActionState(actor, 0);
            PostActionBattleCheck();
        }
        if (actor->scriptState.bytes.bAttackOutcomeState == 2) {
            g_pFightState->pAttackAnimActor_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            if (g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
                StopBgTileAnimationsAfterCard_candidate();
            sub_08012B40();
            g_nLastDamage = 5;
            SetActorActionState(g_pFightState->pFighters[g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]].pActor, 2);
            ShowBattleMessage(AttackResult, g_nLastDamage, 0);
            if (g_pFightState->bPendingStatusMessageVariant_candidate != NO_PENDING_STATUS_MESSAGE_VARIANT)
                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
            ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
            ApplyDamageToEnemyFighter(g_nLastDamage, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
            PostActionBattleCheck();
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            SetActorActionState(actor, 0);
        }
        if (actor->scriptState.bytes.bAttackOutcomeState == 3) {
            g_pFightState->pAttackAnimActor_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            if (g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
                StopBgTileAnimationsAfterCard_candidate();
            sub_08012B40();
            g_nLastDamage = 0x14;
            SetActorActionState(g_pFightState->pFighters[g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]].pActor, 2);
            ShowBattleMessage(AttackResult, g_nLastDamage, 0);
            if (g_pFightState->bPendingStatusMessageVariant_candidate != NO_PENDING_STATUS_MESSAGE_VARIANT)
                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
            ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
            ApplyDamageToEnemyFighter(g_nLastDamage, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
            PostActionBattleCheck();
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            SetActorActionState(actor, 0);
        }
        if (actor->scriptState.bytes.bAttackOutcomeState == 4) {
            g_pFightState->pAttackAnimActor_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            if (g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
                StopBgTileAnimationsAfterCard_candidate();
            sub_08012B40();
            g_nLastDamage = 0x14;
            g_pFightState->bFaintMessageCount_candidate = 0;
            for (i = 0; i < g_pFightState->bFighterCount; i++) {
                if (g_pFightState->pFighters[i].bFighterType == Enemy) {
                    SetActorActionState(g_pFightState->pFighters[i].pActor, 2);
                    g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bEffectId = ((Actor *)g_pFightState->pFighters[i].pActor)->wActorType;
                    g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bFlag = 0;
                    g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = g_nLastDamage;
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, i, 0);
                    ApplyDamageToEnemyFighter(g_nLastDamage, i);
                    g_pFightState->bFaintMessageCount_candidate += 1;
                }
            }
            /* Re-stored after the loop: real emits the store twice, and the
             * intervening calls make actor->scriptState.bytes.bAttackOutcomeState unprovably
             * unchanged, so neither store folds away. */
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            ShowBattleMessage(FaintResult, 0, 0);
            PostActionBattleCheck();
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            if (actor->bActionState == 0x15)
                SetActorActionState(actor, 0);
        }
        if (actor->scriptState.bytes.bAttackOutcomeState != 5)
            return;
        if (g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
            StopBgTileAnimationsAfterCard_candidate();
        sub_08012B40();
        g_pFightState->bFaintMessageCount_candidate = 0;
        for (i = 0; i < g_pFightState->bFighterCount; i++) {
            g_nLastDamage = 0x2d;
            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bEffectId = ((Actor *)g_pFightState->pFighters[i].pActor)->wActorType;
            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bFlag = 0;
            if (g_pFightState->pFighters[i].bFighterType == Enemy) {
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = g_nLastDamage;
                ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, i, 0);
                ShowDamageNumber_candidate(i, g_nLastDamage);
                ApplyDamageToEnemyFighter(g_nLastDamage, i);
            } else {
                if (g_pFightState->pFighters[i].stats.wHp <= 0xf)
                    g_nLastDamage = g_pFightState->pFighters[i].stats.wHp - 1;
                else
                    g_nLastDamage = 0xf;
                ((Actor *)g_pFightState->pFighters[i].pActor)->modeState.actor.wStagedDamage = g_nLastDamage;
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = g_nLastDamage;
                ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, i, 0);
                ShowDamageNumber_candidate(i, g_nLastDamage);
            }
            g_pFightState->bFaintMessageCount_candidate += 1;
        }
        g_pFightState->pAttackAnimActor_candidate = 0;
        g_pFightState->bAttackAnimState_candidate = 0;
        actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
        ShowBattleMessage(FaintResult, 0, 0);
        PostActionBattleCheck();
        ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
        if (actor->bActionState != 0x15)
            return;
        SetActorActionState(actor, 0);
        return;
    }
    case 4: // ApplyStatusRestoreItemEffect?
    {
        u32 result;
        s32 targetIdx, code;
        u16 amount;

        if (actor->bActionFlags & 1) {
            actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;
            SetPlayerActorAnim(actor, 3);
            actor->bActionFlags &= 0xfe;
            actor->dwStateTimer = 0x1e;
        }
        if (actor->dwFlags & 0x40000) {
            actor->dwFlags &= 0xfffbffff;
            result = GetPotionEffect(ACTIVE_FIGHTER.bSpellLevel);
            switch (result) {
            case 1:
                TriggerBattleEffect(8, ACTIVE_FIGHTER.bSlotParam, ACTIVE_FIGHTER.bSelectedActionIndex, g_pFightState->bActiveFighterIndex, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
                break;
            case 2:
                TriggerBattleEffect(0x3e, ACTIVE_FIGHTER.bSlotParam, ACTIVE_FIGHTER.bSelectedActionIndex, g_pFightState->bActiveFighterIndex, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
                break;
            case 4:
                TriggerBattleEffect(0x3f, ACTIVE_FIGHTER.bSlotParam, ACTIVE_FIGHTER.bSelectedActionIndex, g_pFightState->bActiveFighterIndex, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
                break;
            case 3:
                TriggerBattleEffect(0x40, ACTIVE_FIGHTER.bSlotParam, ACTIVE_FIGHTER.bSelectedActionIndex, g_pFightState->bActiveFighterIndex, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
                break;
            }
        }
        actor->dwStateTimer -= 1;
        if (actor->dwStateTimer == 0) {
            ShowBattleMessage(StatusRestore, ACTIVE_FIGHTER.bSpellLevel, 0);
        }
        if (actor->scriptState.bytes.bAttackOutcomeState == AttackOutcome_None)
            return;

        g_pFightState->pAttackAnimActor_candidate = 0;
        g_pFightState->bAttackAnimState_candidate = 0;
        actor->scriptState.bytes.bAttackOutcomeState = AttackOutcome_None;

        {
            u8 spellLevel = ACTIVE_FIGHTER.bSpellLevel;
            u8 fighterIndex = g_pFightState->aAllySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex];

            result = GetPotionEffect(spellLevel);
            switch (result) {
            case 1: {
                s32 x = GetPotionMagnitude(spellLevel);
                amount = sub_080152CC(x, fighterIndex);
                ShowFloatingDamageNumber_candidate(amount, 0xd, fighterIndex, 1);
                code = 9;
                ShowBattleMessage(code, amount, 0);
                break;
            }
            case 2: {
                s32 x = GetPotionMagnitude(spellLevel);
                amount = sub_08015334(x, fighterIndex);
                ShowFloatingDamageNumber_candidate(amount, 6, fighterIndex, 1);
                code = 0xa;
                ShowBattleMessage(code, amount, 0);
                break;
            }
            case 3:
                ClearPoisonedFighter_candidate(fighterIndex);
                break;
            case 4:
                ClearParalyzedFighter_candidate(fighterIndex);
                break;
            }
        }

        ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
        SetActorActionState(actor, 0);
        SetPlayerActorAnim(actor, 0);
        PostActionBattleCheck();
        ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
        actor->bActionFlags &= 0xfe;
        return;
    }
    case 1:
        PlayFighterImpactSound(actor);
        return;
    case 5:
        ReturnFighterToPosition(actor);
        return;
    case 3:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    default:
        return;
    }
}
