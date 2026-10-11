#include "types.h"
#include "actor.h"

void SetObjectAssetRecord(Object *obj, const void *rec)
{
    if (obj->anim.pAnimTable != rec)
    {
        obj->anim.pAnimTable = (ObjectAssetRecord *)rec;
        obj->dwFlags |= ObjectFlagAnimFrameLoaded;
    }

    SetObjectAnimFrame(obj, 0);
}
