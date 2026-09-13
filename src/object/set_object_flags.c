#include "types.h"
#include "object.h"

void SetObjectFlags(Object *obj, ObjectFlags flags)
{
    obj->dwFlags |= flags;
}
