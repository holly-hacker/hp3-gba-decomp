#include "graphics/object.h"

void SnapObjectPosition(Object *obj, u32 x, u32 y)
{
    obj->pos.x = x;
    obj->pos.y = y;
    obj->posPrev.x = x;
    obj->posPrev.y = y;
}
