#include "mt19937.h"

s32 Mt19937Chance(u16 percent)
{
    u32 draw = Mt19937Next() & 0x7FFFu;
    u32 threshold = (draw * 101) >> 15;

    if (percent < threshold)
        return 0;
    return 1;
}
