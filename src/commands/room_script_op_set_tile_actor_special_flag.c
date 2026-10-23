#include "types.h"
#include "area.h"
#include "commands.h"

typedef struct SetTileActorSpecialFlagRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bSet;
} SetTileActorSpecialFlagRecord;

void RoomScriptOpSetTileActorSpecialFlag(SetTileActorSpecialFlagRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    if (pRecord->bSet != 0)
        pActor->bTypeFlags |= 4;
}
