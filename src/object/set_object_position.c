#include "object.h"

void SetObjectPosition(Object *obj, s32 x, s32 y)
{
    obj->nX = x << 16;
    obj->nY = y << 16;
    obj->nXPrev = obj->nX;
    obj->nYPrev = obj->nY;
}
