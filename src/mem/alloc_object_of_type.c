#include "object.h"

// Allocates a default object and stamps its type/kind marker.
Object *AllocObjectOfType(s32 type)
{
    Object *obj = AllocDefaultObject();

    if (obj != NULL) {
        obj->wObjectType = type;
        obj->bUnk_0x7C = 5;
    }
    return obj;
}
