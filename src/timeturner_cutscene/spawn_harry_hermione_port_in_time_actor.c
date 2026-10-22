#include "types.h"
#include "gen/graphics/overworld.h"
#include "palette.h"
#include "timeturner_cutscene.h"

#define ACTOR g_HarryHermionePortInTime.apActors[index]

// Spawns cutscene actor `index` with its animation and a drop shadow.
void SpawnHarryHermionePortInTimeActor(u32 index)
{
    Actor *pShadow;

    ACTOR = AllocActorOfType(6);
    ACTOR->wCharacterId_candidate = index;
    ACTOR->bFighterIndex = index;
    ACTOR->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic | ActorFlagHasAnimation
                     | ActorFlagFourWayDirections_candidate;
    SetActorActionState(ACTOR, 0);
    ACTOR->anim.bAnimFrameDelay = 0;
    ACTOR->bFacing = Direction4Left;
    SetActorPendingPalette(ACTOR, g_aHarryHermionePortInTimeActorAssets[ACTOR->bFighterIndex].pPalette);
    SetActorAnimData(ACTOR, &g_aHarryHermionePortInTimeActorAssets[ACTOR->bFighterIndex],
                     g_aHarryHermionePortInTimeAnims[index], 0);
    ACTOR->oam.priority = 0;
    ACTOR->bDepthSortBias = 0x80;
    ACTOR->nMoveSpeed = 0;

    pShadow = AllocActorOfType(0x11);
    pShadow->bFacing = 0;
    pShadow->oam.objMode = 1;
    pShadow->oam.bpp8 = 0;
    pShadow->dwFlags = ActorFlagVisible;
    pShadow->bDrawFlags = 0;
    pShadow->anim.bAnimFrameDelay = 0;
    pShadow->nMoveSpeed = 0;
    pShadow->oam.priority = ACTOR->oam.priority;
    pShadow->bDepthSortBias = 0xFF;
    SetActorPendingPalette(pShadow, gOverworldPlayer004Palette);
    SetActorAssetRecord(pShadow, &g_HarryHermionePortInTimeShadowGfx);
    SnapActorPosition(pShadow, ACTOR->posPrev.x, ACTOR->posPrev.y);
    pShadow->oam.objMode = 1;
    pShadow->pOwnerActor = ACTOR;
    ACTOR->pLinkedActor_candidate = pShadow;
}
