#include "graphics/palette.h"

void ResetPaletteEffects(void)
{
    u32 i;

    g_dwPaletteEffectCount = 0;
    for (i = 0; i < ARRAY_COUNT(g_aPaletteEffects); i++)
        ClearPaletteEffect(&g_aPaletteEffects[i]);
}
