#include "math.h"

void FixedToIntPoint(FixedPoint pos, IntPoint *pResult)
{
    pResult->x = pos.x >> 16;
    pResult->y = pos.y >> 16;
}
