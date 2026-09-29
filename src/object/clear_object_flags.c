#include "types.h"
#include "graphics/object.h"

void ClearObjectFlags(Object *obj, ObjectFlags flags)
{
    obj->dwFlags &= ~flags;
}
