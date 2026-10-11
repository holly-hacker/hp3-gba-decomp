#include "types.h"
#include "actor.h"

void SetObjectFlags(Object *obj, ObjectFlags flags)
{
    obj->dwFlags |= flags;
}
