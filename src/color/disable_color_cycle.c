#include "color.h"

// Stops the cycle; with resetColors set, its colors are uploaded once more in their original order.
void DisableColorCycle(u8 slot, u32 resetColors)
{
    ColorCycle *pCycle = &g_aColorCycles[slot];

    pCycle->bFlags &= ~PALETTE_ANIM_ACTIVE;
    g_dwColorCycleActiveMask &= ~(1 << slot);
    if (resetColors)
    {
        pCycle->bCurrentColor = pCycle->bStartColor;
        pCycle->bFlags |= PALETTE_ANIM_DIRTY;
    }
}
