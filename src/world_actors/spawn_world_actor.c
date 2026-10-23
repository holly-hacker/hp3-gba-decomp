#include "types.h"
#include "area.h"
#include "npc_actor.h"
#include "world_actors.h"

// Room actor constructor for RoomActorType_WorldActor, whose kind selects its sprite
// and behavior.
Actor *SpawnWorldActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordWorldActor *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_WorldActor);
    u32 kind;

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = ActorFlagVisible | ActorFlagWantsCollisionCheck | ActorFlagHasAnimation
                      | ActorFlagTerrainCollisionA_candidate | ActorFlagUnk2000
                      | ActorFlagTerrainDrawLayer;
    SetActorActionState(pActor, 0);
    pActor->bTerrainBlockResponse = TerrainBlockSlide;
    pActor->anim.bAnimFrameDelay = 1;
    WORLD_ACTOR_STATE(pActor)->bKind = pRecord->bKind;
    kind = pRecord->bKind;
    WORLD_ACTOR_STATE(pActor)->b62 = pRecord->b62;
    WORLD_ACTOR_STATE(pActor)->bPushable = pRecord->bPushable;
    WORLD_ACTOR_STATE(pActor)->bBreakable = pRecord->bBreakable;
    WORLD_ACTOR_STATE(pActor)->b65 = pRecord->b65;
    WORLD_ACTOR_STATE(pActor)->b66 = pRecord->b66;
    WORLD_ACTOR_STATE(pActor)->bChainRow = pRecord->bChainRow;
    pActor->bFacing = pRecord->bFacing;
    WORLD_ACTOR_STATE(pActor)->bActivated = 0;
    WORLD_ACTOR_STATE(pActor)->b6A = 0;
    WORLD_ACTOR_STATE(pActor)->b60 &= 0xFD;
    pActor->pfnTick = TickWorldActor;
    pActor->apfnCollisionCallback[0] = HandleWorldActorTouch;
    pActor->apfnCollisionCallback[1] = HandleWorldActorSecondaryTouch;
    SetActorPendingPalette(pActor, g_apWorldActorEffectData[WORLD_ACTOR_STATE(pActor)->bKind]);
    SetActorAnimData(pActor, g_apWorldActorAnimFrames[WORLD_ACTOR_STATE(pActor)->bKind],
                      (void *)g_abWorldActorAnimData[WORLD_ACTOR_STATE(pActor)->bKind], 0);

    if (kind == 26 || kind == 27 || kind == 28 || kind == 29 || kind == 30
        || kind == 31 || kind == 32 || kind == 33 || kind == 34 || kind == 35
        || kind == 36 || kind == 37 || kind == 38)
    {
        if (kind == 26 || kind == 29)
            pActor->oam.priority = 1;
        else
            pActor->oam.priority = 3;

        pActor->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionA_candidate
                             | ActorFlagTerrainDrawLayer);
    }
    else
    {
        pActor->oam.priority = 1;
    }

    pActor->bDepthSortBias = 0x80;
    WORLD_ACTOR_STATE(pActor)->bBrokenFrame = 0xFF;

    switch (kind)
    {
    case 66:
        pActor->oam.priority = 0;
        pActor->dwFlags &= ~(ActorFlagTerrainCollisionA_candidate | ActorFlagTerrainDrawLayer);
        break;
    case 12:
        pActor->oam.priority = 3;
        pActor->oam.hFlip = pActor->bFacing > DirectionDown;
        pActor->dwFlags &= ~ActorFlagTerrainCollisionA_candidate;
        break;
    case 40:
        pActor->dwFlags &= ~ActorFlagWantsCollisionCheck;
        // fall through
    case 39:
        pActor->oam.priority = 1;
        pActor->dwFlags &= ~ActorFlagTerrainCollisionA_candidate;
        break;
    case 0:
        SetActorAnimFrame(pActor, g_abWorldActorFacingFrames[pActor->bFacing]);
        pActor->oam.hFlip = pActor->bFacing > DirectionDown;
        pActor->pShadowActor = SpawnShadowActor(pActor);
        break;
    case 18:
    case 20:
        pActor->oam.objMode = 1;
        break;
    case 21:
        pActor->bDrawFlags |= ActorDrawFlagBlink;
        break;
    case 1:
        pActor->dwFlags |= ActorFlagHasTickLogic;
        pActor->dwFlags &= ~ActorFlagTerrainDrawLayer;
        break;
    case 81:
        pActor->dwFlags |= ActorFlagHasTickLogic;
        pActor->dwFlags &= ~ActorFlagTerrainDrawLayer;

        if (WORLD_ACTOR_STATE(pActor)->bPushable == 0)
            SetActorAnimFrame(pActor, 1);

        break;
    case 82:
        pActor->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionA_candidate
                             | ActorFlagTerrainDrawLayer);
        SetActorDrawLayer(pActor, 1);
        break;
    case 14:
    case 15:
    case 51:
    case 76:
        pActor->oam.priority = 3;
        pActor->bDepthSortBias = 0xFF;
        break;
    case 55:
        pActor->bDepthSortBias = 0xA0;
        break;
    }

    return pActor;
}
