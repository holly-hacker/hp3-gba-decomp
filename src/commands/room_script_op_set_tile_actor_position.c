#include "types.h"
#include "area.h"
#include "commands.h"

typedef struct SetTileActorPositionRecord {
    u32 dwOpcode;
    s16 nX;  // pixels
    s16 nY;
    u8 bTileX;
    u8 bTileY;
    u8 bFacing;
} SetTileActorPositionRecord;

void RoomScriptOpSetTileActorPosition(SetTileActorPositionRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    pActor->pos.x = pRecord->nX << 16;
    pActor->pos.y = pRecord->nY << 16;
    pActor->bFacing = pRecord->bFacing;
    pActor->bActionFlags |= 0x10;
}
