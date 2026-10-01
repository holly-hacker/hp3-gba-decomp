#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 10; see docs/formats/rooms.md.
Object *sub_08040038(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnkA *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocObjectOfType(RoomObjectType_UnkA);
    u32 i;

    SnapObjectPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pObj->dwFlags = 0x200D;
    SetObjectActionState(pObj, 0);
    SetObjectActionSubState(pObj, 1);
    pObj->bAnimFrameDelay = 1;
    pObj->pfnTick = sub_08040114;
    pObj->apfnCollisionCallback[0] = sub_08040358;
    pObj->wCharacterId_candidate = pRecord->bVariant;
    ROOM_OBJECT_WORD_STATE(pObj)->n60 = pRecord->nArg8;
    ROOM_OBJECT_WORD_STATE(pObj)->n64 = pRecord->nArgA;
    ROOM_OBJECT_WORD_STATE(pObj)->b6C = pRecord->abArgD[0];
    ROOM_OBJECT_WORD_STATE(pObj)->b6D = pRecord->abArgD[1];
    ROOM_OBJECT_WORD_STATE(pObj)->n68 = 0;
    sub_08030844(pObj, g_apRoomObjUnkAEffectData[pObj->wCharacterId_candidate]);
    SetObjectAnimData(pObj, g_apRoomObjUnkAAnimFrames[pObj->wCharacterId_candidate], (void *)g_abRoomObjUnkAAnimData, 0);
    pObj->oam.priority = 3;
    pObj->bDepthSortBias = 0x80;

    for (i = 0; i < ARRAY_COUNT(g_adwRoomObjUnkACState); i++)
        g_adwRoomObjUnkACState[i] = 0;

    return pObj;
}
