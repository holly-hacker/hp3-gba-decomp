#include "types.h"
#include "overworld/room_script.h"

typedef struct ClearTileObjectFlagBitRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bBit;
} ClearTileObjectFlagBitRecord;

void RoomScriptOpClearTileObjectFlagBit(ClearTileObjectFlagBitRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    pObject->dwFlags &= ~(1 << pRecord->bBit);
}
