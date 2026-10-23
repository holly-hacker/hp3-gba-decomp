#include "types.h"
#include "area.h"
#include "overworld/room_actor.h"
#include "flipbook.h"

// Room actor constructor for tile actorType 1.
Actor *SpawnRoomTileAnimationActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordTileAnimation *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(pRecord->dwActorType);

    SetActorPosition(pActor, pRecord->nPixelX, pRecord->nPixelY);
    pActor->dwFlags = ActorFlagWantsCollisionCheck | ActorFlagHasTickLogic | ActorFlagUnk2000;
    AddRoomTileAnimation(pRecord->bAnimId, pRecord->nPixelX, pRecord->nPixelY, 0);

    if (pRecord->bFlag == 0)
        HaltRoomTileAnimation(pRecord->nPixelX, pRecord->nPixelY);
    else
        ResumeRoomTileAnimation(pRecord->nPixelX, pRecord->nPixelY);

    pActor->pfnTick = TickRoomTileAnimationActor;
    return pActor;
}
