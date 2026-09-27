#include "types.h"
#include "room_script.h"

typedef struct SetTileObjectFlagBitRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bBit;
} SetTileObjectFlagBitRecord;

void RoomScriptOpSetTileObjectFlagBit(SetTileObjectFlagBitRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    pObject->dwFlags |= 1 << pRecord->bBit;
}
