#include "types.h"
#include "room_script.h"

typedef struct SetTileObjectFacingRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bFacing;
} SetTileObjectFacingRecord;

void RoomScriptOpSetTileObjectFacing(SetTileObjectFacingRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    SetObjectActionState(pObject, 3);
    if (pObject->dwFlags & 0x100000)
        pObject->bFacing = pRecord->bFacing >> 1;
    else
        pObject->bFacing = pRecord->bFacing;
}
