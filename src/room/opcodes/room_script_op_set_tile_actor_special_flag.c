#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileActorSpecialFlagRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bSet;
} SetTileActorSpecialFlagRecord;

void RoomScriptOpSetTileActorSpecialFlag(SetTileActorSpecialFlagRecord *pRecord)
{
    Actor *pActor = GetRoomActorField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pRecord->bSet != 0)
        pActor->bFlags_0x94_candidate |= 4;
}
