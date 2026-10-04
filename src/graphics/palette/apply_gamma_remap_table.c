#include "graphics/palette.h"
#include "hw/io_regs.h"
#include "hw/mem.h"
#include "menu/options.h"

// Makes pTable the active gamma remap and re-filters palette RAM and both
// shadow palettes with it, first undoing the high-gamma table if it was
// active. The normal table is the identity, so applying it is skipped.
void ApplyGammaRemapTable(const u8 *pTable)
{
    if (g_PaletteState.pGammaTable == pTable)
        return;

    if (g_PaletteState.pGammaTable != NULL && g_PaletteState.pGammaTable != g_abGammaNormalRemap)
    {
        CopyMemory(g_PaletteState.abGammaRemap, g_abGammaHighInverseRemap,
                   sizeof(g_PaletteState.abGammaRemap));
        ApplyGammaToColors((u16 *)BG_PLTT, (u16 *)BG_PLTT, 0x400);
        ApplyGammaToColors(g_PaletteState.bg.pShadow, g_PaletteState.bg.pShadow, 0x200);
        ApplyGammaToColors(g_PaletteState.obj.pShadow, g_PaletteState.obj.pShadow, 0x200);
    }

    g_PaletteState.pGammaTable = pTable;
    CopyMemory(g_PaletteState.abGammaRemap, pTable, sizeof(g_PaletteState.abGammaRemap));
    if (pTable != g_abGammaNormalRemap)
    {
        ApplyGammaToColors((u16 *)BG_PLTT, (u16 *)BG_PLTT, 0x400);
        ApplyGammaToColors(g_PaletteState.bg.pShadow, g_PaletteState.bg.pShadow, 0x200);
        ApplyGammaToColors(g_PaletteState.obj.pShadow, g_PaletteState.obj.pShadow, 0x200);
    }
}
