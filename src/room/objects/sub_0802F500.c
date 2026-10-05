#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 6; see docs/formats/rooms.md.
// bFighterIndex doubles as the kind index into the asset tables.
Object *sub_0802F500(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnk6 *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocObjectOfType(pRecord->dwObjectType);

    SetObjectPosition(pObj, pRecord->nPixelX, pRecord->nPixelY);
    pObj->dwFlags = 0x04102015;
    pObj->bAnimFrameDelay = 0;
    pObj->bFighterIndex = pRecord->bKind;
    pObj->bRoomObjectKind_candidate = pRecord->argC.bFirst;

    if ((pRecord->argC.dwWord & 0x00FFFF00) == 0)
        pObj->bFlags_0x94_candidate |= 3;

    pObj->pfnTick = sub_0802F7F0;
    pObj->apfnCollisionCallback[0] = sub_0802FCC0;
    pObj->apfnCollisionCallback[1] = 0;
    sub_08030844(pObj, g_aObjectTypeAssets[pObj->bFighterIndex].pPalette);
    pObj->bFacing = pRecord->bFacing >> 1;
    SetObjectAssetRecord(pObj, &g_aObjectTypeAssets[pObj->bFighterIndex]);
    SetObjectAnimFrame(pObj, g_abRoomObjUnk6Frames[g_adwRoomObjUnk6FrameRows[pObj->bFighterIndex]][pObj->bFacing]);
    pObj->oam.priority = 1;
    pObj->bDepthSortBias = 0x80;
    pObj->dwUnk_0x28 = 0x10000;
    SetObjectAnimSubState_candidate(pObj, 0);
    SetObjectActionState(pObj, 0);
    pObj->wUnk84 = 0;

    if (pObj->bFighterIndex == 0x21)
        pObj->dwFlags &= ~0x100000;

    if (pObj->bFighterIndex == 0x5F)
    {
        pObj->dwFlags &= ~0x100000;
        pObj->oam.priority = 1;
        pObj->bDepthSortBias = 0xFF;
    }
    else
    {
        pObj->pLinkedObject_candidate = sub_0802FD5C(pObj);
    }

    if (pObj->bFighterIndex != 0x5F)
        pObj->oam.hFlip = pObj->bFacing == 3;

    pObj->bFlags_0x94_candidate &= ~4;

    if ((u8)(pObj->bFighterIndex - 0x69) <= 1)
        SetObjectAffineTransform(pObj, 0x1C000, 0x1C000, 0, 3);

    if (pObj->bFighterIndex == 5)
        pObj->dwFlags &= ~4;

    return pObj;
}
