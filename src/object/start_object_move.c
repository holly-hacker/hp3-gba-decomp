#include "graphics/object.h"

void StartObjectMove(Object *obj, u32 x, u32 y, u16 mode)
{
    obj->moveTarget.x = x;
    obj->moveTarget.y = y;
    obj->wMoveDuration = mode + 1;
}
