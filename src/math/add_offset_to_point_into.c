#include "math.h"

void AddOffsetToPointInto(FixedPoint offset, FixedPoint *pPoint, FixedPoint *pResult)
{
    pResult->x = pPoint->x + offset.x;
    pResult->y = pPoint->y + offset.y;
}
