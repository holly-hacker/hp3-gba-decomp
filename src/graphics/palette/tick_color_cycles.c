#include "graphics/palette.h"

void TickColorCycles(void)
{
    u32 i;
    ColorCycle *pCycle;

    for (i = 0; i < ARRAY_COUNT(g_aColorCycles); i++)
    {
        pCycle = &g_aColorCycles[i];
        if (pCycle->bFlags & PALETTE_ANIM_ACTIVE)
            StepColorCycle(pCycle);
    }
}
