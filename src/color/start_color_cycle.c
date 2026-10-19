#include "color.h"

// Returns the cycle's slot.
u32 StartColorCycle(u32 startColor, u32 colorCount, u32 delay, u32 flags)
{
    u32 slot = AllocColorCycleSlot();
    ColorCycle *pCycle = &g_aColorCycles[slot];

    pCycle->bFlags = flags;
    pCycle->bDelay = delay;
    pCycle->bTimer = 0;
    pCycle->bStartColor = startColor;
    pCycle->bCurrentColor = startColor;
    pCycle->bEndColor = startColor + colorCount - 1;
    pCycle->bColorCount = colorCount;
    pCycle->bColorCount2_candidate = colorCount;
    return slot;
}
