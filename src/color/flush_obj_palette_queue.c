#include "color.h"

void FlushObjPaletteQueue(void)
{
    u32 i;

    for (i = 0; i < g_dwObjPaletteQueueCount; i++)
        LoadPaletteColors(g_aObjPaletteQueue[i].pPalette, g_aObjPaletteQueue[i].wFirstColor,
                          g_aObjPaletteQueue[i].wColorCount, &g_PaletteState.obj);

    g_dwObjPaletteQueueCount = 0;
}
