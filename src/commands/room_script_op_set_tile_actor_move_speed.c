#include "types.h"
#include "area.h"
#include "commands.h"

typedef struct SetTileActorMoveSpeedRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    s16 nSpeed;          // pixels per tick
} SetTileActorMoveSpeedRecord;

// Sets the actor's nMoveSpeed, scaled by 1.25 for the player, and raises
// bActionFlags bit 0x8.
void RoomScriptOpSetTileActorMoveSpeed(SetTileActorMoveSpeedRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    if (pActor->wActorType == RoomActorType_Player)
        pActor->nMoveSpeed = pRecord->nSpeed * 5 << 14;
    else
        pActor->nMoveSpeed = pRecord->nSpeed << 16;
    pActor->bActionFlags |= 8;
}
