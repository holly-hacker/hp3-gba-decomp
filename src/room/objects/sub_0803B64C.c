#include "types.h"
#include "overworld/room_object.h"
#include "gen/ObjectSprites2.h"

// Room object constructor for tile objType 12; see docs/formats/rooms.md.
Object *sub_0803B64C(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnkC *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocObjectOfType(RoomObjectType_UnkC);
    u32 i;

    SnapObjectPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pObj->dwFlags = 0x1D;
    SetObjectActionSubState(pObj, 0xA);
    pObj->bAnimFrameDelay = 1;
    pObj->pfnTick = sub_0803B71C;
    pObj->apfnCollisionCallback[0] = sub_0803BA18;
    pObj->modeState.actor.bRoomScriptArg64_candidate = pRecord->abArg8[0];
    pObj->modeState.actor.bFollowResumeDistance = pRecord->abArg8[1];
    ROOM_OBJECT_WORD_STATE(pObj)->n60 = pRecord->abArg8[2];
    sub_08030844(pObj, gObjectSprite2_111Palette);

    if (ROOM_OBJECT_WORD_STATE(pObj)->n60 == 0)
        SetObjectAnimData(pObj, g_apRoomObjUnkCAnimFrames, (void *)g_abRoomObjUnkCAnimData, 2);
    else
        SetObjectAnimData(pObj, g_apRoomObjUnkCAnimFrames, (void *)g_abRoomObjUnkCAnimData, 0);

    for (i = 0; i < ARRAY_COUNT(g_adwRoomObjUnkACState); i++)
        g_adwRoomObjUnkACState[i] = 0;

    pObj->oam.priority = 3;
    pObj->bDepthSortBias = 0x80;
    return pObj;
}
