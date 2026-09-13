#include "types.h"
#include "object.h"

void ClearObjectFlags(Object *obj, ObjectFlags flags)
{
    obj->dwFlags &= ~flags;
}
