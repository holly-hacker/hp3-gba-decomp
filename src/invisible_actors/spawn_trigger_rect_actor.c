#include "types.h"
#include "area.h"
#include "overworld/room_actor.h"
#include "invisible_actors.h"

// Room actor constructor for tile actorType 7, a trigger zone with explicit
// edges.
Actor *SpawnTriggerRectActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordTriggerRect *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(pRecord->dwActorType);

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = ActorFlagWantsCollisionCheck | ActorFlagHasTickLogic | ActorFlagUnk2000;
    pActor->bRoomActorKind_candidate = pRecord->bKind;
    ROOM_ACTOR_WORD_STATE(pActor)->n60 = pRecord->wRearmDelay * 30;
    ROOM_ACTOR_WORD_STATE(pActor)->b70 = pRecord->bRequireAPress;
    SetActorActionState(pActor, 0);
    pActor->apfnCollisionCallback[0] = HandleTriggerZoneTouch;
    pActor->pfnTick = TickTriggerZoneActor;
    pActor->aCollisionBoxes[0].offsets.edges.bLeft = pRecord->bLeft;
    pActor->aCollisionBoxes[0].offsets.edges.bTop = pRecord->bTop;
    pActor->aCollisionBoxes[0].offsets.edges.bRight = pRecord->bRight;
    pActor->aCollisionBoxes[0].offsets.edges.bBottom = pRecord->bBottom;
    pActor->aCollisionBoxes[0].state.bState = 1;
    pActor->bCollisionBoxCount = 1;

    if (pActor->bRoomActorKind_candidate == 2)
    {
        pActor->aCollisionBoxes[1] = pActor->aCollisionBoxes[0];
        pActor->bCollisionBoxCount = 2;
        pActor->apfnCollisionCallback[1] = HandleTriggerZonePropTouch;
        pActor->apfnCollisionCallback[0] = 0;
    }

    return pActor;
}
