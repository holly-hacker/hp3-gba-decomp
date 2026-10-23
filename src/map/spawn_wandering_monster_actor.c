#include "types.h"
#include "actor.h"
#include "combat_fighter.h"
#include "game_state.h"
#include "npc_actor.h"
#include "palette.h"
#include "map.h"

Actor *SpawnWanderingMonsterActor(u8 monsterId, u16 x, u16 y, u8 encounterId, u8 variant, u8 kind)
{
    Actor *pActor;
    s32 i;
    u32 slotMonster;

    pActor = AllocActorOfType(RoomActorType_WanderingMonster);
    SetActorPosition(pActor, x, y);
    pActor->nMoveSpeed = 1;
    pActor->bRoomActorKind_candidate = monsterId;
    pActor->bFighterIndex = encounterId;
    pActor->bEncounterVariant = variant;
    pActor->bReceivedRewardId = kind;
    pActor->dwFlags = ActorFlagVisible | ActorFlagWantsCollisionCheck | ActorFlagHasAnimation
                      | ActorFlagTerrainCollisionA_candidate | ActorFlagFourWayDirections_candidate
                      | ActorFlagTerrainDrawLayer;
    pActor->bTerrainBlockResponse = TerrainBlockNone;
    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = TickWanderingMonsterActor;
    pActor->apfnCollisionCallback[0] = HandleWanderingMonsterCollision;
    pActor->apfnCollisionCallback[1] = NULL;
    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0x80;

    // Show the "?" silhouette while any monster of the roster is unanalyzed.
    for (i = 0; i < 3; i++)
    {
        slotMonster = g_aRandomEncounters[encounterId].aKinds[kind].aVariants[variant][i];
        if (slotMonster != 0xFF && g_saveStateBlock.abMonsterDocLevel[slotMonster] <= 2)
            break;
    }

    if (i == 3)
    {
        SetActorPendingPalette(pActor, g_pMonsterGraphicsTable[monsterId].overworld.pPalette);
        SetActorAnimData(pActor, &g_pMonsterGraphicsTable[monsterId].overworld, g_WanderingMonsterAnimData, 0);
    }
    else
    {
        SetActorPendingPalette(pActor, g_UnknownWanderingMonsterAsset.pPalette);
        SetActorAnimData(pActor, &g_UnknownWanderingMonsterAsset, g_UnknownWanderingMonsterAnimData, 0);
    }

    pActor->dwStateTimer = 0;
    SetActorActionState(pActor, 15);
    SetActorActionSubState(pActor, 0);
    pActor->pShadowActor = SpawnShadowActor(pActor);
    return pActor;
}
