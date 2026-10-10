#include "math.h"

s32 SignMagnitude8_8ToFixed(s16 value)
{
    s32 result;

    result = (value << 8) & 0x7FFFFF;
    if (value < 0)
        result = -result;
    return result;
}
