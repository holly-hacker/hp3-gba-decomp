#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 4, a trigger zone sized by half
// extents. See docs/formats/rooms.md.
Object *SpawnTriggerZoneObject(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnk4 *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocObjectOfType(pRecord->dwObjectType);

    SnapObjectPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pObj->dwFlags = 0x200C;
    pObj->bRoomObjectKind_candidate = pRecord->bKind;
    ROOM_OBJECT_WORD_STATE(pObj)->n60 = pRecord->wArgA * 30;
    ROOM_OBJECT_WORD_STATE(pObj)->b70 = pRecord->bArgD;
    SetObjectActionState(pObj, 0);
    pObj->apfnCollisionCallback[0] = sub_080265B8;
    pObj->aCollisionBoxes[0].offsets.edges.bLeft = -pRecord->bHalfWidth;
    pObj->aCollisionBoxes[0].offsets.edges.bTop = -pRecord->bHalfHeight;
    pObj->aCollisionBoxes[0].offsets.edges.bRight = pRecord->bHalfWidth;
    pObj->aCollisionBoxes[0].offsets.edges.bBottom = pRecord->bHalfHeight;
    pObj->aCollisionBoxes[0].state.bState = 1;
    pObj->bCollisionBoxCount = 1;

    if (pObj->bRoomObjectKind_candidate == 2)
    {
        pObj->aCollisionBoxes[1] = pObj->aCollisionBoxes[0];
        pObj->bCollisionBoxCount = 2;
        pObj->apfnCollisionCallback[1] = sub_08026674;
        pObj->apfnCollisionCallback[0] = 0;
        pObj->aCollisionBoxes[0].state.bState = 0;
    }

    pObj->pfnTick = sub_080264F0;
    return pObj;
}
