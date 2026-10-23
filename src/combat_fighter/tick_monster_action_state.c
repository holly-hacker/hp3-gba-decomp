#include "types.h"
#include "combat_fighter.h"
#include "sound.h"
#include "combat_dialog.h"
#include "combat_gauge.h"
#include "random.h"
#include "combat.h"

// Enemy-side per-actor tick dispatcher, mirroring TickPlayerActionState's
// shape: a switch on Actor+0x8D (bActionState), every case branching into
// a shared no-op tail rather than returning directly. Registered as
// InitMonsterBattleActor's pActor->pfnTick.
void TickMonsterActionState(Actor *actor)
{
    u8 *pFlags;
    s32 fighterType;
    BattleFighter *active;
    u8 monsterIndex;
    u32 i;

    if (actor->dwFlags & ActorFlagPendingDestroy)
        return;

    UpdateMonsterScreenShake(actor);

    switch (actor->bActionState) {
    case 0:
    {
        pFlags = &actor->bActionFlags;
        if ((*pFlags & 1) == 0)
            return;

        if (actor->wActionVariant != 2)
            SetMonsterActorAnim(actor, 0);

        *pFlags &= 0xfe;
        return;
    }

    case 0xf:
        if (actor->vel.x != 0 || actor->vel.y != 0)
            return;

        SetActorActionState(actor, 0);
        return;

    case 2:
    {
        pFlags = &actor->bActionFlags;
        if (*pFlags & 1) {
            SetMonsterActorAnim(actor, 7);
            *pFlags &= 0xfe;
        }

        if ((actor->dwFlags & ActorFlagActionAnimDone) == 0)
            return;

        SetActorActionState(actor, 0);
        return;
    }

    case 1:
    {
        if (actor->bActionFlags & 1) {
            if (actor->wActorType != 0x3a) {
                SetActorFlippedX(actor, 1);
                PlaySoundById(0x9d);
            } else {
                PlaySoundById(0x14);
            }
            actor->dwStateTimer = 0x14;
            actor->bActionFlags &= 0xfe;
        }

        if (actor->wActorType != 0x3a) {
            ClearActorOrbitX(actor);
            ClearActorOrbitY(actor);
            SetActorVelocity(actor, 0xfffa0000, 0);
        }

        if (--actor->dwStateTimer != 0)
            return;

        if (actor->pLinkedActor != 0)
            DestroyLinkedActor(actor->pLinkedActor);

        if (actor->pShadowActor != 0)
            actor->pShadowActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;

        if (g_pFightState->bHitResultCount == 0)
            CheckBattleVictory(actor);

        if (g_pFightState->dwBattleResultPending != 0) {
            if (actor->wActorType == 0x3a)
                return;
            actor->dwFlags &= ~ActorFlagVisible;
            return;
        }

        if (actor->wActorType == (fighterType = 0x3a))
            return;

        actor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;

        if ((u16)(actor->wActorType - 0x31) > 2)
            return;

        FreeActor(actor->pShadowActor);
        return;
    }

    case 0x1a:
    {
        active = &g_pFightState->pFighters[g_pFightState->bActiveFighterIndex];
        monsterIndex = active->bRosterIndex;

        if (actor->bActionFlags == 0x21) {
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
                         || candidate->pActor == 0
                         || (u16)candidate->nFaintedFlag == 0xffff);
                active->bSelectedActionIndex = roll;
            }

            g_pFightState->savedPos = actor->pos;

            if (MonsterTable[active->bRosterIndex].bSpecialChance == 100) {
                g_pFightState->bAttackMoveTicks = 5;
                if (active->bRosterIndex != 0x36) {
                    u32 destX, destY;
                    if ((u8)(active->bRosterIndex - 0x1a) < 3) {
                        destX = 0x380000;
                        destY = 0x2c0000;
                    } else {
                        destX = 0x480000;
                        destY = 0x540000;
                    }

                    StartActorMove(actor, destX, destY, 3);
                }
            } else {

                u32 roster;
                u8 targetSlot;
                g_pFightState->bAttackMoveTicks = 10;
                roster = active->bRosterIndex;
                targetSlot = g_pFightState->pFighters[active->bSelectedActionIndex].bSlotParam;
                StartActorMove(actor,
                    (g_aPartySlotPos[targetSlot][0] - g_aMonsterAttackOffset[roster][0]) << 16,
                    (g_aPartySlotPos[targetSlot][1] - g_aMonsterAttackOffset[roster][1]) << 16,
                    8);


                SetActorAffineTransform(actor, 0x10000, 0x10000, 0, 3);

                if ((u8)(active->bRosterIndex - 0x37) <= 1) {
                    StartActorAffineScaleTween(actor, 0x13333, 0x13333, 8);
                } else {
                    StartActorAffineScaleTween(actor, 0x18000, 0x18000, 8);
                }
            }

            actor->bActionFlags &= 0xfe;
        } else if (actor->bActionFlags == 0x41) {
            SetMonsterActorAnim(actor, 0);

            g_pFightState->bAttackMoveTicks = 0x14;

            StartActorMove(actor, g_pFightState->savedPos.x, g_pFightState->savedPos.y, 3);

            if (MonsterTable[active->bRosterIndex].bSpecialChance != 100)
                StartActorAffineScaleTween(actor, 0x10000, 0x10000, 3);

            actor->bActionFlags &= 0xfe;
        }

        if (actor->bActionFlags & 0x20) {
            g_pFightState->bAttackMoveTicks--;
            if (g_pFightState->bAttackMoveTicks != 0)
                return;

            actor->wTimedMoveTicks = 0;
            SetActorVelocity(actor, 0, 0);
            actor->bActionFlags = 1;
            return;
        }
        if (actor->bActionFlags & 0x40) {
            g_pFightState->bAttackMoveTicks--;
            if (g_pFightState->bAttackMoveTicks != 0)
                return;

            actor->wMoveDuration = 0;
            actor->bActionState = 0;
            actor->bActionFlags |= 1;

            PostActionBattleCheck();
            if (actor->oam.affineMode != 3)
                return;

            ReleaseActorAffineSlot(actor);
            return;
        }

        if (actor->bActionFlags & 1) {
            SetMonsterActorAnim(actor, 0xc);
            actor->bActionFlags &= 0xfe;
        }

        if (actor->dwFlags & ActorFlagSpecialMoveTrigger) {
            if (MonsterTable[monsterIndex].bSpecialChance == 100) {
                g_nLastDamage = (u16)ResolveEnemyAttack(g_pFightState->bActiveFighterIndex, active->bSelectedActionIndex);
                RollMonsterSpecialEffect(monsterIndex, active->bSelectedActionIndex, g_nLastDamage);
            }

            if (actor->wActorType == 0x3e) {
                actor->anim.param.bEventMarker = 0xff;
                actor->scriptState.bytes.bAttackOutcomeState = 2;
            }

            actor->dwFlags &= ~ActorFlagSpecialMoveTrigger;
        }

        if (((actor->dwFlags & ActorFlagActionAnimDone) == 0) || (actor->anim.param.bEventMarker == 0xff)) {
            if (actor->anim.param.bEventMarker != 0xff)
                goto skipPhase0;

            if (actor->scriptState.bytes.bAttackOutcomeState != 1)
                goto phase2;
        }
        {
        phase0:
            // g_nLastDamage is shared with the ActorFlagSpecialMoveTrigger block above:
            // exactly one of the two ResolveEnemyAttack calls fires per
            // attack (bSpecialChance==100 there, <=99 here), and this tail
            // always reads whichever one just ran.
            actor->anim.param.bEventMarker = 0;

            if (MonsterTable[monsterIndex].bSpecialChance <= 99) {
                g_nLastDamage = (u16)ResolveEnemyAttack(g_pFightState->bActiveFighterIndex, active->bSelectedActionIndex);
                if (g_nLastDamage != 0)
                    RollMonsterSpecialEffect(monsterIndex, active->bSelectedActionIndex, g_nLastDamage);
            }

            if (g_nLastDamage != 0) {
                StageFighterDamage(active->bSelectedActionIndex, g_nLastDamage);
            } else {
                PlaySoundById(0x4b);
            }

            actor->bActionFlags = 0x41;
            actor->dwFlags &= ~ActorFlagActionAnimDone;

            ShowAttackResult(actor, active->bSelectedActionIndex);

            phase2:
            if (actor->anim.param.bEventMarker != 0xff)
                goto skipPhase0;

            if (actor->scriptState.bytes.bAttackOutcomeState == 2) {
                if (MonsterTable[monsterIndex].bSpecialChance <= 99) {
                    g_nLastDamage = (u16)ResolveEnemyAttack(
                        g_pFightState->bActiveFighterIndex,
                        g_pFightState->pFighters[g_pFightState->bActiveFighterIndex].bSelectedActionIndex);
                }

                if (g_nLastDamage != 0)
                    StageFighterDamage(active->bSelectedActionIndex, g_nLastDamage);

                active->bSpellId = Flipendo;
                ShowAttackResult(actor, active->bSelectedActionIndex);
            }

            if (actor->anim.param.bEventMarker != 0xff)
                goto skipPhase0;

            if (actor->scriptState.bytes.bAttackOutcomeState == 4) {
                // Hit sweep: every living non-enemy fighter is resolved as a
                // target and queues a hit result.
                actor->scriptState.bytes.bAttackOutcomeState = 0;
                g_pFightState->pAttackOutcomeActor = 0;
                g_pFightState->bAttackOutcomeState = 0;
                g_pFightState->bHitResultCount = 0;
                for (i = 0; i < g_pFightState->bFighterCount; i++) {
                    if (g_pFightState->pFighters[i].bFighterType != Enemy) {
                        g_nLastDamage = (u16)ResolveEnemyAttack(g_pFightState->bActiveFighterIndex, i);
                        if (g_nLastDamage != 0)
                            StageFighterDamage((u8)i, g_nLastDamage);
                        if (g_nLastDamage > 999) {
                            // Handle crit damage
                            g_pFightState->aHitResults[g_pFightState->bHitResultCount].wDamage = g_nLastDamage;
                            g_pFightState->aHitResults[g_pFightState->bHitResultCount].bTargetKind = g_pFightState->pFighters[i].pActor->wActorType;
                            g_pFightState->aHitResults[g_pFightState->bHitResultCount].bMissed = 0;
                            if (g_pFightState->bPendingStatusMessageVariant != 0x12)
                                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant);
                            g_nLastDamage = g_nLastDamage - 999;
                            ShowFloatingDamageNumber(g_nLastDamage, 3, i, 0);
                        } else if (g_nLastDamage != 0) {
                            g_pFightState->aHitResults[g_pFightState->bHitResultCount].wDamage = g_nLastDamage;
                            g_pFightState->aHitResults[g_pFightState->bHitResultCount].bTargetKind = g_pFightState->pFighters[i].pActor->wActorType;
                            g_pFightState->aHitResults[g_pFightState->bHitResultCount].bMissed = 0;
                            if (g_pFightState->bPendingStatusMessageVariant != 0x12)
                                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant);
                            ShowFloatingDamageNumber(g_nLastDamage, 0, i, 0);
                        } else {
                            // Zero literal, not g_nLastDamage: on this path
                            // the compiler already holds a register known to
                            // be 0 and reuses it, which is what the ROM does.
                            g_pFightState->aHitResults[g_pFightState->bHitResultCount].wDamage = 0;
                            g_pFightState->aHitResults[g_pFightState->bHitResultCount].bTargetKind = g_pFightState->pFighters[i].pActor->wActorType;
                            g_pFightState->aHitResults[g_pFightState->bHitResultCount].bMissed = 1;
                            if (g_pFightState->bPendingStatusMessageVariant != 0x12)
                                ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant);
                            ShowFloatingDamageNumber(g_nLastDamage, 2, i, 0);
                        }
                        g_pFightState->bHitResultCount++;
                    }
                }
                if (g_pFightState->dwBattleResultPending == 0)
                    ShowBattleMessage(FaintResult, 0, 0);
            }
            if (actor->anim.param.bEventMarker != 0xff || actor->scriptState.bytes.bAttackOutcomeState != 3)
                goto skipPhase0;
            goto finish;
        }

    skipPhase0:
        if (actor->wActorType != 0x3e)
            return;
        if ((actor->dwFlags & ActorFlagActionAnimDone) == 0)
            return;
    finish:
        g_pFightState->pAttackOutcomeActor = 0;
        g_pFightState->bAttackOutcomeState = 0;
        actor->scriptState.bytes.bAttackOutcomeState = 0;
        active->bSpellId = Flipendo;
        actor->anim.param.bEventMarker = 0;
        actor->bActionFlags = 0x41;
        actor->dwFlags &= ~ActorFlagActionAnimDone;
        return;
    }
    }
}
