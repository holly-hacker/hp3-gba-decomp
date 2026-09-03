#include "types.h"
#include "battle.h"

#define ACTIVE_FIGHTER (g_pFightState->pFighters[g_pFightState->bActiveFighterIndex])

typedef struct Vec2 {
    u32 x, y;
} Vec2;

// per-wFighterType windup-flash resource pointer row, stride 0xA0
typedef struct AnimFlashRow {
    u8 pad_00[0x68];
    void *pWindupResourceB;  // 0x68
    u8 pad_6C[0x0C];         // -> 0x78
    void *pWindupResourceA;  // 0x78
    u8 pad_7C[0xA0 - 0x7C];
} AnimFlashRow;

extern AnimFlashRow g_aFighterAnimTable[];  // 0x08051248, UNCONFIRMED row count

extern void SetObjectFlippedX(Object *obj, s32 flip);
extern void sub_08015484(Object *obj, s32 state);
extern void sub_0800D264(void *ptr, s16 val1, s16 val2);  // 25-entry palette-flash/fade queue; val1/val2 real width is 16-bit
extern void PlaySoundById(s32 id);
extern void sub_08018B14(u16 damage, s32 fighterIndex);
extern void SetFighterAttackAnimState_candidate(Object *obj, s32 state);
extern void ApplyStatusDamageToFighter_candidate(s32 damage, s32 fighterIndex);
extern void TriggerBattleEffect(s32 effectId, s32 slotParam, s32 selectedActionIndex, s32 activeFighterIndex, s32 targetIdx, s32 damage);
extern s32 sub_08026CDC(s32 spellLevel);
extern s32 sub_08026CF0(s32 spellLevel);
extern u16 sub_08015334(s32 x, s32 fighterIndex);
extern u16 sub_080152CC(s32 x, s32 fighterIndex);
extern void ShowFloatingDamageNumber_candidate(s32 damage, s32 code, s32 fighterIndex, s32 flag);
extern void ShowBattleMessage(s32 code, s32 arg2, s32 arg3);
extern void sub_0800EB2C(s32 fighterIndex);
extern void ClearParalyzedFighter_candidate(s32 fighterIndex);
extern void PostActionBattleCheck(void);
extern void PushBattleState(s32 state);
extern void DecrementFolioUniversitasCard(s32 slot);
extern u8 g_abHarryCardEffectId[16];            // 0x080514C8
extern u8 g_aCardTargetingMeta[][2];            // 0x080514DE, stride 2
extern u8 g_abHermioneLectureEffectId[3];       // 0x0805150D
extern u8 g_abSpecialMoveEffectId[7];           // 0x0805150A
extern u16 g_nLastDamage;                       // 0x0300274A
extern u8 g_bLastTargetIndex;                   // 0x0300274C
extern void sub_080129F4(void);
extern void sub_08012B40(void);

// --- case 0x1a additions ---
extern void sub_080019C0(void *obj, s32 x, s32 y);  // sets Object+0x3c/+0x40, i.e. nVelX/nVelY directly
extern void sub_08003A30(void *obj, s16 a, s16 b, s16 c);  // a is stored pre-shifted << 8 into a 16-bit field
extern void sub_0802D64C(s16 delta);
extern void sub_08012A38(void);
extern void sub_0800E0CC(s32 fighterType, s32 arg2);
extern void ShowDamageNumber_candidate(s32 targetIndex, s32 damage);
extern void SnapObjectPosition(Object *obj, u32 x, u32 y);
extern void StartObjectMove(Object *obj, u32 x, u32 y, s16 mode);
extern void ShowItemUseResult(Object *obj, s32 targetIndex);
extern void PushGameMode_2(s32 mode, s32 arg2, s32 arg3);
extern void PushGameMode_0(s32 mode, s32 arg2, s32 arg3);
extern s32 ResolvePlayerAttack(s32 attackerIndex, s32 targetIndex);
// 0x08017F98; draft.c also refers to it as sub_08017F98 in case 0x15.
extern void ApplyDamageToFighter(u16 damage, u8 fighterIndex);
extern u8 g_abSpellEffectScriptId[][3];         // 0x080538B0, [spellId][level]
extern u16 g_awSpellMpCost[][3];                // 0x08053964, [spellId][level]
extern BattleFighter g_aPartyMasterStats[];     // 0x030024EC, 0x48 stride, by FighterType
extern u8 g_bDefeatWarpParam;                   // 0x03002748

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
            sub_08015484(obj, 7);
            slot = obj->bGfxSlotAndFlags >> 4;
            ptr = (u8 *)g_aFighterAnimTable[obj->wFighterType].pWindupResourceA + 2;
            sub_0800D264(ptr, (slot << 4) + 1, 0xf);
        } else if (obj->wActionVariant == 2) {
            sub_08015484(obj, 6);
            slot = obj->bGfxSlotAndFlags >> 4;
            ptr = (u8 *)g_aFighterAnimTable[obj->wFighterType].pWindupResourceB + 2;
            sub_0800D264(ptr, (slot << 4) + 1, 0xf);
        } else {
            sub_08015484(obj, 0);
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
            sub_08015484(obj, 4);
            obj->bActionFlags &= 0xfe;
        }
        if ((obj->dwFlags & 0x40000) == 0)
            return;
        SetFighterAttackAnimState_candidate(obj, 0);
        ApplyStatusDamageToFighter_candidate(obj->wStagedDamage, obj->bFighterIndex);
        return;
    case 0x1a: // ExecutePlayerAttackSequence?
    {
        s16 flags;
        u8 phase, delay, i;
        // Real loads *g_pFightState once before testing bActionFlags and uses
        // that value in both the 0x21 and 0x41 arms, so it is a single local.
        FightState *fs = g_pFightState;

        flags = obj->bActionFlags;
        if (flags == 0x21) {
            if (fs->dwPlayerActionActive_candidate == 0)
                sub_08012A38();
            sub_0800E0CC(ACTIVE_FIGHTER.bFighterType, 0);
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
                    PushGameMode_0(0x2d, 0, g_bDefeatWarpParam);
                ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
                return;
            }
            sub_0802D640((u8)(g_abBgPriority[4] + 1));
            g_aBgScrollState[0x25] += 0x30000;
            g_pFightState->bCameraZoomStep_candidate -= 1;
            goto zoomJoin_08016882;
        }
        if (flags & 1) {
            sub_08015484(obj, 1);
            obj->bActionFlags &= 0xfe;
            if (ACTIVE_FIGHTER.bSpellId == Fumos) {
                if (g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[
                        ACTIVE_FIGHTER.bSelectedActionIndex]].wHp == 0) {
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
            if (obj->wFighterType != Buckbeak)
                TriggerBattleEffect(1, ACTIVE_FIGHTER.bSlotParam,
                                    0, g_pFightState->bActiveFighterIndex, 0, 0);
            obj->dwFlags &= 0xffff7fff;
        }
        if (obj->dwFlags & 0x40000) {
            obj->dwFlags &= 0xfffbffff;
            if (obj->wFighterType != Buckbeak) {
                var_8 = g_abSpellEffectScriptId[ACTIVE_FIGHTER.bSpellId][ACTIVE_FIGHTER.bSpellLevel];
                ACTIVE_FIGHTER.wMp -= g_awSpellMpCost[ACTIVE_FIGHTER.bSpellId][ACTIVE_FIGHTER.bSpellLevel];
                g_aPartyMasterStats[ACTIVE_FIGHTER.bFighterType].wMp =
                    ACTIVE_FIGHTER.wMp;
                if (ACTIVE_FIGHTER.bSelectedActionIndex != 0xfe)
                    g_nLastDamage = ResolvePlayerAttack(
                        g_pFightState->bActiveFighterIndex,
                        g_pFightState->aEnemySlotTurnOrderIndex[
                            ACTIVE_FIGHTER.bSelectedActionIndex]);
                sub_0800E0CC(g_pFightState->pFighters[g_pFightState->bMenuFighterIndex].bFighterType, 0);
            } else {
                obj->bAttackOutcomeState = 6;
            }

            // Real reuses one r4/r6 pair across all three call sites, but that
            // sharing comes from CSE on the repeated ACTIVE_FIGHTER expression,
            // not from a source-level cached pointer: introducing a local here
            // makes the address expand as a plain PLUS (base first) instead of
            // an EXPAND_SUM address (mult term sorted last), which real uses.
            if (ACTIVE_FIGHTER.bSpellId == Fumos) {
                TriggerBattleEffect((u8)var_8, ACTIVE_FIGHTER.bSlotParam, ACTIVE_FIGHTER.bSelectedActionIndex,
                                    g_pFightState->bActiveFighterIndex,
                                    g_pFightState->aAllySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex],
                                    g_nLastDamage);
            } else if (obj->wFighterType != Buckbeak) {
                if (ACTIVE_FIGHTER.bSelectedActionIndex != 0xfe)
                    TriggerBattleEffect((u8)var_8, ACTIVE_FIGHTER.bSlotParam, (u8)(ACTIVE_FIGHTER.bSelectedActionIndex + 3),
                                        g_pFightState->bActiveFighterIndex,
                                        g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex],
                                        g_nLastDamage);
                else
                    TriggerBattleEffect((u8)var_8, ACTIVE_FIGHTER.bSlotParam, (u8)(ACTIVE_FIGHTER.bSelectedActionIndex + 3),
                                        g_pFightState->bActiveFighterIndex, 0, 0);
            }
        }

        // Real re-reads obj->bAttackOutcomeState at every test rather than
        // caching it in one register, so this chain must not use a local.
        if (obj->bAttackOutcomeState == 1) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = 0;
            if (g_nLastDamage == 0)
                return;
            ShowDamageNumber_candidate(g_pFightState->aEnemySlotTurnOrderIndex[
                             ACTIVE_FIGHTER.bSelectedActionIndex],
                         g_nLastDamage);
            return;
        }
        if (obj->bAttackOutcomeState == 2) {
            ShowItemUseResult(obj, g_pFightState->aEnemySlotTurnOrderIndex[
                                       ACTIVE_FIGHTER.bSelectedActionIndex]);
            return;
        }
        if (obj->bAttackOutcomeState == 3) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = 0;
            obj->bActionFlags = 0x41;
            ApplyDamageToFighter(g_nLastDamage,
                                 g_pFightState->aEnemySlotTurnOrderIndex[
                                     ACTIVE_FIGHTER.bSelectedActionIndex]);
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
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bEffectId =
                    (u8)((Object *)g_pFightState->pFighters[i].pObject)->wFighterType;
                g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bFlag = 0;
                g_pFightState->bFaintMessageCount_candidate += 1;
                SetFighterAttackAnimState_candidate(g_pFightState->pFighters[i].pObject, 2);
                if (g_nLastDamage > 999) {
                    g_nLastDamage -= 999;
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 3, i, 0);
                } else if (g_nLastDamage != 0) {
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, i, 0);
                } else {
                    ShowFloatingDamageNumber_candidate(g_nLastDamage, 2, i, 0);
                }
                ApplyDamageToFighter(g_nLastDamage, i);
            }
            obj->bAttackOutcomeState = 0;
            obj->bActionFlags = 0x41;
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            if (g_pFightState->dwBattleResultPending != 0)
                return;
            ShowBattleMessage(6, 0, 0);
            return;
        }
        if (obj->bAttackOutcomeState == 5) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = 0;
            obj->bActionFlags = 0x41;
            g_bLastTargetIndex = ACTIVE_FIGHTER.bSelectedActionIndex;
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            return;
        }
        if (obj->bAttackOutcomeState != 6)
            return;
        PlaySoundById(0x37);
        obj->bAttackOutcomeState = 0;
        g_nLastDamage = (g_aPartyMasterStats[0].bLevel >> 1) + 0x1e;
        if (ACTIVE_FIGHTER.bStatusFlags & SpellPowerBoost)
            g_nLastDamage = (g_nLastDamage * 4) / 3;
        SetFighterAttackAnimState_candidate(g_pFightState->pFighters[
                         g_pFightState->aEnemySlotTurnOrderIndex[
                             ACTIVE_FIGHTER.bSelectedActionIndex]].pObject,
                     2);
        ShowBattleMessage(5, g_nLastDamage, 0);
        if (g_pFightState->bPendingStatusMessageVariant_candidate != 0x12)
            ShowBattleMessage(5, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
        ShowFloatingDamageNumber_candidate(g_nLastDamage, 0,
                     g_pFightState->aEnemySlotTurnOrderIndex[
                         ACTIVE_FIGHTER.bSelectedActionIndex], 0);
        obj->bActionFlags = 0x41;
        ApplyDamageToFighter(g_nLastDamage,
                             g_pFightState->aEnemySlotTurnOrderIndex[
                                 ACTIVE_FIGHTER.bSelectedActionIndex]);
        g_bLastTargetIndex = ACTIVE_FIGHTER.bSelectedActionIndex;
        ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
        return;
    }
    case 0x15: // HandleScriptedDamageEvent_candidate?
    {
        FighterType fighterType;
        u8 activeIdx, cardMeta, effectId, slotParam, selActionIdx, targetIdx;
        u8 i;

        if (obj->bActionFlags & 1) {
            sub_08015484(obj, 2);
            obj->bActionFlags &= 0xfe;
            obj->bAttackOutcomeState = 0;
            if (ACTIVE_FIGHTER.bFighterType == Harry)
                obj->dwStateTimer = 0x3c;
            else
                obj->dwStateTimer = 0x28;
        }
        if (obj->dwStateTimer != 0) {
            obj->dwStateTimer -= 1;
            if (obj->dwStateTimer == 0) {
                if (ACTIVE_FIGHTER.bFighterType == Harry)
                    ShowBattleMessage(3, g_nFolioUniversitasSlot & 0xffff, 0);
                else
                    ShowBattleMessage(3, ACTIVE_FIGHTER.bSpellId, 0);
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
                sub_08015484(obj, 0);
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
                sub_08015484(obj, 0);
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
            obj->bAttackOutcomeState = 0;
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
            obj->bAttackOutcomeState = 0;
            if (g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
                sub_080129F4();
            sub_08012B40();
            g_nLastDamage = 5;
            SetFighterAttackAnimState_candidate(g_pFightState->pFighters[g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]].pObject, 2);
            ShowBattleMessage(5, g_nLastDamage, 0);
            if (g_pFightState->bPendingStatusMessageVariant_candidate != 0x12)
                ShowBattleMessage(5, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
            ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
            ApplyDamageToFighter(g_nLastDamage, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
            PostActionBattleCheck();
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            SetFighterAttackAnimState_candidate(obj, 0);
        }
        if (obj->bAttackOutcomeState == 3) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = 0;
            if (g_aCardTargetingMeta[g_nFolioUniversitasSlot][1] != 0)
                sub_080129F4();
            sub_08012B40();
            g_nLastDamage = 0x14;
            SetFighterAttackAnimState_candidate(g_pFightState->pFighters[g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]].pObject, 2);
            ShowBattleMessage(5, g_nLastDamage, 0);
            if (g_pFightState->bPendingStatusMessageVariant_candidate != 0x12)
                ShowBattleMessage(5, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
            ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex], 0);
            ApplyDamageToFighter(g_nLastDamage, g_pFightState->aEnemySlotTurnOrderIndex[ACTIVE_FIGHTER.bSelectedActionIndex]);
            PostActionBattleCheck();
            ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
            SetFighterAttackAnimState_candidate(obj, 0);
        }
        if (obj->bAttackOutcomeState == 4) {
            g_pFightState->pAttackAnimObject_candidate = 0;
            g_pFightState->bAttackAnimState_candidate = 0;
            obj->bAttackOutcomeState = 0;
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
            obj->bAttackOutcomeState = 0;
            ShowBattleMessage(6, 0, 0);
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
        obj->bAttackOutcomeState = 0;
        ShowBattleMessage(6, 0, 0);
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
            obj->bAttackOutcomeState = 0;
            sub_08015484(obj, 3);
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
            ShowBattleMessage(8, ACTIVE_FIGHTER.bSpellLevel, 0);
        }
        if (obj->bAttackOutcomeState == 0)
            return;

        g_pFightState->pAttackAnimObject_candidate = 0;
        g_pFightState->bAttackAnimState_candidate = 0;
        obj->bAttackOutcomeState = 0;

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
                sub_0800EB2C(fighterIndex);
                break;
            case 4:
                ClearParalyzedFighter_candidate(fighterIndex);
                break;
            }
        }

        ACTIVE_FIGHTER.bSelectedActionIndex = 0xff;
        SetFighterAttackAnimState_candidate(obj, 0);
        sub_08015484(obj, 0);
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
        sub_08015484(obj, 8);
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
