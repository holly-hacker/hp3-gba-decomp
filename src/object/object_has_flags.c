#include "types.h"
#include "object.h"

s32 ObjectHasFlags(Object *obj, ObjectFlags flags)
{
    if ((obj->dwFlags & flags) == flags)
        return 1;
    return 0;
}
