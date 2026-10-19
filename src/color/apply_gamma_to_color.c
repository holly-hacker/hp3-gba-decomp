#include "color.h"

u16 ApplyGammaToColor(u16 color)
{
    u8 r = g_PaletteState.abGammaRemap[color & 0x1f];
    u8 g = g_PaletteState.abGammaRemap[(color & 0x3e0) >> 5];
    u8 b = g_PaletteState.abGammaRemap[(color & 0x7c00) >> 10];

    return (r & 0x1f) | ((g << 5) & 0x3e0) | ((b << 10) & 0x7c00);
}
