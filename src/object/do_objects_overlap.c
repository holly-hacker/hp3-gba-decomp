#include "types.h"
#include "object.h"

// Returns 1 if the two objects' collision box 0 rects overlap; touching edges
// count as overlapping.
s32 DoObjectsOverlap(Object *a, Object *b)
{
    ObjectRect rectA;
    ObjectRect rectB;

    rectA = GetObjectCollisionBoxRect(a, 0);
    rectB = GetObjectCollisionBoxRect(b, 0);

    if (rectA.right >= rectB.left && rectB.right >= rectA.left
        && rectA.bottom >= rectB.top && rectB.bottom >= rectA.top)
        return 1;
    return 0;
}
