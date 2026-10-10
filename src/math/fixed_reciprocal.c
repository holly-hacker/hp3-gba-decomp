#include "math.h"

s32 FixedReciprocal(s32 value)
{
    s32 result;

    result = 0x10000;
    result = g_pfnIwramDivideSignedQuotient(result, value);
    return result << 16;
}
