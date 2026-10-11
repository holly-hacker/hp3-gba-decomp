#include "types.h"
#include "overworld/room_actor.h"

// Room actor constructor for tile actorType 7, a trigger zone with explicit
// edges. See docs/formats/rooms.md.
Actor *SpawnTriggerRectActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnk7 *pRecord = sub_08005C38(bColumn, bRow);
    Actor *pActor = AllocActorOfType(pRecord->dwActorType);

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = 0x200C;
    pActor->bRoomActorKind_candidate = pRecord->bKind;
    ROOM_ACTOR_WORD_STATE(pActor)->n60 = pRecord->wArgC * 30;
    ROOM_ACTOR_WORD_STATE(pActor)->b70 = pRecord->bArgF;
    SetActorActionState(pActor, 0);
    pActor->apfnCollisionCallback[0] = sub_080265B8;
    pActor->pfnTick = sub_080264F0;
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
        pActor->apfnCollisionCallback[1] = sub_08026674;
        pActor->apfnCollisionCallback[0] = 0;
    }

    return pActor;
}
