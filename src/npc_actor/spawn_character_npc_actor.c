#include "types.h"
#include "hero.h"
#include "palette.h"
#include "npc_actor.h"

// Spawns an NPC standing in for party member characterId, at its party actor's
// position and facing (the player's when it is not in the party).
Actor *SpawnCharacterNpcActor(u8 characterId)
{
    Actor *pSource;
    Actor *pActor;

    if (g_pPlayerActor->wCharacterId_candidate == characterId)
        pSource = g_pPlayerActor;
    else if (g_pFollowerActor0->wCharacterId_candidate == characterId)
        pSource = g_pFollowerActor0;
    else if (g_pFollowerActor1->wCharacterId_candidate == characterId)
        pSource = g_pFollowerActor1;
    else
        pSource = g_pPlayerActor;

    pActor = AllocActorOfType(6);
    SnapActorPosition(pActor, pSource->pos.x, pSource->pos.y);
    pActor->dwFlags = ActorFlagVisible | ActorFlagWantsCollisionCheck | ActorFlagHasAnimation | ActorFlagUnk2000
                     | ActorFlagFourWayDirections_candidate | ActorFlagTerrainDrawLayer;
    SetActorActionState(pActor, 0);
    pActor->anim.bAnimFrameDelay = 0;
    pActor->bFighterIndex = g_abCharacterNpcKinds[characterId];
    pActor->bFacing = pSource->bFacing;
    pActor->bRoomActorKind_candidate = 0;
    pActor->pfnTick = TickNpcActor;
    pActor->apfnCollisionCallback[0] = HandleNpcActorTouch;
    pActor->apfnCollisionCallback[1] = NULL;
    SetActorPendingPalette(pActor, g_aActorTypeAssets[pActor->bFighterIndex].pPalette);
    SetActorAssetRecord(pActor, &g_aActorTypeAssets[pActor->bFighterIndex]);
    SetActorAnimFrame(pActor, g_abRoomActorUnk6Frames[g_adwRoomActorUnk6FrameRows[pActor->bFighterIndex]][pActor->bFacing]);
    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0x80;
    pActor->oam.hFlip = pActor->bFacing == Direction4Left;
    pActor->nMoveSpeed = 0x10000;
    pActor->bFlags_0x94_candidate &= ~4;
    return pActor;
}
