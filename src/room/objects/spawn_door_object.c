#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 2, a door to another room.
// See docs/formats/rooms.md.
Object *SpawnDoorObject(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnk2 *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocObjectOfType(pRecord->dwObjectType);
    u8 *pDst;
    u8 i;

    SnapObjectPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pObj->dwFlags = 0x2004;
    SetObjectActionState(pObj, 0);
    ROOM_OBJECT_BOX_STATE(pObj)->w60 = pRecord->bB;

    for (i = 0, pDst = ROOM_OBJECT_BOX_STATE(pObj)->ab62; i < 2; i++)
        pDst[i] = pRecord->bA;

    pObj->modeState.actor.bFollowResumeDistance = pRecord->bD;
    pObj->modeState.actor.bRoomScriptArg66_candidate = pRecord->bC;
    pObj->aCollisionBoxes[0].offsets.edges.bTop = -pRecord->bHalfHeight;
    pObj->aCollisionBoxes[0].offsets.edges.bBottom = pRecord->bHalfHeight;
    pObj->aCollisionBoxes[0].offsets.edges.bLeft = -pRecord->bHalfWidth;
    pObj->aCollisionBoxes[0].offsets.edges.bRight = pRecord->bHalfWidth;
    pObj->aCollisionBoxes[0].state.bState = 1;
    pObj->bCollisionBoxCount = 1;
    pObj->apfnCollisionCallback[0] = sub_0800CBF0;
    pObj->pfnTick = sub_0802BC74;
    return pObj;
}
