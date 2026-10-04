#include "graphics/palette.h"
#include "hw/mem.h"

void ClearPaletteEffect(PaletteEffect *pEffect)
{
    memset(pEffect, 0, sizeof(PaletteEffect));
    if (g_dwPaletteEffectCount != 0)
        g_dwPaletteEffectCount--;
}
