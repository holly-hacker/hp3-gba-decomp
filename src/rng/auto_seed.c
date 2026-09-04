#include "mt19937.h"
#include "vblank.h"

void Mt19937AutoSeed(void)
{
    gMt19937RemainingIndices = -1;
    gMt19937RemainingIndices2 = -1;

    gMt19937SeedValue += (g_pVBlankState->dwVBlankCount << 4) + (gMt19937SeedSourceCounter << 2);
    if (gMt19937SeedValue == 0)
        gMt19937SeedValue = (u32)Mt19937Next() % 0xFFF1F + 1;

    gMt19937AutoSeedCallCount++;
    gMt19937SeedValue = ((gMt19937SeedValue << 8) + (g_pVBlankState->dwVBlankCount << 6) +
                          (gMt19937AutoSeedCallCount << 4)) | gMt19937SeedSourceCounter;
    Mt19937SeedArray(gMt19937SeedValue);
}
