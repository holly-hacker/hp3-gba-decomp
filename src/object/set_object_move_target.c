#include "graphics/object.h"

void SetObjectMoveTarget(Object *obj, u32 x, u32 y)
{
    obj->moveTarget.x = x;
    obj->moveTarget.y = y;
}
