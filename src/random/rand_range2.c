#include "random.h"

s32 Mt19937RandRange2(s32 min, s32 max)
{
    return min + (((Mt19937Next2() & 0x7FFF) * (max - min + 1)) >> 15);
}
