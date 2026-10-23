#include "lupin_potion_cutscene.h"
#include "palette.h"
#include "random.h"
#include "gen/graphics/overworld.h"

// Spawns a cast member walking at a random point of its cycle, with its drop shadow.
Actor *SpawnLupinPotionCastActor(s32 index)
{
    Actor *pActor = AllocActorOfType(RoomActorType_Npc);
    Actor *pShadow;

    pActor->wSubtype = index;
    pActor->bFighterIndex = index;
    pActor->bActionSubState = 0;
    SetActorPosition(pActor, g_aLupinPotionCastPositions[index].x, g_aLupinPotionCastPositions[index].y);
    pActor->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic | ActorFlagHasAnimation
                      | ActorFlagFourWayDirections;
    SetActorActionState(pActor, 0);
    pActor->anim.bAnimFrameDelay = 0;
    pActor->bFacing = Direction4Left;
    pActor->pfnTick = TickLupinPotionCastActor;
    SetActorPendingPalette(pActor, g_aLupinPotionCastAssets[pActor->bFighterIndex].pPalette);
    SetActorAnimDataAtCommand(pActor, &g_aLupinPotionCastAssets[pActor->bFighterIndex],
                              g_aLupinPotionWalkAnims[pActor->bFacing], Mt19937RandMax2(7));
    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0x80;
    pActor->oam.hFlip = pActor->bFacing > Direction4Down;
    pActor->nMoveSpeed = 0;

    pShadow = AllocActorOfType(RoomActorType_Shadow);
    pShadow->bFacing = 0;
    pShadow->oam.objMode = 0;
    pShadow->oam.bpp8 = 0;
    pShadow->dwFlags = ActorFlagVisible;
    pShadow->bDrawFlags = 0;
    pShadow->anim.bAnimFrameDelay = 0;
    pShadow->nMoveSpeed = 0;
    pShadow->oam.priority = pActor->oam.priority;
    pShadow->bDepthSortBias = 0xFF;
    pShadow->pfnTick = TickLupinPotionShadowActor;
    SetActorPendingPalette(pShadow, gOverworldPlayer004Palette);
    SetActorAssetRecord(pShadow, &g_LupinPotionShadowGfx);
    SnapActorPosition(pShadow, pActor->posPrev.x, pActor->posPrev.y);
    pShadow->pOwnerActor = pActor;
    pActor->pLinkedActor = pShadow;
    return pActor;
}
