#include "types.h"
#include "area.h"
#include "overworld/room_actor.h"
#include "rising_platform_actor.h"
#include "gen/graphics/overworld.h"

// Room actor constructor for tile actorType 12, a platform that lifts the party.
Actor *SpawnRaisingPlatformActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordRaisingPlatform *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_RaisingPlatform);
    u32 i;

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = 0x1D;
    SetActorActionSubState(pActor, 0xA);
    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = TickRaisingPlatformActor;
    pActor->apfnCollisionCallback[0] = HandleRaisingPlatformTouch;
    RAISING_PLATFORM_STATE(pActor)->finish.rows.bRespawnRow = pRecord->abArg8[0];
    RAISING_PLATFORM_STATE(pActor)->finish.rows.bChainRow = pRecord->abArg8[1];
    RAISING_PLATFORM_STATE(pActor)->dwInactive = pRecord->abArg8[2];
    SetActorPendingPalette(pActor, gRaisingPlatformPalette);

    if (RAISING_PLATFORM_STATE(pActor)->dwInactive == 0)
        SetActorAnimData(pActor, &g_RoomRaisingPlatformSprite, (void *)g_abRoomRaisingPlatformAnimData, 2);
    else
        SetActorAnimData(pActor, &g_RoomRaisingPlatformSprite, (void *)g_abRoomRaisingPlatformAnimData, 0);

    for (i = 0; i < ARRAY_COUNT(g_adwPartyMemberArrived); i++)
        g_adwPartyMemberArrived[i] = 0;

    pActor->oam.priority = 3;
    pActor->bDepthSortBias = 0x80;
    return pActor;
}
