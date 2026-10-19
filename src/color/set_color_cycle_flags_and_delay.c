#include "color.h"

void SetColorCycleFlagsAndDelay(u32 slot, u32 delay, u32 flags)
{
    ColorCycle *pCycle = &g_aColorCycles[slot];

    pCycle->bFlags = flags;
    pCycle->bDelay = delay;
    if (pCycle->bTimer > delay)
        pCycle->bTimer = delay;
}
