#include "graphics/object.h"

void SetObjectVelocity(Object *obj, u32 velX, u32 velY)
{
    obj->vel.x = velX;
    obj->vel.y = velY;
}
