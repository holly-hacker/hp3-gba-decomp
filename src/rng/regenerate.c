#include "mt19937.h"

#define MT_M 397
#define MATRIX_A   0x9908B0DFu
#define UPPER_MASK 0x80000000u
#define LOWER_MASK 0x7FFFFFFFu

u32 Mt19937Regenerate(void)
{
    s32 kk;
    u32 y;
    u32 lo, hi;
    u32 *p, *p2, *pM;

    p = gMt19937StatePtr;
    p2 = p + 2;
    pM = p + MT_M;

    if (gMt19937RemainingIndices < -1) {
        u32 seed = gMt19937SeedValue | 1;
        u32 *state = p;
        s32 i;
        gMt19937RemainingIndices = 0;
        *state++ = seed;
        for (i = MT_N - 1; i != 0; i--) {
            seed = 0x10DCD * seed;
            *state++ = seed;
        }
    }

    gMt19937RemainingIndices = MT_N - 1;
    gMt19937CurPtr = gMt19937StatePtr + 1;

    lo = gMt19937StatePtr[0];
    hi = gMt19937StatePtr[1];

    kk = MT_N - MT_M;
    do {
        y = (lo & UPPER_MASK) | (hi & LOWER_MASK);
        *p++ = *pM++ ^ (y >> 1) ^ ((hi & 1) ? MATRIX_A : 0);
        lo = hi;
        hi = *p2++;
    } while (--kk);

    pM = gMt19937StatePtr;
    kk = MT_M - 1;
    do {
        y = (lo & UPPER_MASK) | (hi & LOWER_MASK);
        *p++ = *pM++ ^ (y >> 1) ^ ((hi & 1) ? MATRIX_A : 0);
        lo = hi;
        hi = *p2++;
    } while (--kk);

    y = gMt19937StatePtr[0];
    {
        u32 tmp = (lo & UPPER_MASK) | (y & LOWER_MASK);
        *p = *pM ^ (tmp >> 1);
        if (y & 1)
            *p ^= MATRIX_A;
    }

    y ^= y >> 11;
    y ^= (y << 7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    y ^= y >> 18;
    return y;
}
