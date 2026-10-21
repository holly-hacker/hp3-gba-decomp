#include "types.h"
#include "area.h"
#include "overworld/room_actor.h"
#include "invisible_actors.h"

// Room actor constructor for tile actorType 4, a trigger zone sized by half
// extents.
Actor *SpawnTriggerZoneActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordTriggerZone *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(pRecord->dwActorType);

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = 0x200C;
    pActor->bRoomActorKind_candidate = pRecord->bKind;
    ROOM_ACTOR_WORD_STATE(pActor)->n60 = pRecord->wRearmDelay * 30;
    ROOM_ACTOR_WORD_STATE(pActor)->b70 = pRecord->bRequireAPress;
    SetActorActionState(pActor, 0);
    pActor->apfnCollisionCallback[0] = HandleTriggerZoneTouch;
    pActor->aCollisionBoxes[0].offsets.edges.bLeft = -pRecord->bHalfWidth;
    pActor->aCollisionBoxes[0].offsets.edges.bTop = -pRecord->bHalfHeight;
    pActor->aCollisionBoxes[0].offsets.edges.bRight = pRecord->bHalfWidth;
    pActor->aCollisionBoxes[0].offsets.edges.bBottom = pRecord->bHalfHeight;
    pActor->aCollisionBoxes[0].state.bState = 1;
    pActor->bCollisionBoxCount = 1;

    if (pActor->bRoomActorKind_candidate == 2)
    {
        pActor->aCollisionBoxes[1] = pActor->aCollisionBoxes[0];
        pActor->bCollisionBoxCount = 2;
        pActor->apfnCollisionCallback[1] = HandleTriggerZonePropTouch;
        pActor->apfnCollisionCallback[0] = 0;
        pActor->aCollisionBoxes[0].state.bState = 0;
    }

    pActor->pfnTick = TickTriggerZoneActor;
    return pActor;
}
