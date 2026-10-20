#include "types.h"
#include "color.h"
#include "screen_transitions.h"

// Saves the BG palette shadow to g_pScreenPaletteBackup and fades the BG palette to half
// brightness.
void DarkenScreenPalette(void)
{
    s32 i;
    u16 color;
    u16 red;
    u16 green;
    u16 blue;
    u16 *pDst;
    u16 *pSrc;

    ResetPaletteAnimations();
    SaveBgPaletteShadow(g_pScreenPaletteBackup);
    g_dwPaletteRedirect = 1;
    g_dwScreenPaletteDarkened = 1;

    pDst = g_pPaletteWorkBuffer;
    pSrc = g_pScreenPaletteBackup;
    for (i = 0; i < 256; i++)
    {
        color = pSrc[i];
        red = color & 0x1E;
        green = color & 0x3C0;
        blue = color & 0x7800;
        pDst[i] = (red | green | blue) >> 1;
    }

    StartPaletteEffect(0, 0x100, g_dwPaletteFadeStepTicks, g_dwPaletteFadeStepTicks, PALETTE_ANIM_ACTIVE,
                       g_pPaletteWorkBuffer);
    g_dwPaletteRedirect = 0;
}
