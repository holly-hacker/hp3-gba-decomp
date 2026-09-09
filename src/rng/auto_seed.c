#include "input.h"
#include "mt19937.h"
#include "vblank.h"

// g_wKeysHeld (0x030034EC) is the live held-key bitmask maintained by
// UpdateKeyInput (see docs/memory-map/input.md), folded in here purely as
// a cheap, frame-varying entropy source -- not RNG state itself.
void Mt19937AutoSeed(void)
{
    gMt19937RemainingIndices = -1;
    gMt19937RemainingIndices2 = -1;

    gMt19937SeedValue += (g_pVBlankState->dwVBlankCount << 4) + (g_wKeysHeld << 2);
    if (gMt19937SeedValue == 0)
        gMt19937SeedValue = (u32)Mt19937Next() % 0xFFF1F + 1;

    gMt19937AutoSeedCallCount++;
    gMt19937SeedValue = ((gMt19937SeedValue << 8) + (g_pVBlankState->dwVBlankCount << 6) +
                          (gMt19937AutoSeedCallCount << 4)) | g_wKeysHeld;
    Mt19937SeedArray(gMt19937SeedValue);
}
