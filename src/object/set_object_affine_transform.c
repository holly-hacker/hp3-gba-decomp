#include "object.h"
#include "graphics.h"

void SetObjectAffineTransform(Object *obj, u32 nScaleX, u32 nScaleY, s16 wAngle, u8 bMode)
{
    s16 sx, sy;
    u16 slotId;
    u32 nMode;
    ObjectFlagsD1 *pFlags;

    obj->nAffineScaleX = nScaleX;
    obj->nAffineScaleY = nScaleY;
    obj->wAffineAngle = wAngle;
    obj->bAffineMode = bMode;

    slotId = AllocObjectAffineSlot(obj);

    sx = 0x1000000 / (s32)nScaleX;
    sy = 0x1000000 / (s32)nScaleY;
    if (sx == 0) {
        sx = 1;
    }
    if (sy == 0) {
        sy = 1;
    }

    g_aObjAffineSetSource[slotId].sx = sx;
    g_aObjAffineSetSource[slotId].sy = sy;
    g_aObjAffineSetSource[slotId].theta = wAngle;

    nMode = bMode;
    pFlags = (ObjectFlagsD1 *)&obj->bFlags_0xD1;
    pFlags->bAffineSlotState = nMode & 3;
}
