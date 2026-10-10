#include "math.h"

void GetOffsetFromPoint(FixedPoint pos, FixedPoint *pPoint, FixedPoint *pOffset)
{
    pOffset->x = pos.x - pPoint->x;
    pOffset->y = pos.y - pPoint->y;
}
