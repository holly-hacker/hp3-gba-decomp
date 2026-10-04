#include "divide.h"

s32 iwramDivideSignedQuotient(s32 numerator, s32 denominator)
{
    return g_pfnIwramDivideSignedQuotient(numerator, denominator);
}
