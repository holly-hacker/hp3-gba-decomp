#include "color.h"

// Starts one color cycle per table entry and marks entry i's bit in g_dwColorCycleActiveMask.
void SetupColorCycles(const ColorCycleTable *pTable)
{
    s32 i;
    u32 startColor;
    u32 colorCount;
    u32 delay;
    u32 flags;
    ColorCycle *pCycle;

    for (i = 0; i < pTable->wCount; i++)
    {
        startColor = pTable->aCycles[i].bStartColor;
        colorCount = pTable->aCycles[i].bColorCount;
        delay = pTable->aCycles[i].bDelay;
        flags = pTable->aCycles[i].bFlags;

        pCycle = &g_aColorCycles[AllocColorCycleSlot()];
        pCycle->bFlags = flags;
        pCycle->bDelay = delay;
        pCycle->bTimer = 0;
        pCycle->bStartColor = startColor;
        pCycle->bCurrentColor = startColor;
        pCycle->bEndColor = startColor + colorCount - 1;
        pCycle->bColorCount = colorCount;
        pCycle->bColorCountCopy = colorCount;

        g_dwColorCycleActiveMask |= 1 << i;
    }
}
