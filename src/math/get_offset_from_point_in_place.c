#include "math.h"

void GetOffsetFromPointInPlace(FixedPoint pos, FixedPoint *pPoint)
{
    pPoint->x = pos.x - pPoint->x;
    pPoint->y = pos.y - pPoint->y;
}
