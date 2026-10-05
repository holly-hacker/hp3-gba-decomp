#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 5; see docs/formats/rooms.md.
Object *sub_08045AE8(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnk5 *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocObjectOfType(RoomObjectType_ScriptedTrigger);
    u32 kind;

    SnapObjectPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pObj->dwFlags = 0x04002215;
    SetObjectActionState(pObj, 0);
    pObj->bUnk_0x7C = 5;
    pObj->bAnimFrameDelay = 1;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->bKind = pRecord->bKind;
    kind = pRecord->bKind;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->b62 = pRecord->b62;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->b63 = pRecord->b63;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->b64 = pRecord->b64;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->b65 = pRecord->b65;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->b66 = pRecord->b66;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->b68 = pRecord->b68;
    pObj->bFacing = pRecord->bFacing;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->b69 = 0;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->b6A = 0;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->b60 &= 0xFD;
    pObj->pfnTick = sub_08045ECC;
    pObj->apfnCollisionCallback[0] = sub_080465D4;
    pObj->apfnCollisionCallback[1] = sub_0804651C;
    sub_08030844(pObj, g_apRoomObjTriggerEffectData[ROOM_OBJECT_TRIGGER_STATE(pObj)->bKind]);
    SetObjectAnimData(pObj, g_apRoomObjTriggerAnimFrames[ROOM_OBJECT_TRIGGER_STATE(pObj)->bKind],
                      (void *)g_abRoomObjTriggerAnimData[ROOM_OBJECT_TRIGGER_STATE(pObj)->bKind], 0);

    if (kind - 0x1A <= 0xC)
    {
        if (kind == 0x1A || kind == 0x1D)
            pObj->oam.priority = 1;
        else
            pObj->oam.priority = 3;

        pObj->dwFlags &= ~0x04000204;
    }
    else
    {
        pObj->oam.priority = 1;
    }

    pObj->bDepthSortBias = 0x80;
    ROOM_OBJECT_TRIGGER_STATE(pObj)->b67 = 0xFF;

    switch (kind)
    {
    case 66:
        pObj->oam.priority = 0;
        pObj->dwFlags &= ~0x04000200;
        break;
    case 12:
        pObj->oam.priority = 3;
        pObj->oam.hFlip = pObj->bFacing > 4;
        pObj->dwFlags &= ~0x200;
        break;
    case 40:
        pObj->dwFlags &= ~4;
        // fall through
    case 39:
        pObj->oam.priority = 1;
        pObj->dwFlags &= ~0x200;
        break;
    case 0:
        SetObjectAnimFrame(pObj, g_abRoomObjTriggerFacingFrames[pObj->bFacing]);
        pObj->oam.hFlip = pObj->bFacing > 4;
        pObj->pShadowObject = sub_0802FD5C(pObj);
        break;
    case 18:
    case 20:
        pObj->oam.objMode = 1;
        break;
    case 21:
        pObj->bDrawFlags |= ObjectDrawFlagBlink;
        break;
    case 1:
        pObj->dwFlags |= 8;
        pObj->dwFlags &= ~0x04000000;
        break;
    case 81:
        pObj->dwFlags |= 8;
        pObj->dwFlags &= ~0x04000000;

        if (ROOM_OBJECT_TRIGGER_STATE(pObj)->b63 == 0)
            SetObjectAnimFrame(pObj, 1);

        break;
    case 82:
        pObj->dwFlags &= ~0x04000204;
        SetObjectDrawLayer(pObj, 1);
        break;
    case 14:
    case 15:
    case 51:
    case 76:
        pObj->oam.priority = 3;
        pObj->bDepthSortBias = 0xFF;
        break;
    case 55:
        pObj->bDepthSortBias = 0xA0;
        break;
    }

    return pObj;
}
