#include "math.h"

s32 ApplyPercent(s32 value, u16 percent)
{
    s32 result;

    result = value * percent;
    result = g_pfnIwramDivideSignedQuotient(result, 100);
    return result;
}
