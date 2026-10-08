#include "graphics/object.h"

void CancelObjectMove_candidate(Object *obj)
{
    obj->nAccelX = 0;
    obj->nAccelY = 0;
    obj->nVelX = 0;
    obj->nVelY = 0;
}
