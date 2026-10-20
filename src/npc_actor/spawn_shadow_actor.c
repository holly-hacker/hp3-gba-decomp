#include "types.h"
#include "gen/graphics/overworld.h"
#include "palette.h"
#include "npc_actor.h"

// Spawns the semi-transparent drop shadow that follows pOwner on its draw layer.
Actor *SpawnShadowActor(Actor *pOwner)
{
    Actor *pShadow = AllocActorOfType(0x11);

    pShadow->bFacing = 0;
    pShadow->oam.objMode = 0;
    pShadow->oam.bpp8 = 0;
    pShadow->dwFlags = ActorFlagVisible;
    pShadow->bDrawFlags = 0;
    pShadow->anim.bAnimFrameDelay = 0;
    pShadow->nMoveSpeed = 0x10000;
    pShadow->oam.priority = pOwner->oam.priority;
    pShadow->bDepthSortBias = 0xFF;
    pShadow->pfnTick = TickShadowActor;
    SetActorPendingPalette(pShadow, gOverworldPlayer004Palette);
    SetActorAssetRecord(pShadow, &g_ShadowActorGfx);
    SnapActorPosition(pShadow, pOwner->posPrev.x, pOwner->posPrev.y);
    pShadow->pOwnerActor = pOwner;
    pShadow->oam.objMode = 1;
    pOwner->pShadowActor = pShadow;
    return pShadow;
}
