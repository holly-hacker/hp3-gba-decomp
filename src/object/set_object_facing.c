#include "types.h"
#include "graphics/object.h"

void SetObjectFacing(Object *obj, u8 facing)
{
    if (obj->bFacing != facing)
    {
        obj->bFacing = facing;
        obj->bActionFlags |= 0x10;
    }
}
