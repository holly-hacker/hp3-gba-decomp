#include "math.h"

s16 Reciprocal8_8(s16 value)
{
    return g_pfnIwramDivideSignedQuotient(0x10000, value);
}
