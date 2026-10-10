#include "math.h"

s32 iwramDivideSignedRemainder(s32 numerator, s32 denominator, s32 *pRemainder)
{
    return g_pfnIwramDivideSignedRemainder(numerator, denominator, pRemainder);
}
