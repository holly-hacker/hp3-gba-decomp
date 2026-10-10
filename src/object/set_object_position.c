#include "graphics/object.h"

void SetObjectPosition(Object *obj, s32 x, s32 y)
{
    obj->pos.x = x << 16;
    obj->pos.y = y << 16;
    obj->posPrev.x = obj->pos.x;
    obj->posPrev.y = obj->pos.y;
}
