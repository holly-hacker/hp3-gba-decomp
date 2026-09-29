#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileObjectSpecialFlagRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bSet;
} SetTileObjectSpecialFlagRecord;

void RoomScriptOpSetTileObjectSpecialFlag(SetTileObjectSpecialFlagRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pRecord->bSet != 0)
        pObject->bFlags_0x94_candidate |= 4;
}
