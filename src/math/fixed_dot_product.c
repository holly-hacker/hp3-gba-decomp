#include "math.h"

s32 FixedDotProduct(FixedPoint a, FixedPoint b)
{
    return (((a.x >> 6) * (b.x >> 6)) >> 4) + (((a.y >> 6) * (b.y >> 6)) >> 4);
}
