#include "object.h"

void SetObjectMoveTarget(Object *obj, u32 x, u32 y)
{
    obj->nMoveTargetX = x;
    obj->nMoveTargetY = y;
}
