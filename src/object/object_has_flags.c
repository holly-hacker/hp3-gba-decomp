#include "types.h"
#include "graphics/object.h"

s32 ObjectHasFlags(Object *obj, ObjectFlags flags)
{
    if ((obj->dwFlags & flags) == flags)
        return 1;
    return 0;
}
