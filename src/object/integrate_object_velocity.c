#include "graphics/object.h"

// Applies this tick's acceleration, then sets the pending position that
// TickObjectList commits once collisions are resolved.
void IntegrateObjectVelocity(Object *obj)
{
    obj->vel.x += obj->accel.x;
    obj->vel.y += obj->accel.y;
    obj->posPrev.x = obj->pos.x + obj->vel.x;
    obj->posPrev.y = obj->pos.y + obj->vel.y;
}
