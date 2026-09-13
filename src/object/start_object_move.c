#include "object.h"

void StartObjectMove(Object *obj, u32 x, u32 y, u16 mode)
{
    obj->nMoveTargetX = x;
    obj->nMoveTargetY = y;
    obj->wMoveDuration = mode + 1;
}
