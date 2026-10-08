#include "graphics/object.h"

void FollowOwnerObject(Object *obj)
{
    u32 x;
    u32 y;

    y = obj->pOwnerObject->nYPrev;
    x = obj->pOwnerObject->nXPrev;
    obj->nXPrev = x;
    obj->nYPrev = y;
    obj->oam.priority = obj->pOwnerObject->oam.priority;

    if (obj->bDrawFlags & ObjectDrawFlagFollowBelow)
        obj->nYPrev += 0x10000;
    else if (obj->bDrawFlags & ObjectDrawFlagFollowAbove)
        obj->nYPrev -= 0x10000;
}
