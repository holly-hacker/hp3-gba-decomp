#include "mt19937.h"

void Mt19937SetSeed(u32 seed)
{
    gMt19937SeedValue = seed;
    Mt19937SeedArray(seed);
    gMt19937RemainingIndices = 0x26F;
    gMt19937CurPtr = gMt19937StatePtr + 1;
}
