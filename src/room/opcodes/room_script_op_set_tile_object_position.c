#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileObjectPositionRecord {
    u32 dwOpcode;
    s16 nX;  // pixels
    s16 nY;
    u8 bTileX;
    u8 bTileY;
    u8 bFacing;
} SetTileObjectPositionRecord;

void RoomScriptOpSetTileObjectPosition(SetTileObjectPositionRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    pObject->nX = pRecord->nX << 16;
    pObject->nY = pRecord->nY << 16;
    pObject->bFacing = pRecord->bFacing;
    pObject->bActionFlags |= 0x10;
}
