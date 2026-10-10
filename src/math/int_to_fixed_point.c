#include "math.h"

void IntToFixedPoint(IntPoint pos, FixedPoint *pResult)
{
    pResult->x = pos.x << 16;
    pResult->y = pos.y << 16;
}
