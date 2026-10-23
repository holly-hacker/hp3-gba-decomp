#include "types.h"
#include "area.h"
#include "commands.h"

typedef struct LockTileActorSpriteRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bSet;
} LockTileActorSpriteRecord;

void RoomScriptOpLockTileActorSprite(LockTileActorSpriteRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    if (pRecord->bSet != 0)
        pActor->bTypeFlags |= 4;
}
