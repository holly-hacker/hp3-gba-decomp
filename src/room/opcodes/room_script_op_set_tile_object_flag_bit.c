#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileObjectFlagBitRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bBit;
} SetTileObjectFlagBitRecord;

void RoomScriptOpSetTileObjectFlagBit(SetTileObjectFlagBitRecord *pRecord)
{
    Actor *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    pObject->dwFlags |= 1 << pRecord->bBit;
}
