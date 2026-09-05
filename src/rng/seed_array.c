#include "mt19937.h"

void Mt19937SeedArray(u32 seed)
{
    u32 *state;
    s32 i;

    seed |= 1;
    state = gMt19937StatePtr;
    gMt19937RemainingIndices = 0;
    *state++ = seed;
    for (i = MT_N - 1; i != 0; i--) {
        seed = 0x10DCD * seed;
        *state++ = seed;
    }
}
