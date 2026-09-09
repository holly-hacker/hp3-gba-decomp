#include "mt19937.h"

s16 Mt19937RandSigned(s16 max)
{
    u32 temp;
    u32 draw;
    s16 smax;
    u32 range;

    temp = Mt19937Next();
    draw = temp & 0x7FFFu;
    smax = max;
    range = smax << 1;
    range += 1;
    range *= draw;
    range >>= 15;
    range -= smax;
    return (s16)range;
}
