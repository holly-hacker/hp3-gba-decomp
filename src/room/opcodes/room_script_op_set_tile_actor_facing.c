#include "types.h"
#include "area.h"
#include "overworld/room_script.h"

typedef struct SetTileActorFacingRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bFacing;
} SetTileActorFacingRecord;

void RoomScriptOpSetTileActorFacing(SetTileActorFacingRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    SetActorActionState(pActor, 3);
    if (pActor->dwFlags & 0x100000)
        pActor->bFacing = pRecord->bFacing >> 1;
    else
        pActor->bFacing = pRecord->bFacing;
}
