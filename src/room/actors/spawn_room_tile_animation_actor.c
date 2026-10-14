#include "types.h"
#include "overworld/room_actor.h"

// Room actor constructor for tile actorType 1; see docs/formats/rooms.md.
Actor *SpawnRoomTileAnimationActor_candidate(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnk1 *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(pRecord->dwActorType);

    SetActorPosition(pActor, pRecord->nPixelX, pRecord->nPixelY);
    pActor->dwFlags = 0x200C;
    AddRoomTileAnimation_candidate(pRecord->bAnimId, pRecord->nPixelX, pRecord->nPixelY, 0);

    if (pRecord->bFlag == 0)
        sub_0802042C(pRecord->nPixelX, pRecord->nPixelY);
    else
        sub_080203F0(pRecord->nPixelX, pRecord->nPixelY);

    pActor->pfnTick = sub_080205F8;
    return pActor;
}
