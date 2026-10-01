#include "types.h"
#include "overworld/overworld.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 3; see docs/formats/rooms.md.
Object *sub_08044C00(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnk3 *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocDefaultObject();

    if (pObj != 0)
    {
        SnapObjectPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
        pObj->wObjectType = pRecord->dwObjectType;
        pObj->dwFlags = 0x808;
        pObj->wCharacterId_candidate = pRecord->bVariant;
        pObj->oam.objMode = 0;
        pObj->oam.bpp8 = 0;
        pObj->oam.priority = 3;
        sub_08030844(pObj, g_apRoomObjUnk3EffectData[pObj->wCharacterId_candidate]);
        pObj->bActionState = 0;
        ROOM_OBJECT_WORD_STATE(pObj)->b6D = 0;
        ROOM_OBJECT_WORD_STATE(pObj)->b6C = 1;
        ROOM_OBJECT_WORD_STATE(pObj)->b6F = pRecord->bArgD;
        ROOM_OBJECT_WORD_STATE(pObj)->n60 = pRecord->wArgA * 30;
        pObj->pfnTick = sub_08044D24;

        if (pObj->wCharacterId_candidate <= 10)
        {
            SetObjectAssetRecord(pObj, g_apRoomObjUnk3AssetRecords[pObj->wCharacterId_candidate]);

            if ((pObj->wCharacterId_candidate == 9 || pObj->wCharacterId_candidate == 10) && pRecord->bFlagC != 0)
                SetObjectAnimFrame(pObj, 1);
            else
                SetObjectAnimFrame(pObj, 0);

            if (g_bUnk03005E18 == 0)
                pObj->bActionFlags = 0;
            else
                pObj->bActionFlags |= 0x20;

            pObj->apfnCollisionCallback[0] = sub_08044F54;
            pObj->dwFlags |= 0x2005;
            pObj->dwFlags &= ~0x800;
        }
    }

    return pObj;
}
