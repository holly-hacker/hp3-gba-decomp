#include "graphics/palette.h"

void ResetColorCycles(void)
{
    u32 i;

    g_dwColorCycleCount = 0;
    for (i = 0; i < ARRAY_COUNT(g_aColorCycles); i++)
        ClearColorCycle(&g_aColorCycles[i]);
}
