#include "math.h"

s32 ToPercent(s32 value, s32 total)
{
    s32 result;

    result = value * 100;
    result = g_pfnIwramDivideSignedQuotient(result, total);
    return result;
}
