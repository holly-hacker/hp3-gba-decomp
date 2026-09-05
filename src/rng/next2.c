#include "mt19937.h"

// A secondary `next` impl for a secondary RNG that doesn't regenerate. Used for purely visual effects so it doesn't
// advance the gameplay RNG.
s32 Mt19937Next2(void)
{
    u32 y;

    gMt19937RemainingIndices2--;
    if (gMt19937RemainingIndices2 < 0) {
        gMt19937RemainingIndices2 = MT_N - 1;
        gMt19937CurPtr2 = gMt19937StatePtr + 1;
    }
    y = *gMt19937CurPtr2++;
    y ^= y >> 11;
    y ^= (y << 7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    y ^= y >> 18;
    return y;
}
