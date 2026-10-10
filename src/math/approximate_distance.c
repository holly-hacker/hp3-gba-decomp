#include "math.h"

s32 ApproximateDistance(FixedPoint a, FixedPoint b)
{
    a.x -= b.x;
    a.y -= b.y;
    return ApproximateLength(a);
}
