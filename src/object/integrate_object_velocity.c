#include "graphics/object.h"

// Applies this tick's acceleration, then sets the pending position that
// TickObjectList commits once collisions are resolved.
void IntegrateObjectVelocity(Object *obj)
{
    obj->nVelX += obj->nAccelX;
    obj->nVelY += obj->nAccelY;
    obj->nXPrev = obj->nX + obj->nVelX;
    obj->nYPrev = obj->nY + obj->nVelY;
}
