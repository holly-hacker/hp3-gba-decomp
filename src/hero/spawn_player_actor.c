#include "types.h"
#include "actor.h"
#include "area.h"
#include "commands.h"
#include "hero.h"
#include "mem.h"
#include "npc_actor.h"
#include "palette.h"
#include "overworld/room.h"
#include "overworld/overworld.h"

Actor *SpawnPlayerActor(u8 characterId)
{
    const RoomEntryPoint *pEntry;

    g_pPlayerActor = AllocActorOfType(RoomActorType_Player);
    pEntry = FindRoomEntryPoint(g_abRoomScriptExitParams_candidate[0], 0);
    g_abQuestEventState[QUEST_SPAWN_ID_COPY] = g_abRoomScriptExitParams_candidate[0];
    SnapActorPosition(g_pPlayerActor, pEntry->nX << 16, pEntry->nY << 16);
    g_pPlayerActor->bFacing = pEntry->bFacing;
    g_pPlayerActor->wCharacterId_candidate = characterId;
    g_pPlayerActor->anim.bAnimFrameDelay = 3;
    g_pPlayerActor->oam.objMode = 0;
    g_pPlayerActor->oam.bpp8 = 0;
    g_pPlayerActor->dwFlags = ActorFlagVisible | ActorFlagWantsCollisionCheck | ActorFlagHasTickLogic
        | ActorFlagHasAnimation | ActorFlagTerrainCollisionA_candidate | ActorFlagTerrainDrawLayer;
    g_pPlayerActor->bTerrainBlockResponse = TerrainBlockSlide;
    SetActorActionState(g_pPlayerActor, 0x21);
    SetActorPrevActionState(g_pPlayerActor, 0x21);
    g_pPlayerActor->nMoveSpeed = 0x28000;
    g_pPlayerActor->pfnTick = TickPlayerActor;
    g_pPlayerActor->apfnCollisionCallback[0] = HandlePlayerWorldActorCollision;
    g_pPlayerActor->oam.priority = 1;
    g_pPlayerActor->bDepthSortBias = 0x80;
    SetActorPendingPalette(g_pPlayerActor, g_aPartyWalkAssets[g_pPlayerActor->wCharacterId_candidate].pPalette);
    SetActorAssetRecord(g_pPlayerActor, &g_aPartyWalkAssets[g_pPlayerActor->wCharacterId_candidate]);
    SetActorAnimFrame(g_pPlayerActor, g_abPartyStandFrames[g_pPlayerActor->bFacing]);
    g_OverworldControlState.aSlots[0].pActor = g_pPlayerActor;
    if (g_pPlayerActor->wCharacterId_candidate != 4)
        g_pPlayerShadowActor_candidate = SpawnShadowActor(g_pPlayerActor);

    g_pPartyTrail = AllocZeroed(PARTY_TRAIL_LENGTH * sizeof(PartyTrailStep));
    g_bPartyTrailWriteIndex = 0;
    g_bPartyTrailReadIndex0 = 29;
    g_bPartyTrailReadIndex1 = 14;
    g_PartyTrailLastPos.x = pEntry->nX << 16;
    g_PartyTrailLastPos.y = pEntry->nY << 16;
    return g_pPlayerActor;
}
