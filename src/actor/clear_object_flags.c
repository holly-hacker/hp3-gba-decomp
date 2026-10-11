#include "types.h"
#include "actor.h"

void ClearObjectFlags(Object *obj, ObjectFlags flags)
{
    obj->dwFlags &= ~flags;
}
