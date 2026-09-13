#include "object.h"

void SnapObjectPosition(Object *obj, u32 x, u32 y)
{
    obj->nX = x;
    obj->nY = y;
    obj->nXPrev = x;
    obj->nYPrev = y;
}
