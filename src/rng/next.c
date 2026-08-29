#include "mt19937.h"

s32 Mt19937Next(void)
{
    u32 y;

    gMt19937RemainingIndices--;
    if (gMt19937RemainingIndices < 0)
        return Mt19937Regenerate();

    gMt19937DrawIndex++;
    y = *gMt19937CurPtr++;
    y ^= y >> 11;
    y ^= (y << 7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    gMt19937LastRollByte = y ^ (y >> 18);
    return y ^ (y >> 18);
}
