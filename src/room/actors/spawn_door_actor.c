#include "types.h"
#include "overworld/room_actor.h"

// Room actor constructor for tile actorType 2, a door to another room.
// See docs/formats/rooms.md.
Actor *SpawnDoorActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnk2 *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(pRecord->dwActorType);
    u8 *pDst;
    u8 i;

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = 0x2004;
    SetActorActionState(pActor, 0);
    ROOM_ACTOR_BOX_STATE(pActor)->w60 = pRecord->bB;

    for (i = 0, pDst = ROOM_ACTOR_BOX_STATE(pActor)->ab62; i < 2; i++)
        pDst[i] = pRecord->bA;

    pActor->modeState.actor.bFollowResumeDistance = pRecord->bD;
    pActor->modeState.actor.bRoomScriptArg66_candidate = pRecord->bC;
    pActor->aCollisionBoxes[0].offsets.edges.bTop = -pRecord->bHalfHeight;
    pActor->aCollisionBoxes[0].offsets.edges.bBottom = pRecord->bHalfHeight;
    pActor->aCollisionBoxes[0].offsets.edges.bLeft = -pRecord->bHalfWidth;
    pActor->aCollisionBoxes[0].offsets.edges.bRight = pRecord->bHalfWidth;
    pActor->aCollisionBoxes[0].state.bState = 1;
    pActor->bCollisionBoxCount = 1;
    pActor->apfnCollisionCallback[0] = sub_0800CBF0;
    pActor->pfnTick = sub_0802BC74;
    return pActor;
}
