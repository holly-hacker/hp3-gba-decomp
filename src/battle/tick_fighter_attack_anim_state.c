#include "types.h"
#include "battle.h"
#include "mt19937.h"

// Enemy-side per-object tick dispatcher, mirroring TickPlayerActionState's
// shape: a switch on Object+0x8D (bActionState), every case branching into
// a shared no-op tail rather than returning directly. Registered as
// InitMonsterBattleActor's pObject->pfnTick. See docs/memory-map/battle.md.
void TickFighterAttackAnimState_candidate(Object *obj)
{
    u8 *pFlags;
    s32 fighterType;
    BattleFighter *active;
    u8 monsterIndex;
    u32 i;

    if (obj->dwFlags & 2)
        return;

    UpdateFighterFlashEffect_candidate(obj);

    switch (obj->bActionState) {
    case 0:
    {
        pFlags = &obj->bActionFlags;
        if ((*pFlags & 1) == 0)
            return;

        if (obj->wActionVariant != 2)
            SetMonsterObjectAnim(obj, 0);

        *pFlags &= 0xfe;
        return;
    }

    case 0xf:
        if (obj->nVelX != 0 || obj->nVelY != 0)
            return;

        SetObjectActionState(obj, 0);
        return;

    case 2:
    {
        pFlags = &obj->bActionFlags;
        if (*pFlags & 1) {
            SetMonsterObjectAnim(obj, 7);
            *pFlags &= 0xfe;
        }

        if ((obj->dwFlags & 0x40000) == 0)
            return;

        SetObjectActionState(obj, 0);
        return;
    }

    case 1:
    {
        if (obj->bActionFlags & 1) {
            if (obj->wObjectType != 0x3a) {
                SetObjectFlippedX(obj, 1);
                PlaySoundById(0x9d);
            } else {
                PlaySoundById(0x14);
            }
            obj->dwStateTimer = 0x14;
            obj->bActionFlags &= 0xfe;
        }

        if (obj->wObjectType != 0x3a) {
            sub_080039F8(obj);
            sub_08003A0C(obj);
            SetObjectVelocity(obj, 0xfffa0000, 0);
        }

        if (--obj->dwStateTimer != 0)
            return;

        if (obj->pLinkedObject_candidate != 0)
            sub_0801BCB0(obj->pLinkedObject_candidate);

        if (obj->pShadowObject != 0)
            obj->pShadowObject->dwFlags |= 0x82;

        if (g_pFightState->bFaintMessageCount_candidate == 0)
            CheckBattleVictory(obj);

        if (g_pFightState->dwBattleResultPending != 0) {
            if (obj->wObjectType == 0x3a)
                return;
            obj->dwFlags &= 0xfffffffe;
            return;
        }

        if (obj->wObjectType == (fighterType = 0x3a))
            return;

        obj->dwFlags |= 0x82;

        if ((u16)(obj->wObjectType - 0x31) > 2)
            return;

        FreeObject(obj->pShadowObject);
        return;
    }

    case 0x1a:
    {
        active = &g_pFightState->pFighters[g_pFightState->bActiveFighterIndex];
        monsterIndex = active->bRosterIndex;

        if (obj->bActionFlags == 0x21) {
            if (monsterIndex == 0x3f) { // Lupin Werewolf
                active->bSelectedActionIndex = 0xff;

                // Lupin Werewolf always attacks buckbeak (if available)
                for (i = 0; i < g_pFightState->bFighterCount; i++) {
                    if (g_pFightState->pFighters[i].bFighterType == Buckbeak)
                        active->bSelectedActionIndex = i;
                }
            } else {
                // Every other enemy: uniform rejection sample over the
                // whole fighter array until a living ally is hit.
                u16 roll;
                BattleFighter *candidate;
                BattleFighter *fighters;
                do {
                    roll = Mt19937RandMax(g_pFightState->bFighterCount - 1);
                    fighters = g_pFightState->pFighters;
                    // Register-pressure proxy: integer form, not
                    // `&fighters[roll]`, reproduces the ROM's
                    // `adds rD, rIndex, rBase` operand order.
                    candidate = (BattleFighter *)(roll * sizeof(BattleFighter) + (u32)fighters);
                } while (candidate->bFighterType == Enemy
                         || candidate->pObject == 0
                         || (u16)candidate->nFaintedFlag == 0xffff);
                active->bSelectedActionIndex = roll;
            }

            *(Point1616 *)&g_pFightState->nSavedPosX = *(Point1616 *)&obj->nX;

            if (MonsterTable[active->bRosterIndex].bSpecialChance == 100) {
                g_pFightState->bActionDelayCounter_candidate = 5;
                if (active->bRosterIndex != 0x36) {
                    u32 destX, destY;
                    if ((u8)(active->bRosterIndex - 0x1a) < 3) {
                        destX = 0x380000;
                        destY = 0x2c0000;
                    } else {
                        destX = 0x480000;
                        destY = 0x540000;
                    }

                    StartObjectMove(obj, destX, destY, 3);
                }
            } else {

                u32 roster;
                u8 targetSlot;
                g_pFightState->bActionDelayCounter_candidate = 10;
                roster = active->bRosterIndex;
                targetSlot = g_pFightState->pFighters[active->bSelectedActionIndex].bSlotParam;
                StartObjectMove(obj,
                    (g_aBattleSlotAnchorPos_candidate[targetSlot][0] - g_aMonsterAttackOffset_candidate[roster][0]) << 16,
                    (g_aBattleSlotAnchorPos_candidate[targetSlot][1] - g_aMonsterAttackOffset_candidate[roster][1]) << 16,
                    8);


                SetObjectAffineTransform(obj, 0x10000, 0x10000, 0, 3);

                if ((u8)(active->bRosterIndex - 0x37) <= 1) {
                    StartObjectAffineScaleTween(obj, 0x13333, 0x13333, 8);
                } else {
                    StartObjectAffineScaleTween(obj, 0x18000, 0x18000, 8);
                }
            }

            obj->bActionFlags &= 0xfe;
        } else if (obj->bActionFlags == 0x41) {
            SetMonsterObjectAnim(obj, 0);

            g_pFightState->bActionDelayCounter_candidate = 0x14;

            StartObjectMove(obj, g_pFightState->nSavedPosX, g_pFightState->nSavedPosY, 3);

            if (MonsterTable[active->bRosterIndex].bSpecialChance != 100)
                StartObjectAffineScaleTween(obj, 0x10000, 0x10000, 3);

            obj->bActionFlags &= 0xfe;
        }

        if (obj->bActionFlags & 0x20) {
            g_pFightState->bActionDelayCounter_candidate--;
            if (g_pFightState->bActionDelayCounter_candidate != 0)
                return;

            obj->wUnk86 = 0;
            SetObjectVelocity(obj, 0, 0);
            obj->bActionFlags = 1;
            return;
        }
        if (obj->bActionFlags & 0x40) {
            g_pFightState->bActionDelayCounter_candidate--;
            if (g_pFightState->bActionDelayCounter_candidate != 0)
                return;

            obj->wMoveDuration = 0;
            obj->bActionState = 0;
            obj->bActionFlags |= 1;

            PostActionBattleCheck();
            // Low two bits only: the ROM extracts them with a shift pair,
            // the way a 2-bit unsigned bitfield read compiles.
            if ((((u32)obj->bFlags_0xD1 << 30) >> 30) != 3)
                return;

            ReleaseObjectAffineSlot(obj);
            return;
        }

        if (obj->bActionFlags & 1) {
            SetMonsterObjectAnim(obj, 0xc);
            obj->bActionFlags &= 0xfe;
        }

        if (obj->dwFlags & 0x8000) {
            if (MonsterTable[monsterIndex].bSpecialChance == 100) {
                g_nLastDamage = (u16)ResolveEnemyAttack(g_pFightState->bActiveFighterIndex, active->bSelectedActionIndex);
                RollMonsterSpecialEffect(monsterIndex, active->bSelectedActionIndex, g_nLastDamage);
            }

            if (obj->wObjectType == 0x3e) {
                obj->bEnemyAttackPhase_candidate = 0xff;
                obj->bAttackOutcomeState = 2;
            }

            obj->dwFlags &= 0xffff7fff;
        }

        if (((obj->dwFlags & 0x40000) == 0) || (obj->bEnemyAttackPhase_candidate == 0xff)) {
            if (obj->bEnemyAttackPhase_candidate != 0xff)
                goto skipPhase0;

            if (obj->bAttackOutcomeState != 1)
                goto phase2;
        }
        {
        phase0:
            // g_nLastDamage is shared with the dwFlags&0x8000 block above:
            // exactly one of the two ResolveEnemyAttack calls fires per
            // attack (bSpecialChance==100 there, <=99 here), and this tail
            // always reads whichever one just ran.
            obj->bEnemyAttackPhase_candidate = 0;

            if (MonsterTable[monsterIndex].bSpecialChance <= 99) {
                g_nLastDamage = (u16)ResolveEnemyAttack(g_pFightState->bActiveFighterIndex, active->bSelectedActionIndex);
                if (g_nLastDamage != 0)
                    RollMonsterSpecialEffect(monsterIndex, active->bSelectedActionIndex, g_nLastDamage);
            }

            if (g_nLastDamage != 0) {
                ShowDamageNumber_candidate(active->bSelectedActionIndex, g_nLastDamage);
            } else {
                PlaySoundById(0x4b);
            }

            obj->bActionFlags = 0x41;
            obj->dwFlags &= 0xfffbffff;

            ShowItemUseResult(obj, active->bSelectedActionIndex);

            phase2:
            if (obj->bEnemyAttackPhase_candidate != 0xff)
                goto skipPhase0;

            if (obj->bAttackOutcomeState == 2) {
                if (MonsterTable[monsterIndex].bSpecialChance <= 99) {
                    g_nLastDamage = (u16)ResolveEnemyAttack(
                        g_pFightState->bActiveFighterIndex,
                        g_pFightState->pFighters[g_pFightState->bActiveFighterIndex].bSelectedActionIndex);
                }

                if (g_nLastDamage != 0)
                    ShowDamageNumber_candidate(active->bSelectedActionIndex, g_nLastDamage);

                active->bSpellId = Flipendo;
                ShowItemUseResult(obj, active->bSelectedActionIndex);
            }

            if (obj->bEnemyAttackPhase_candidate != 0xff)
                goto skipPhase0;

            if (obj->bAttackOutcomeState == 4) {
                // Fainted-message sweep: every living non-enemy fighter
                // resolves once more and queues a faint/HP message.
                obj->bAttackOutcomeState = 0;
                g_pFightState->pAttackAnimObject_candidate = 0;
                g_pFightState->bAttackAnimState_candidate = 0;
                g_pFightState->bFaintMessageCount_candidate = 0;
                for (i = 0; i < g_pFightState->bFighterCount; i++) {
                    if (g_pFightState->pFighters[i].bFighterType != Enemy) {
                        g_nLastDamage = (u16)ResolveEnemyAttack(g_pFightState->bActiveFighterIndex, i);
                        if (g_nLastDamage != 0)
                            ShowDamageNumber_candidate((u8)i, g_nLastDamage);
                        if (g_nLastDamage > 999) {
                            // Overkill: the message carries the excess over
                            // 999 and g_nLastDamage is rewritten in place.
                            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = g_nLastDamage;
                            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bEffectId = g_pFightState->pFighters[i].pObject->wObjectType;
                            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bFlag = 0;
                            if (g_pFightState->bPendingStatusMessageVariant_candidate != 0x12)
                                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
                            g_nLastDamage = g_nLastDamage - 999;
                            ShowFloatingDamageNumber_candidate(g_nLastDamage, 3, i, 0);
                        } else if (g_nLastDamage != 0) {
                            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = g_nLastDamage;
                            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bEffectId = g_pFightState->pFighters[i].pObject->wObjectType;
                            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bFlag = 0;
                            if (g_pFightState->bPendingStatusMessageVariant_candidate != 0x12)
                                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
                            ShowFloatingDamageNumber_candidate(g_nLastDamage, 0, i, 0);
                        } else {
                            // Zero literal, not g_nLastDamage: on this path
                            // the compiler already holds a register known to
                            // be 0 and reuses it, which is what the ROM does.
                            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].wDamage = 0;
                            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bEffectId = g_pFightState->pFighters[i].pObject->wObjectType;
                            g_pFightState->aFaintMessages_candidate[g_pFightState->bFaintMessageCount_candidate].bFlag = 1;
                            if (g_pFightState->bPendingStatusMessageVariant_candidate != 0x12)
                                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
                            ShowFloatingDamageNumber_candidate(g_nLastDamage, 2, i, 0);
                        }
                        g_pFightState->bFaintMessageCount_candidate++;
                    }
                }
                if (g_pFightState->dwBattleResultPending == 0)
                    ShowBattleMessage(FaintResult, 0, 0);
            }
            if (obj->bEnemyAttackPhase_candidate != 0xff || obj->bAttackOutcomeState != 3)
                goto skipPhase0;
            goto finish;
        }

    skipPhase0:
        if (obj->wObjectType != 0x3e)
            return;
        if ((obj->dwFlags & 0x40000) == 0)
            return;
    finish:
        g_pFightState->pAttackAnimObject_candidate = 0;
        g_pFightState->bAttackAnimState_candidate = 0;
        obj->bAttackOutcomeState = 0;
        active->bSpellId = Flipendo;
        obj->bEnemyAttackPhase_candidate = 0;
        obj->bActionFlags = 0x41;
        obj->dwFlags &= 0xfffbffff;
        return;
    }
    }
}
