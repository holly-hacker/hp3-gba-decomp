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
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pObject->wObjectType == RoomObjectType_Player)
        pObject->dwUnk_0x28 = pRecord->nValue * 5 << 14;
    else
        pObject->dwUnk_0x28 = pRecord->nValue << 16;
    pObject->bActionFlags |= 8;
}
