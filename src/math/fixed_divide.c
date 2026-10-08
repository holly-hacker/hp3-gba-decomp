#include "divide.h"

s32 FixedDivide(s32 numerator, s32 denominator)
{
    return g_pfnIwramDivideSignedQuotient(numerator << 6, denominator / 64) << 4;
}
