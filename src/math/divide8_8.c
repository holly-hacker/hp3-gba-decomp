#include "math.h"

s16 Divide8_8(s16 numerator, s16 denominator)
{
    s32 value = numerator;

    return g_pfnIwramDivideSignedQuotient(value << 8, denominator);
}
