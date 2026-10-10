#include "graphics/object.h"

void FollowOwnerObject(Object *obj)
{
    u32 x;
    u32 y;

    y = obj->pOwnerObject->posPrev.y;
    x = obj->pOwnerObject->posPrev.x;
    obj->posPrev.x = x;
    obj->posPrev.y = y;
    obj->oam.priority = obj->pOwnerObject->oam.priority;

    if (obj->bDrawFlags & ObjectDrawFlagFollowBelow)
        obj->posPrev.y += 0x10000;
    else if (obj->bDrawFlags & ObjectDrawFlagFollowAbove)
        obj->posPrev.y -= 0x10000;
}
