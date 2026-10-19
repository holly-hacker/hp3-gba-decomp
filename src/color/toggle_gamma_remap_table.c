#include "color.h"

void ToggleGammaRemapTable(void)
{
    if (g_PaletteState.pGammaTable == g_abGammaNormalRemap)
        ApplyGammaRemapTable(g_abGammaHighRemap);
    else
        ApplyGammaRemapTable(g_abGammaNormalRemap);
}
