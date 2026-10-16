#include "types.h"
#include "area.h"
#include "commands.h"
#include "overworld/room_script.h"

typedef struct SetTileActorFlagBitRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bBit;
} SetTileActorFlagBitRecord;

void RoomScriptOpSetTileActorFlagBit(SetTileActorFlagBitRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    pActor->dwFlags |= 1 << pRecord->bBit;
}
