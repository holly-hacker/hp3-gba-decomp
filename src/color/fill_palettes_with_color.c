#include "color.h"
#include "hw/bios.h"
#include "hw/io_regs.h"

// Fills palette RAM with the gamma-corrected color.
void FillPalettesWithColor(u32 color)
{
    u32 bgFill;
    u32 bgShadowFill;
    u32 objShadowFill;

    color = ApplyGammaToColor(color);
    color |= color << 16;

    bgFill = color;
    bios_CPUFastSet(&bgFill, BG_PLTT, 0x01000100);
    // BUG: fills only the first 16 colors of each shadow, unlike palette RAM.
    bgShadowFill = color;
    bios_CPUFastSet(&bgShadowFill, g_PaletteState.bg.pShadow, 0x01000001);
    objShadowFill = color;
    bios_CPUFastSet(&objShadowFill, g_PaletteState.obj.pShadow, 0x01000001);
}
