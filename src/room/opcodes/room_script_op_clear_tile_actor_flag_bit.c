#include "types.h"
#include "overworld/room_script.h"

typedef struct ClearTileActorFlagBitRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bBit;
} ClearTileActorFlagBitRecord;

void RoomScriptOpClearTileActorFlagBit(ClearTileActorFlagBitRecord *pRecord)
{
    Actor *pActor = GetRoomActorField_candidate(pRecord->bTileX, pRecord->bTileY);

    pActor->dwFlags &= ~(1 << pRecord->bBit);
}
