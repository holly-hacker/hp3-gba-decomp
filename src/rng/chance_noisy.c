#include "mt19937.h"

#define REG_VCOUNT (*(volatile u16 *)0x04000006)

s32 Mt19937ChanceNoisy(u16 percent)
{
    u32 draw = (Mt19937Next() + REG_VCOUNT) & 0x7FFFu;
    u32 threshold = (draw * 101) >> 15;

    if (percent < threshold)
        return 0;
    return 1;
}
