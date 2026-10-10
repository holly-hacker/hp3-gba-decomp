#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 1; see docs/formats/rooms.md.
Object *SpawnRoomTileAnimationObject_candidate(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnk1 *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocObjectOfType(pRecord->dwObjectType);

    SetObjectPosition(pObj, pRecord->nPixelX, pRecord->nPixelY);
    pObj->dwFlags = 0x200C;
    AddRoomTileAnimation_candidate(pRecord->bAnimId, pRecord->nPixelX, pRecord->nPixelY, 0);

    if (pRecord->bFlag == 0)
        sub_0802042C(pRecord->nPixelX, pRecord->nPixelY);
    else
        sub_080203F0(pRecord->nPixelX, pRecord->nPixelY);

    pObj->pfnTick = sub_080205F8;
    return pObj;
}
