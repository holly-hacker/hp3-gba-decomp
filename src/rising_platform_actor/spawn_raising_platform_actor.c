#include "types.h"
#include "area.h"
#include "overworld/room_actor.h"
#include "rising_platform_actor.h"
#include "gen/graphics/overworld.h"

// Room actor constructor for tile actorType 12, a platform that lifts the party.
// See docs/formats/rooms.md.
Actor *SpawnRaisingPlatformActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnkC *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_UnkC);
    u32 i;

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = 0x1D;
    SetActorActionSubState(pActor, 0xA);
    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = sub_0803B71C;
    pActor->apfnCollisionCallback[0] = sub_0803BA18;
    pActor->modeState.actor.bRoomScriptArg64_candidate = pRecord->abArg8[0];
    pActor->modeState.actor.bFollowResumeDistance = pRecord->abArg8[1];
    ROOM_ACTOR_WORD_STATE(pActor)->n60 = pRecord->abArg8[2];
    SetActorPendingPalette(pActor, gRaisingPlatformPalette);

    if (ROOM_ACTOR_WORD_STATE(pActor)->n60 == 0)
        SetActorAnimData(pActor, &g_RoomRaisingPlatformSprite, (void *)g_abRoomRaisingPlatformAnimData, 2);
    else
        SetActorAnimData(pActor, &g_RoomRaisingPlatformSprite, (void *)g_abRoomRaisingPlatformAnimData, 0);

    for (i = 0; i < ARRAY_COUNT(g_adwRoomActorUnkACState); i++)
        g_adwRoomActorUnkACState[i] = 0;

    pActor->oam.priority = 3;
    pActor->bDepthSortBias = 0x80;
    return pActor;
}
