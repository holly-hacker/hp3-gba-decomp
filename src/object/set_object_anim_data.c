#include "graphics/object.h"

// Starts the animation command stream at command startCommand of pAnimData. A
// new sprite record also invalidates the loaded frame so it is reloaded.
void SetObjectAnimData(Object *obj, const void *pAnimTable, const void *pAnimData, u8 startCommand)
{
    obj->anim.pAnimFrameBase = (u8 *)pAnimData + startCommand * 2;
    obj->anim.pAnimFrameCursor = obj->anim.pAnimFrameBase;

    if (obj->anim.pAnimTable != pAnimTable) {
        obj->anim.pAnimTable = (ObjectAssetRecord *)pAnimTable;
        obj->anim.bAnimFrameIndex_candidate = 0xFF;
        obj->anim.bLastAnimFrameValue = 0xFF;
    }

    RunObjectAnimCommands(obj);
    LoadObjectAnimFrameBounds(obj);
}
