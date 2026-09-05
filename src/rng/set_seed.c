#include "mt19937.h"

void Mt19937SetSeed(u32 seed)
{
    gMt19937SeedValue = seed;
    Mt19937SeedArray(seed);
    gMt19937RemainingIndices = MT_N - 1;
    gMt19937CurPtr = gMt19937StatePtr + 1;
}
