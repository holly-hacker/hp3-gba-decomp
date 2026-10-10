#include "graphics/object.h"

void CancelObjectMove_candidate(Object *obj)
{
    obj->accel.x = 0;
    obj->accel.y = 0;
    obj->vel.x = 0;
    obj->vel.y = 0;
}
