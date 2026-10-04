#include "graphics/palette.h"

// Copies `size` bytes of BGR555 colors, remapping each channel through the
// active gamma table. pDst may equal pSrc.
u16 *ApplyGammaToColors(u16 *pDst, const u16 *pSrc, u32 size)
{
    u32 count = size / 2;
    u32 i;

    for (i = 0; i < count; i++)
    {
        u8 r = g_PaletteState.abGammaRemap[pSrc[i] & 0x1f];
        u8 g = g_PaletteState.abGammaRemap[(pSrc[i] & 0x3e0) >> 5];
        u8 b = g_PaletteState.abGammaRemap[(pSrc[i] & 0x7c00) >> 10];

        pDst[i] = (r & 0x1f) | ((g << 5) & 0x3e0) | ((b << 10) & 0x7c00);
    }

    return pDst;
}
