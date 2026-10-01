#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 8; see docs/formats/rooms.md.
Object *sub_08035540(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnk8 *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocObjectOfType(RoomObjectType_Unk8);

    SnapObjectPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pObj->oam.objMode = 0;
    pObj->oam.bpp8 = 0;
    pObj->oam.priority = 1;
    pObj->bDepthSortBias = 0xFF;
    pObj->wCharacterId_candidate = pRecord->bVariant;
    pObj->bAnimFrameDelay = 0;
    pObj->pfnTick = sub_08035664;
    pObj->apfnCollisionCallback[0] = sub_08035724;
    ROOM_OBJECT_UNK8_STATE(pObj)->abA[0] = pRecord->abPairs[0];
    ROOM_OBJECT_UNK8_STATE(pObj)->abB[0] = pRecord->abPairs[1];
    ROOM_OBJECT_UNK8_STATE(pObj)->abA[1] = pRecord->abPairs[2];
    ROOM_OBJECT_UNK8_STATE(pObj)->abB[1] = pRecord->abPairs[3];
    ROOM_OBJECT_UNK8_STATE(pObj)->abA[2] = pRecord->abPairs[4];
    ROOM_OBJECT_UNK8_STATE(pObj)->abB[2] = pRecord->abPairs[5];
    ROOM_OBJECT_UNK8_STATE(pObj)->abA[3] = pRecord->abPairs[6];
    ROOM_OBJECT_UNK8_STATE(pObj)->abB[3] = pRecord->abPairs[7];
    ROOM_OBJECT_UNK8_STATE(pObj)->abA[4] = pRecord->abPairs[8];
    ROOM_OBJECT_UNK8_STATE(pObj)->abB[4] = pRecord->abPairs[9];
    ROOM_OBJECT_UNK8_STATE(pObj)->abA[5] = pRecord->abPairs[10];
    ROOM_OBJECT_UNK8_STATE(pObj)->abB[5] = pRecord->abPairs[11];
    ROOM_OBJECT_UNK8_STATE(pObj)->abA[6] = pRecord->abPairs[12];
    ROOM_OBJECT_UNK8_STATE(pObj)->abB[6] = pRecord->abPairs[13];
    ROOM_OBJECT_UNK8_STATE(pObj)->abA[7] = pRecord->abPairs[14];
    ROOM_OBJECT_UNK8_STATE(pObj)->abB[7] = pRecord->abPairs[15];
    pObj->dwFlags = 0x0400221D;
    sub_08030844(pObj, g_apRoomObjUnk8EffectData[pObj->wCharacterId_candidate]);
    SetObjectAssetRecord(pObj, g_apRoomObjUnk8AssetRecords[pObj->wCharacterId_candidate]);
    SetObjectAnimFrame(pObj, 0);
    SetObjectActionState(pObj, 0);
    return pObj;
}
