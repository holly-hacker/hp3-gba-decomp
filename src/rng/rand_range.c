#include "mt19937.h"

s32 Mt19937RandRange(s32 min, s32 max)
{
    if (min == max)
        return min;
    return min + (((Mt19937Next() & 0x7FFF) * (max - min + 1)) >> 15);
}
