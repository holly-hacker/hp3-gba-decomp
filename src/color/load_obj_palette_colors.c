#include "color.h"

void LoadObjPaletteColors(const u16 *pColors, u32 firstColor, u32 colorCount)
{
    LoadPaletteColors(pColors, firstColor, colorCount, &g_PaletteState.obj);
}
