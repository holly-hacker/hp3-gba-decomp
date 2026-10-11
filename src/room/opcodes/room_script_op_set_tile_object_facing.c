#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileObjectFacingRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bFacing;
} SetTileObjectFacingRecord;

void RoomScriptOpSetTileObjectFacing(SetTileObjectFacingRecord *pRecord)
{
    Actor *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    SetActorActionState(pObject, 3);
    if (pObject->dwFlags & 0x100000)
        pObject->bFacing = pRecord->bFacing >> 1;
    else
        pObject->bFacing = pRecord->bFacing;
}
