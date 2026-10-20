#include "types.h"
#include "combat_dispatch.h"

void QueueStatsPortraitPalette(u32 bank, const ObjPalette *palette)
{
    if (g_StatsPortraitPaletteLoad.pPalette != palette) {
        g_StatsPortraitPaletteLoad.bBank = bank;
        g_StatsPortraitPaletteLoad.pPalette = palette;
        g_StatsPortraitPaletteLoad.bCountdown = 2;
        ClearStatsPortraitPalette();
    }
}
