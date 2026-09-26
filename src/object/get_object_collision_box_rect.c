#include "types.h"
#include "object.h"

// Returns collision box boxIndex as pixel edges around the object's
// previous-frame position, mirrored by its flip bits.
ObjectRect GetObjectCollisionBoxRect(Object *obj, s32 boxIndex)
{
    ObjectRect rect;
    s32 offsets;
    s32 origin;

    offsets = (obj->aCollisionBoxes + boxIndex)->dwPackedOffsets;

    origin = (s16)(obj->nYPrev >> 16);
    if (obj->bYFlip) {
        rect.top = origin - (offsets >> 24);
        offsets <<= 8;
        rect.bottom = origin - (offsets >> 24);
    }
    else {
        rect.bottom = origin + (offsets >> 24);
        offsets <<= 8;
        rect.top = origin + (offsets >> 24);
    }
    offsets <<= 8;

    origin = (s16)(obj->nXPrev >> 16);
    if (obj->bXFlip) {
        rect.left = origin - (offsets >> 24);
        offsets <<= 8;
        rect.right = origin - (offsets >> 24);
    }
    else {
        rect.right = origin + (offsets >> 24);
        offsets <<= 8;
        rect.left = origin + (offsets >> 24);
    }

    return rect;
}
