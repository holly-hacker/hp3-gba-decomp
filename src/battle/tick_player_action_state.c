#include "types.h"
#include "battle.h"
#include "game_modes.h"

typedef struct Vec2 {
    u32 x, y;
} Vec2;

// Certain bAttackOutcomeState (Object+0x60) values. States 1-5 stay numeric:
// their tails differ between cases 0x1a and 0x15, so no one name fits both.
typedef enum {
    AttackOutcome_None = 0,    // idle/reset: nothing pending
    AttackOutcome_Buckbeak = 6, // Buckbeak's level-scaled damage tail
} AttackOutcomeState;

void TickPlayerActionState(Object *obj)
{
    u8 state;
    s32 var_8 = -1;  // unconditionally initialized at entry (real: str r0,[sp,#8] right after prologue); only case 0x1a ever reads it back

    if (g_pFightState->bScreenShakeTimer_candidate == 0) {
        sub_080039E8(obj);
    } else {
        if (g_pFightState->bScreenShakeTimer_candidate > 0xf)
            SetObjectFlippedX(obj, 1);
        else
            SetObjectFlippedX(obj, 0);
    }

    state = obj->bActionState;
    switch (state) {
    /* physical ROM order matters here: agbcc emits case bodies in source
     * order, not numeric case-value order, so this switch's case labels are
     * deliberately listed in the same order their bodies appear in the real
     * ROM (0, 0xf, 2, 0x1a, 0x15, 4, 1, 5), not ascending by value. */
    case 0: // PlayActionWindupFlash?
    {
        void *ptr;
        s32 slot;
        if ((obj->bActionFlags & 1) == 0)
            return;
        if (obj->wActionVariant == 1) {
            SetPlayerObjectAnim(obj, 7);
            slot = obj->bGfxSlotAndFlags >> 4;
            ptr = (u8 *)g_aFighterAnimTable[obj->wFighterType].pWindupResourceA + 2;
            sub_0800D264(ptr, (slot << 4) + 1, 0xf);
        } else if (obj->wActionVariant == 2) {
            SetPlayerObjectAnim(obj, 6);
            slot = obj->bGfxSlotAndFlags >> 4;
            ptr = (u8 *)g_aFighterAnimTable[obj->wFighterType].pWindupResourceB + 2;
            sub_0800D264(ptr, (slot << 4) + 1, 0xf);
        } else {
            SetPlayerObjectAnim(obj, 0);
        }
        obj->bActionFlags &= 0xfe;
        return;
    }
    case 0xf: // WaitForMoveThenApplyDamageNumber?
        if (obj->nVelX != 0)
            return;
        if (obj->nVelY != 0)
            return;
        SetFighterAttackAnimState_candidate(obj, 0);
        return;
    case 2: // ApplyDamageNumberAnimState?
        if (obj->bActionFlags & 1) {
            sub_08018B14(obj->wStagedDamage, (u8)obj->wFighterType);
            PlaySoundById(0x9b);
            SetPlayerObjectAnim(obj, 4);
            obj->bActionFlags &= 0xfe;
        }
        if ((obj->dwFlags & 0x40000) == 0)
            return;
        SetFighterAttackAnimState_candidate(obj, 0);
        ApplyStatusDamageToFighter_candidate(obj->wStagedDamage, obj->bFighterIndex);
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

        flags = obj->bActionFlags;
        if (flags == 0x21) {
            if (fs->dwPlayerActionActive_candidate == 0)
                sub_08012A38();
            DrawFighterStatsUi_candidate(ACTIVE_FIGHTER.bFighterType, 0);
            if (ACTIVE_FIGHTER.bSpellId == Fumos) {
                obj->bActionFlags = 1;
                return;
            }
            g_pFightState->bActionDelayCounter_candidate = 0x12;
            for (i = 0; i < g_pFightState->bFighterCount; i++) {
                if (g_pFightState->pFighters[i].bFighterType != Enemy)
                    sub_080019C0(g_pFightState->pFighters[i].pObject, 0xFFFF0000, 0x25000);
                else
                    sub_080019C0(g_pFightState->pFighters[i].pObject, 0x8000, 0x15000);
            }
            for (i = 0; i < g_pFightState->bPendingFighterCount_candidate; i++)
                sub_080019C0(g_pFightState->pPendingFighters_candidate[i].pObject, 0xFFFF0000, 0x25000);
            obj->bActionFlags &= 0xfe;
            sub_0802D64C(0x250);
        } else if (flags == 0x41) {
            if (fs->pFighters[fs->bActiveFighterIndex].bSpellId == Fumos) {
                obj->bActionState = 0;
                obj->bActionFlags |= 1;
                fs->pFighters[fs->bActiveFighterIndex].bSelectedActionIndex = 0xff;
                PostActionBattleCheck();
                return;
            }
            fs->bActionDelayCounter_candidate = 0x13;
            StartObjectMove(obj, g_pFightState->nSavedPosX, g_pFightState->nSavedPosY, 3);
            obj->bActionFlags &= 0xfe;
        }

        flags = obj->bActionFlags;
        phase = flags & 0x20;
        // The phase!=0 chain re-reads bActionDelayCounter_candidate from the
        // struct at each comparison; only the flags&0x40 chain below keeps it
        // in the delay local. Caching it here too puts delay in r1 function-
        // wide and mismatches the flags&0x40 reread (real r0, 0x08016528).
        if (phase != 0) {
            g_pFightState->bActionDelayCounter_candidate -= 1;
            if (g_pFightState->bActionDelayCounter_candidate > 4) {
                sub_0802D640((u8)(g_abBgPriority[4] - 1));
                g_aBgScrollState[0x25] += 0xFFFD0000;
                g_pFightState->bCameraZoomStep_candidate += 1;
                goto zoomJoin_08016882;
            }
            if (g_pFightState->bActionDelayCounter_candidate == 4) {
                sub_0802D64C(0);
                goto zoomJoin_08016882;
            }
            if (g_pFightState->bActionDelayCounter_candidate == 3) {
                for (i = 0; i < g_pFightState->bFighterCount; i++) {
                    sub_080019C0(g_pFightState->pFighters[i].pObject, 0, 0);
                    sub_080039E8(g_pFightState->pFighters[i].pObject);
                }
                for (i = 0; i < g_pFightState->bPendingFighterCount_candidate; i++) {
                    sub_080019C0(g_pFightState->pPendingFighters_candidate[i].pObject, 0, 0);
                    sub_080039E8(g_pFightState->pPendingFighters_candidate[i].pObject);
                }
                // Real emits an 8-byte block move (ldr/ldr/str/str off one
                // base each side), not two independent field stores.
                *(Vec2 *)&g_pFightState->nSavedPosX = *(Vec2 *)&obj->nX;
                StartObjectMove(obj, 0xb00000, 0x720000, 3);
                return;
            }
            if (g_pFightState->bActionDelayCounter_candidate != 0)
                return;
            sub_080019C0(obj, 0, 0);
            obj->bActionFlags = 1;
            return;
        }
        if (flags & 0x40) {
            g_pFightState->bActionDelayCounter_candidate -= 1;
            delay = g_pFightState->bActionDelayCounter_candidate;
            if (delay > 0xe)
                return;
            if (delay == 0xe) {
                SnapObjectPosition(obj, g_pFightState->nSavedPosX, g_pFightState->nSavedPosY);
                obj->wMoveDuration = 0;
                obj->wUnk86 = 0;
                for (i = 0; i < g_pFightState->bFighterCount; i++) {
                    if (g_pFightState->pFighters[i].bFighterType != Enemy) {
                        sub_080019C0(g_pFightState->pFighters[i].pObject, 0x10000, 0xFFFDB000);
                        sub_08003A30(g_pFightState->pFighters[i].pObject, 0, (s16)0xFFFFFC00, 0xc);
                    } else {
                        sub_080019C0(g_pFightState->pFighters[i].pObject, 0xFFFF8000, 0xFFFEB000);
                        sub_08003A30(g_pFightState->pFighters[i].pObject, 0, (s16)0xFFFFFC00, 0xc);
                    }
                }
                for (i = 0; i < g_pFightState->bPendingFighterCount_candidate; i++) {
                    sub_080019C0(g_pFightState->pPendingFighters_candidate[i].pObject, 0x10000, 0xFFFDB000);
                    sub_08003A30(g_pFightState->pPendingFighters_candidate[i].pObject, 0, (s16)0xFFFFFC00, 0xc);
                }
                sub_0802D64C((s16)0xFFFFFDB0);
                obj->bActionFlags &= 0xfe;
                goto zoomJoin_08016882;
            }
            if (delay == 0) {
                for (i = 0; i < g_pFightState->bFighterCount; i++) {
                    sub_080019C0(g_pFightState->pFighters[i].pObject, 0, 0);
                    sub_080039E8(g_pFightState->pFighters[i].pObject);
                }
                for (i = 0; i < g_pFightState->bPendingFighterCount_candidate; i++) {
                    sub_080019C0(g_pFightState->pPendingFighters_candidate[i].pObject, 0, 0);
                    sub_080039E8(g_pFightState->pPendingFighters_candidate[i].pObject);
                }
                sub_0802D64C(0);
                obj->bActionState = 0;
                obj->bActionFlags |= 1;
                PostActionBattleCheck();
                if (ACTIVE_FIGHTER.bSpellId == Informus)
                    PushGameMode_2(FolioBruti, 0, g_bDefeatWarpParam);
                ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
                return;
            }
            sub_0802D640((u8)(g_abBgPriority[4] + 1));
            g_aBgScrollState[0x25] += 0x30000;
            g_pFightState->bCameraZoomStep_candidate -= 1;
            goto zoomJoin_08016882;
        }
        if (flags & 1) {
            SetPlayerObjectAnim(obj, 1);
            obj->bActionFlags &= 0xfe;
            if (ACTIVE_FIGHTER.bSpellId == Fumos) {
                if (g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]].wHp == 0) {
                    i = 0;
                    while (g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[i]].wHp == 0 ||
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

    zoomJoin_08016882:
        if (obj->dwFlags & 0x8000) {
            // Buckbeak carve-out 1/4: skips the special-move effect; the flag
            // clear below still runs.
            if (obj->wFighterType != Buckbeak)
                TriggerBattleEffect(1, ACTIVE_FIGHTER.bSlotParam,
                                    0, g_pFightState->bActiveFighterIndex, 0, 0);
            obj->dwFlags &= 0xffff7fff;
        }
        if (obj->dwFlags & 0x40000) {
            obj->dwFlags &= 0xfffbffff;
            // Buckbeak carve-out 2/4: takes state Buckbeak below instead of
            // resolving a spell.
            if (obj->wFighterType != Buckbeak) {
                var_8 = g_abSpellEffectScriptId[ACTIVE_FIGHTER.bSpellId][ACTIVE_FIGHTER.bSpellLevel];
                ACTIVE_FIGHTER.wMp -= g_awSpellMpCost[ACTIVE_FIGHTER.bSpellId][ACTIVE_FIGHTER.bSpellLevel];
                g_aPartyMasterStats[ACTIVE_FIGHTER.bFighterType].wMp = ACTIVE_FIGHTER.wMp;
                if (ACTIVE_FIGHTER.bSelectedActionIndex != 0xfe)
                    g_nLastDamage = ResolvePlayerAttack(
                        g_pFightState->bActiveFighterIndex,
                        g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
                DrawFighterStatsUi_candidate(g_pFightState->pFighters[g_pFightState->bMenuFighterIndex].bFighterType, 0);
            } else {
                obj->bAttackOutcomeState = AttackOutcome_Buckbeak;
            }

            // Real reuses one r4/r6 pair across all three call sites, but that
            // sharing comes from CSE on the repeated ACTIVE_FIGHTER expression,
            // not from a source-level cached pointer: introducing a local here
            // makes the address expand as a plain PLUS (base first) instead of
            // an EXPAND_SUM address (mult term sorted last), which real uses.
            // Buckbeak carve-out 3/4: Fumos has no fighter check, so it still
            // triggers; every other spell skips the cast VFX for Buckbeak.
            if (ACTIVE_FIGHTER.bSpellId == Fumos) {
                TriggerBattleEffect(var_8, ACTIVE_FIGHTER.bSlotParam, ACTIVE_FIGHTER.bSelectedActionIndex,
                                    g_pFightState->bActiveFighterIndex,
                                    g_pFightState->aAllySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex],
                                    g_nLastDamage);
            } else if (obj->wFighterType != Buckbeak) {
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

        // Real re-reads obj->bAttackOutcomeState at every test rather than
        // caching it in one register, so this chain must not use a local.
        if (obj->bAttackOutcomeState == 1) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = AttackOutcome_None;
            if (g_nLastDamage == 0)
                return;
            ShowDamageNumber_candidate(g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex],
                         g_nLastDamage);
            return;
        }
        if (obj->bAttackOutcomeState == 2) {
            ShowItemUseResult(obj, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
            return;
        }
        if (obj->bAttackOutcomeState == 3) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = AttackOutcome_None;
            obj->bActionFlags = 0x41;
            ApplyDamageToFighter(g_nLastDamage,
                                 g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
            g_bLastTargetIndex = ACTIVE_FIGHTER.bSelectedActionIndex;
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            return;
        }
        if (obj->bAttackOutcomeState == 4) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            g_pFightState->bFaintMessageCount_candidate = 0;
            for (i = 0; i < g_pFightState->bFighterCount; i++) {
                if (g_pFightState->pFighters[i].bFighterType != Enemy)
                    continue;
                g_nLastDamage = ResolvePlayerAttack(g_pFightState->bActiveFighterIndex, i);
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = g_nLastDamage;
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bEffectId = (u8)((Object *)g_pFightState->pFighters[i].pObject)->wFighterType;
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bFlag = 0;
                g_pFightState->bFaintMessageCount_candidate += 1;
                SetFighterAttackAnimState_candidate(g_pFightState->pFighters[i].pObject, 2);
                if (g_nLastDamage > 999) {
                    g_nLastDamage -= 999;
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 3, i, 0); // crit
                } else if (g_nLastDamage != 0) {
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, i, 0); // normal
                } else {
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 2, i, 0); // miss
                }
                ApplyDamageToFighter(g_nLastDamage, i);
            }
            obj->bAttackOutcomeState = AttackOutcome_None;
            obj->bActionFlags = 0x41;
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            if (g_pFightState->dwBattleResultPending != 0)
                return;
            ShowBattleMessage(FaintResult, 0, 0);
            return;
        }
        if (obj->bAttackOutcomeState == 5) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = AttackOutcome_None;
            obj->bActionFlags = 0x41;
            g_bLastTargetIndex = ACTIVE_FIGHTER.bSelectedActionIndex;
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            return;
        }
        // Buckbeak carve-out 4/4: level-scaled damage, computed here rather
        // than in ResolvePlayerAttack: (HarryLevel >> 1) + 30, x4/3 under
        // SpellPowerBoost. Presented via the attack-result message plus a
        // floating number, never ShowDamageNumber.
        if (obj->bAttackOutcomeState == AttackOutcome_Buckbeak) {
            PlaySoundById(0x37);
            obj->bAttackOutcomeState = AttackOutcome_None;

            g_nLastDamage = (g_aPartyMasterStats[Harry].bLevel >> 1) + 30;
            if (ACTIVE_FIGHTER.bStatusFlags & SpellPowerBoost)
                g_nLastDamage = (g_nLastDamage * 4) / 3;

            SetFighterAttackAnimState_candidate(
                g_pFightState->pFighters[g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]].pObject,
                2);

            ShowBattleMessage(AttackResult, g_nLastDamage, 0);

            if (g_pFightState->bPendingStatusMessageVariant_candidate != NO_PENDING_STATUS_MESSAGE_VARIANT)
                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant_candidate);

            ShowFloatingDamageNumber_candidate(g_nLastDamage, 0,
                         g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);

            obj->bActionFlags = 0x41;

            ApplyDamageToFighter(g_nLastDamage,
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

        if (obj->bActionFlags & 1) {
            SetPlayerObjectAnim(obj, 2);
            obj->bActionFlags &= 0xfe;
            obj->bAttackOutcomeState = AttackOutcome_None;
            if (ACTIVE_FIGHTER.bFighterType == Harry)
                obj->dwStateTimer = 0x3c;
            else
                obj->dwStateTimer = 0x28;
        }
        if (obj->dwStateTimer != 0) {
            obj->dwStateTimer -= 1;
            if (obj->dwStateTimer == 0) {
                if (ACTIVE_FIGHTER.bFighterType == Harry)
                    ShowBattleMessage(SpecialAbilityText, g_nFolioUniversitasSlot & 0xffff, 0);
                else
                    ShowBattleMessage(SpecialAbilityText, ACTIVE_FIGHTER.bSpellId, 0);
            }
        }
        if (obj->dwFlags & 0x40000) {
            obj->dwFlags &= 0xfffbffff;
            fighterType = ACTIVE_FIGHTER.bFighterType;
            if (fighterType == Harry) {
                if (g_pFightState->bAttackVfxId_candidate != 0xff) {
                    DecrementFolioUniversitasCard(g_pFightState->bAttackVfxId_candidate);
                    DecrementFolioUniversitasCard(g_pFightState->bAttackVfxId_candidate + 1);
                }
                SetPlayerObjectAnim(obj, 0);
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
                SetPlayerObjectAnim(obj, 0);
            }
        }
        if (obj->dwFlags & 0x8000) {
            selActionIdx = ACTIVE_FIGHTER.bSelectedActionIndex;
            if (g_pFightState->aEnemySlotTurnOrderIndex[selActionIdx] == 0xff) {
                i = 0;
                while (g_pFightState->aEnemySlotTurnOrderIndex[i] == 0xff)
                    i++;
                ACTIVE_FIGHTER.bSelectedActionIndex = i;
            }
            obj->dwFlags &= 0xffff7fff;
            TriggerBattleEffect(g_abSpecialMoveEffectId[ACTIVE_FIGHTER.bSpellId],
                                 ACTIVE_FIGHTER.bSlotParam,
                                 (u8)(ACTIVE_FIGHTER.bSelectedActionIndex + 3),
                                 g_pFightState->bActiveFighterIndex,
                                 g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
        }
        if (obj->bAttackOutcomeState == 1) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = AttackOutcome_None;
            if (ACTIVE_FIGHTER.bFighterType == Harry &&
                g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
                sub_080129F4();
            sub_08012B40();
            PostActionBattleCheck();
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            SetFighterAttackAnimState_candidate(obj, 0);
            PostActionBattleCheck();
        }
        if (obj->bAttackOutcomeState == 2) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = AttackOutcome_None;
            if (g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
                sub_080129F4();
            sub_08012B40();
            g_nLastDamage = 5;
            SetFighterAttackAnimState_candidate(g_pFightState->pFighters[g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]].pObject, 2);
            ShowBattleMessage(AttackResult, g_nLastDamage, 0);
            if (g_pFightState->bPendingStatusMessageVariant_candidate != NO_PENDING_STATUS_MESSAGE_VARIANT)
                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
            ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
            ApplyDamageToFighter(g_nLastDamage, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
            PostActionBattleCheck();
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            SetFighterAttackAnimState_candidate(obj, 0);
        }
        if (obj->bAttackOutcomeState == 3) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = AttackOutcome_None;
            if (g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
                sub_080129F4();
            sub_08012B40();
            g_nLastDamage = 0x14;
            SetFighterAttackAnimState_candidate(g_pFightState->pFighters[g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]].pObject, 2);
            ShowBattleMessage(AttackResult, g_nLastDamage, 0);
            if (g_pFightState->bPendingStatusMessageVariant_candidate != NO_PENDING_STATUS_MESSAGE_VARIANT)
                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
            ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
            ApplyDamageToFighter(g_nLastDamage, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
            PostActionBattleCheck();
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            SetFighterAttackAnimState_candidate(obj, 0);
        }
        if (obj->bAttackOutcomeState == 4) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = AttackOutcome_None;
            if (g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
                sub_080129F4();
            sub_08012B40();
            g_nLastDamage = 0x14;
            g_pFightState->bFaintMessageCount_candidate = 0;
            for (i = 0; i < g_pFightState->bFighterCount; i++) {
                if (g_pFightState->pFighters[i].bFighterType == Enemy) {
                    SetFighterAttackAnimState_candidate(g_pFightState->pFighters[i].pObject, 2);
                    g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bEffectId = ((Object *)g_pFightState->pFighters[i].pObject)->wFighterType;
                    g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bFlag = 0;
                    g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = g_nLastDamage;
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, i, 0);
                    ApplyDamageToFighter(g_nLastDamage, i);
                    g_pFightState->bFaintMessageCount_candidate += 1;
                }
            }
            /* Re-stored after the loop: real emits the store twice, and the
             * intervening calls make obj->bAttackOutcomeState unprovably
             * unchanged, so neither store folds away. */
            obj->bAttackOutcomeState = AttackOutcome_None;
            ShowBattleMessage(FaintResult, 0, 0);
            PostActionBattleCheck();
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            if (obj->bActionState == 0x15)
                SetFighterAttackAnimState_candidate(obj, 0);
        }
        if (obj->bAttackOutcomeState != 5)
            return;
        if (g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
            sub_080129F4();
        sub_08012B40();
        g_pFightState->bFaintMessageCount_candidate = 0;
        for (i = 0; i < g_pFightState->bFighterCount; i++) {
            g_nLastDamage = 0x2d;
            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bEffectId = ((Object *)g_pFightState->pFighters[i].pObject)->wFighterType;
            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bFlag = 0;
            if (g_pFightState->pFighters[i].bFighterType == Enemy) {
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = g_nLastDamage;
                ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, i, 0);
                ShowDamageNumber_candidate(i, g_nLastDamage);
                ApplyDamageToFighter(g_nLastDamage, i);
            } else {
                if (g_pFightState->pFighters[i].wHp <= 0xf)
                    g_nLastDamage = g_pFightState->pFighters[i].wHp - 1;
                else
                    g_nLastDamage = 0xf;
                ((Object *)g_pFightState->pFighters[i].pObject)->wStagedDamage = g_nLastDamage;
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = g_nLastDamage;
                ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, i, 0);
                ShowDamageNumber_candidate(i, g_nLastDamage);
            }
            g_pFightState->bFaintMessageCount_candidate += 1;
        }
        g_pFightState->pAttackAnimObject_candidate = 0;
        g_pFightState->bAttackAnimState_candidate = 0;
        obj->bAttackOutcomeState = AttackOutcome_None;
        ShowBattleMessage(FaintResult, 0, 0);
        PostActionBattleCheck();
        ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
        if (obj->bActionState != 0x15)
            return;
        SetFighterAttackAnimState_candidate(obj, 0);
        return;
    }
    case 4: // ApplyStatusRestoreItemEffect?
    {
        u32 result;
        s32 targetIdx, code;
        u16 amount;

        if (obj->bActionFlags & 1) {
            obj->bAttackOutcomeState = AttackOutcome_None;
            SetPlayerObjectAnim(obj, 3);
            obj->bActionFlags &= 0xfe;
            obj->dwStateTimer = 0x1e;
        }
        if (obj->dwFlags & 0x40000) {
            obj->dwFlags &= 0xfffbffff;
            result = sub_08026CDC(ACTIVE_FIGHTER.bSpellLevel);
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
        obj->dwStateTimer -= 1;
        if (obj->dwStateTimer == 0) {
            ShowBattleMessage(StatusRestore, ACTIVE_FIGHTER.bSpellLevel, 0);
        }
        if (obj->bAttackOutcomeState == AttackOutcome_None)
            return;

        g_pFightState->pAttackAnimObject_candidate = 0;
        g_pFightState->bAttackAnimState_candidate = 0;
        obj->bAttackOutcomeState = AttackOutcome_None;

        {
            u8 spellLevel = ACTIVE_FIGHTER.bSpellLevel;
            u8 fighterIndex = g_pFightState->aAllySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex];

            result = sub_08026CDC(spellLevel);
            switch (result) {
            case 1: {
                s32 x = sub_08026CF0(spellLevel);
                amount = sub_080152CC(x, fighterIndex);
                ShowFloatingDamageNumber_candidate(amount, 0xd, fighterIndex, 1);
                code = 9;
                ShowBattleMessage(code, amount, 0);
                break;
            }
            case 2: {
                s32 x = sub_08026CF0(spellLevel);
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
        SetFighterAttackAnimState_candidate(obj, 0);
        SetPlayerObjectAnim(obj, 0);
        PostActionBattleCheck();
        ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
        obj->bActionFlags &= 0xfe;
        return;
    }
    case 1: // PlayFighterImpactSound?
        if ((obj->bActionFlags & 1) == 0)
            return;
        switch (obj->wFighterType) {
        case 0: PlaySoundById(0xa1); break;
        case 1: PlaySoundById(0xa7); break;
        case 2: PlaySoundById(0xa4); break;
        case 3: PlaySoundById(0x39); break;
        }
        SetPlayerObjectAnim(obj, 8);
        obj->bActionFlags &= 0xfe;
        PlaySoundById(0x9c);
        return;
    case 5: // ReturnFighterToPosition?
        if (obj->bActionFlags & 1) {
            obj->bActionFlags &= 0xfe;
            obj->dwStateTimer = 0x1e;
            SetObjectFlippedX(obj, 1);
            return;
        }
        obj->dwStateTimer -= 1;
        if (obj->dwStateTimer != 0)
            return;
        ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
        SetObjectFlippedX(obj, 0);
        SetFighterAttackAnimState_candidate(obj, 0);
        PushBattleState(1);
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
