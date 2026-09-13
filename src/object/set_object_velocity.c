#include "object.h"

void SetObjectVelocity(Object *obj, u32 velX, u32 velY)
{
    obj->nVelX = velX;
    obj->nVelY = velY;
}
