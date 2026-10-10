#include "math.h"

void AddOffsetToPoint(s32 dx, s32 dy, s32 *pPoint)
{
    s32 value;

    value = pPoint[0];
    value += dx;
    pPoint[0] = value;
    value = pPoint[1];
    value += dy;
    pPoint[1] = value;
}
