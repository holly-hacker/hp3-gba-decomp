#include "color.h"

void LoadBgPaletteColors(const void *pColors, u32 firstColor, u32 colorCount)
{
    LoadPaletteColors(pColors, firstColor, colorCount, &g_PaletteState.bg);
}
