#include "types.h"
#include "object.h"

// Byte-identical to SetObjectFacing; no callers found anywhere in the ROM.
void SetObjectFacing_unused(Object *obj, u8 facing)
{
    if (obj->bFacing != facing)
    {
        obj->bFacing = facing;
        obj->bActionFlags |= 0x10;
    }
}
