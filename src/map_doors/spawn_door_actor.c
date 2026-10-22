#include "types.h"
#include "area.h"
#include "overworld/room_actor.h"
#include "map_doors.h"
#include "collision.h"

// Room actor constructor for tile actorType 2, a door to another room.
Actor *SpawnDoorActor(u8 bColumn, u8 bRow)
{
    RoomActorDoorRecord *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(pRecord->dwActorType);
    u8 *pDst;
    u8 i;

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = ActorFlagWantsCollisionCheck | ActorFlagUnk2000;
    SetActorActionState(pActor, 0);
    pActor->scriptState.wDoorDestinationRoom = pRecord->bDestinationRoom;

    for (i = 0, pDst = pActor->modeState.door.abExitParams; i < 2; i++)
        pDst[i] = pRecord->bExitParam;

    pActor->modeState.door.bRequireAPress = pRecord->bRequireAPress;
    pActor->modeState.door.bChain = pRecord->bChain;
    pActor->aCollisionBoxes[0].offsets.edges.bTop = -pRecord->bHalfHeight;
    pActor->aCollisionBoxes[0].offsets.edges.bBottom = pRecord->bHalfHeight;
    pActor->aCollisionBoxes[0].offsets.edges.bLeft = -pRecord->bHalfWidth;
    pActor->aCollisionBoxes[0].offsets.edges.bRight = pRecord->bHalfWidth;
    pActor->aCollisionBoxes[0].state.bState = 1;
    pActor->bCollisionBoxCount = 1;
    pActor->apfnCollisionCallback[0] = HandleDoorTouch;
    pActor->pfnTick = TickDoorActor;
    return pActor;
}
