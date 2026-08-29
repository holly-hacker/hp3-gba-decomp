#include "mt19937.h"

// Return a random bool of roughly `percent` chance.
s32 Mt19937Chance(u16 percent)
{
    u32 draw = Mt19937Next() & 0x7FFFu;

    // BUG: This should be 100, not 101.
    u32 threshold = (draw * 101) >> 15;

    // BUG: If `percent` is 0, this function could still return `true`. This check should be `<=`.
    if (percent < threshold)
        return 0;
    return 1;
}
