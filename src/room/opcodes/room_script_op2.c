#include "types.h"
#include "overworld/room_script.h"

typedef struct Op2Record {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    s16 nValue;
} Op2Record;

// Unnamed; reads like an animation or movement speed with a special case for the player.
void RoomScriptOp2(Op2Record *pRecord)
{
    Actor *pActor = GetRoomActorField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pActor->wActorType == RoomActorType_Player)
        pActor->nMoveSpeed = pRecord->nValue * 5 << 14;
    else
        pActor->nMoveSpeed = pRecord->nValue << 16;
    pActor->bActionFlags |= 8;
}
