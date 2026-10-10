#include "math.h"

s32 ApproximateLength(FixedPoint delta)
{
    delta.x = ABS(delta.x);
    delta.y = ABS(delta.y);

    if (delta.x > delta.y)
        return ((delta.y * 2 + delta.y) >> 3) + delta.x;
    else
        return ((delta.x * 2 + delta.x) >> 3) + delta.y;
}
