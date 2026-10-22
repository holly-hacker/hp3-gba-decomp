#include "types.h"
#include "actor.h"
#include "area.h"
#include "hero.h"
#include "mem.h"
#include "npc_actor.h"
#include "palette.h"

// Spawns a party follower on the player and restarts the party trail.
Actor *SpawnPartyFollowerActor(u8 characterId)
{
    Actor *pActor;
    const RoomEntryPoint *pEntry;

    pActor = AllocActorOfType(RoomActorType_PartyFollower);
    pEntry = FindRoomEntryPoint(g_abRoomScriptExitParams_candidate[0], 0);
    SnapActorPosition(pActor, g_pPlayerActor->pos.x, g_pPlayerActor->pos.y);
    pActor->bFacing = pEntry->bFacing;
    pActor->wCharacterId_candidate = characterId;
    pActor->oam.objMode = 0;
    pActor->oam.bpp8 = 0;
    pActor->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic | ActorFlagHasAnimation
        | ActorFlagTerrainDrawLayer;
    SetActorActionSubState(pActor, 0);
    pActor->nMoveSpeed = 0x28000;
    pActor->pfnTick = TickPartyFollowerActor;
    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0x80;
    SetActorPendingPalette(pActor, g_aPartyWalkAssets[pActor->wCharacterId_candidate].pPalette);
    SetActorAssetRecord(pActor, &g_aPartyWalkAssets[pActor->wCharacterId_candidate]);
    SetActorAnimFrame(pActor, g_abPartyStandFrames[pActor->bFacing]);
    if (pActor->wCharacterId_candidate != 4)
        SpawnShadowActor(pActor);

    memset(g_pPartyTrail, 0, PARTY_TRAIL_LENGTH * sizeof(PartyTrailStep));
    g_bPartyTrailWriteIndex = 0;
    g_bPartyTrailReadIndex0 = 29;
    g_bPartyTrailReadIndex1 = 14;
    return pActor;
}
