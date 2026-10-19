#include "color.h"

void EnableColorCycle(u8 slot)
{
    ColorCycle *pCycle = &g_aColorCycles[slot];

    pCycle->bFlags |= PALETTE_ANIM_ACTIVE;
    g_dwColorCycleActiveMask |= 1 << slot;
}
