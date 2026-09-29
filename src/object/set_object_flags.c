#include "types.h"
#include "graphics/object.h"

void SetObjectFlags(Object *obj, ObjectFlags flags)
{
    obj->dwFlags |= flags;
}
