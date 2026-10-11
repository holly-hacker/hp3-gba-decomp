#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/graphics.h"

#define FIGHTER(i) (g_pFightState->pFighters[i])
#define PENDING(i) (g_pFightState->pPendingFighters_candidate[i])

// Rebuilds the battle's Objects after returning from a submode: each live
// then pending fighter's Actor is re-allocated and restored from the snapshot
// ExitBattle took (keeping the new Actor's list links), then the turn-order
// icons are respawned and the active fighter's icon is highlighted.
void RestoreFighterObjects_candidate(void)
{
    u8 i;
    u8 k;
    Actor *obj;
    Actor *shadow;
    ListNode *pNext;
    ListNode *pPrev;

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        obj = AllocDefaultActor();
        pNext = obj->node.pNext;
        pPrev = obj->node.pPrev;
        *obj = g_pFightState->aSuspendedFighterObjects_candidate[i];
        obj->node.pNext = pNext;
        obj->node.pPrev = pPrev;
        FIGHTER(i).pObject = obj;
        obj->dwFlags &= ~ActorFlagHasPaletteSlot;
        obj->dwFlags |= ActorFlagAnimFrameLoaded;
        obj->pLinkedActor_candidate = 0;
        obj->pWindupParticleEmitter = 0;
        obj->oam.affineMode = 0;
        SetObjectAffineSlotId(&obj->oam, 0);

        if (FIGHTER(i).pObject->wActorType > 3)
            AttachObjectPaletteUnshared(FIGHTER(i).pObject,
                                                  g_pMonsterGraphicsTable[FIGHTER(i).pObject->wActorType - 4].battle.pPalette);
        else
            AttachObjectPaletteUnshared(FIGHTER(i).pObject,
                                                  g_aFighterAnimTable[FIGHTER(i).pObject->wActorType].aRecords[0].pPalette);

        if (sub_08012E0C(i)) {
            shadow = AllocDefaultActor();
            shadow->wActorType = FIGHTER(i).pObject->wActorType;
            shadow->bUnk_0x7C = 0;
            shadow->oam.priority = 1;
            shadow->bDepthSortBias = 0xC8;
            shadow->dwUnk_0x28 = 1;
            shadow->dwFlags = 0x6019;
            shadow->anim.bAnimFrameDelay = 1;
            AttachObjectPalette(shadow, g_MonsterShadowGfxRow.pPalette);
            SetActorAnimData(shadow, &g_MonsterShadowGfxRow, g_MonsterShadowAnimData, 0);
            shadow->anim.pAnimFrameCursor = obj->anim.pAnimFrameCursor;

            if (FIGHTER(i).pObject->wActionVariant == 2)
                shadow->anim.bAnimFrameCounter = 0;

            shadow->pOwnerActor = obj;
            obj->pShadowActor = shadow;
        }

        if (FIGHTER(i).bStatusFlags & Paralyzed) {
            FIGHTER(i).pObject->wActionVariant = 2;

            if (FIGHTER(i).bFighterType != Enemy) {
                SpawnParalysisEffect(FIGHTER(i).pObject);
                QueueObjPaletteLoad(&g_aFighterAnimTable[FIGHTER(i).pObject->wActorType].aRecords[6].pPalette->aColors[1],
                             (FIGHTER(i).pObject->oam.paletteNum << 4) + 1, 0xF);
            }
        }

        if (FIGHTER(i).bStatusFlags & Poisoned) {
            FIGHTER(i).pObject->wActionVariant = 1;
            SpawnParalysisEffect(FIGHTER(i).pObject);
            QueueObjPaletteLoad(&g_aFighterAnimTable[FIGHTER(i).pObject->wActorType].aRecords[7].pPalette->aColors[1],
                         (FIGHTER(i).pObject->oam.paletteNum << 4) + 1, 0xF);
        }
    }

    for (k = 0; k < g_pFightState->bPendingFighterCount_candidate; k++, i++) {
        obj = AllocDefaultActor();
        pNext = obj->node.pNext;
        pPrev = obj->node.pPrev;
        *obj = g_pFightState->aSuspendedFighterObjects_candidate[i];
        obj->node.pNext = pNext;
        obj->node.pPrev = pPrev;
        PENDING(k).pObject = obj;
        obj->dwFlags &= ~ActorFlagHasPaletteSlot;
        obj->dwFlags |= ActorFlagAnimFrameLoaded;
        obj->pLinkedActor_candidate = 0;
        obj->pWindupParticleEmitter = 0;
        obj->oam.affineMode = 0;
        SetObjectAffineSlotId(&obj->oam, 0);
        AttachObjectPaletteUnshared(PENDING(k).pObject,
                                              g_aFighterAnimTable[PENDING(k).pObject->wActorType].aRecords[0].pPalette);
    }

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        if (FIGHTER(i).bFighterType != Enemy) {
            SpawnTurnOrderIcon(FIGHTER(i).bFighterType, 1, i, FIGHTER(i).pObject->oam.paletteNum);
            g_pFightState->pStagingFighters[FIGHTER(i).bFighterType].pObject = FIGHTER(i).pObject;
        } else {
            SpawnTurnOrderIcon(FIGHTER(i).bRosterIndex, 0, i, FIGHTER(i).pObject->oam.paletteNum);
            g_pFightState->pStagingFighters[g_pFightState->aEnemySlotTurnOrderIndex[FIGHTER(i).bSlotParam]].pObject =
                FIGHTER(i).pObject;
        }

        if (i == g_pFightState->bActiveFighterIndex) {
            g_pFightState->apTurnOrderIconObjects[i]->pLinkedActor_candidate->bDepthSortBias = 0xFD;
            g_pFightState->apTurnOrderIconObjects[i]->bDepthSortBias = 0x80;
        } else {
            g_pFightState->apTurnOrderIconObjects[i]->pLinkedActor_candidate->bDepthSortBias = 0xFF;
            g_pFightState->apTurnOrderIconObjects[i]->bDepthSortBias = 0xFE;
        }
    }

    if (FIGHTER(g_pFightState->bActiveFighterIndex).bFighterType == Enemy)
        SetActorAnimFrame(g_pFightState->apTurnOrderIconObjects[g_pFightState->bActiveFighterIndex]->pLinkedActor_candidate, 3);
    else
        SetActorAnimFrame(g_pFightState->apTurnOrderIconObjects[g_pFightState->bActiveFighterIndex]->pLinkedActor_candidate, 2);
}
