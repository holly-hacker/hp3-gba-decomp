#include "math.h"

s32 FixedMultiply(s32 a, s32 b)
{
    return ((a >> 6) * (b >> 6)) >> 4;
}
