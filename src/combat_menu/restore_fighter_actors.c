#include "types.h"
#include "battle/battle.h"
#include "combat_menu.h"
#include "color.h"
#include "combat_2.h"
#include "graphics/display.h"
#include "particles.h"

#define FIGHTER(i) (g_pFightState->pFighters[i])
#define PENDING(i) (g_pFightState->pPendingFighters_candidate[i])

// Rebuilds the battle's Actors after returning from a submode: each live
// then pending fighter's Actor is re-allocated and restored from the snapshot
// ExitBattle took (keeping the new Actor's list links), then the turn-order
// icons are respawned and the active fighter's icon is highlighted.
void RestoreFighterActors_candidate(void)
{
    u8 i;
    u8 k;
    Actor *actor;
    Actor *shadow;
    ListNode *pNext;
    ListNode *pPrev;

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        actor = AllocDefaultActor();
        pNext = actor->node.pNext;
        pPrev = actor->node.pPrev;
        *actor = g_pFightState->aSuspendedFighterActors_candidate[i];
        actor->node.pNext = pNext;
        actor->node.pPrev = pPrev;
        FIGHTER(i).pActor = actor;
        actor->dwFlags &= ~ActorFlagHasPaletteSlot;
        actor->dwFlags |= ActorFlagAnimFrameLoaded;
        actor->pLinkedActor_candidate = 0;
        actor->pWindupParticleEmitter = 0;
        actor->oam.affineMode = 0;
        SetActorAffineSlotId(&actor->oam, 0);

        if (FIGHTER(i).pActor->wActorType > 3)
            AttachActorPaletteUnshared(FIGHTER(i).pActor,
                                                  g_pMonsterGraphicsTable[FIGHTER(i).pActor->wActorType - 4].battle.pPalette);
        else
            AttachActorPaletteUnshared(FIGHTER(i).pActor,
                                                  g_aFighterAnimTable[FIGHTER(i).pActor->wActorType].aRecords[0].pPalette);

        if (sub_08012E0C(i)) {
            shadow = AllocDefaultActor();
            shadow->wActorType = FIGHTER(i).pActor->wActorType;
            shadow->bUnk_0x7C = 0;
            shadow->oam.priority = 1;
            shadow->bDepthSortBias = 0xC8;
            shadow->nMoveSpeed = 1;
            shadow->dwFlags = 0x6019;
            shadow->anim.bAnimFrameDelay = 1;
            AttachActorPalette(shadow, g_MonsterShadowGfxRow.pPalette);
            SetActorAnimData(shadow, &g_MonsterShadowGfxRow, g_MonsterShadowAnimData, 0);
            shadow->anim.pAnimFrameCursor = actor->anim.pAnimFrameCursor;

            if (FIGHTER(i).pActor->wActionVariant == 2)
                shadow->anim.bAnimFrameCounter = 0;

            shadow->pOwnerActor = actor;
            actor->pShadowActor = shadow;
        }

        if (FIGHTER(i).bStatusFlags & Paralyzed) {
            FIGHTER(i).pActor->wActionVariant = 2;

            if (FIGHTER(i).bFighterType != Enemy) {
                SpawnParalysisEffect(FIGHTER(i).pActor);
                QueueObjPaletteLoad(&g_aFighterAnimTable[FIGHTER(i).pActor->wActorType].aRecords[6].pPalette->aColors[1],
                             (FIGHTER(i).pActor->oam.paletteNum << 4) + 1, 0xF);
            }
        }

        if (FIGHTER(i).bStatusFlags & Poisoned) {
            FIGHTER(i).pActor->wActionVariant = 1;
            SpawnParalysisEffect(FIGHTER(i).pActor);
            QueueObjPaletteLoad(&g_aFighterAnimTable[FIGHTER(i).pActor->wActorType].aRecords[7].pPalette->aColors[1],
                         (FIGHTER(i).pActor->oam.paletteNum << 4) + 1, 0xF);
        }
    }

    for (k = 0; k < g_pFightState->bPendingFighterCount_candidate; k++, i++) {
        actor = AllocDefaultActor();
        pNext = actor->node.pNext;
        pPrev = actor->node.pPrev;
        *actor = g_pFightState->aSuspendedFighterActors_candidate[i];
        actor->node.pNext = pNext;
        actor->node.pPrev = pPrev;
        PENDING(k).pActor = actor;
        actor->dwFlags &= ~ActorFlagHasPaletteSlot;
        actor->dwFlags |= ActorFlagAnimFrameLoaded;
        actor->pLinkedActor_candidate = 0;
        actor->pWindupParticleEmitter = 0;
        actor->oam.affineMode = 0;
        SetActorAffineSlotId(&actor->oam, 0);
        AttachActorPaletteUnshared(PENDING(k).pActor,
                                              g_aFighterAnimTable[PENDING(k).pActor->wActorType].aRecords[0].pPalette);
    }

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        if (FIGHTER(i).bFighterType != Enemy) {
            SpawnTurnOrderIcon(FIGHTER(i).bFighterType, 1, i, FIGHTER(i).pActor->oam.paletteNum);
            g_pFightState->pStagingFighters[FIGHTER(i).bFighterType].pActor = FIGHTER(i).pActor;
        } else {
            SpawnTurnOrderIcon(FIGHTER(i).bRosterIndex, 0, i, FIGHTER(i).pActor->oam.paletteNum);
            g_pFightState->pStagingFighters[g_pFightState->aEnemySlotTurnOrderIndex[FIGHTER(i).bSlotParam]].pActor =
                FIGHTER(i).pActor;
        }

        if (i == g_pFightState->bActiveFighterIndex) {
            g_pFightState->apTurnOrderIconActors[i]->pLinkedActor_candidate->bDepthSortBias = 0xFD;
            g_pFightState->apTurnOrderIconActors[i]->bDepthSortBias = 0x80;
        } else {
            g_pFightState->apTurnOrderIconActors[i]->pLinkedActor_candidate->bDepthSortBias = 0xFF;
            g_pFightState->apTurnOrderIconActors[i]->bDepthSortBias = 0xFE;
        }
    }

    if (FIGHTER(g_pFightState->bActiveFighterIndex).bFighterType == Enemy)
        SetActorAnimFrame(g_pFightState->apTurnOrderIconActors[g_pFightState->bActiveFighterIndex]->pLinkedActor_candidate, 3);
    else
        SetActorAnimFrame(g_pFightState->apTurnOrderIconActors[g_pFightState->bActiveFighterIndex]->pLinkedActor_candidate, 2);
}
