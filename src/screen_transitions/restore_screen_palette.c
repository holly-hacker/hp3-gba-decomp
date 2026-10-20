#include "types.h"
#include "hw/bios.h"
#include "color.h"
#include "screen_transitions.h"

// Fades the BG palette back to the one DarkenScreenPalette saved.
void RestoreScreenPalette(void)
{
    g_dwScreenPaletteDarkened = 0;
    bios_CPUFastSet(g_pScreenPaletteBackup, g_pPaletteWorkBuffer, 0x80);
    g_dwPaletteRedirect = 1;
    StartPaletteEffect(0, 0x100, g_dwPaletteFadeStepTicks, g_dwPaletteFadeStepTicks, PALETTE_ANIM_ACTIVE,
                       g_pPaletteWorkBuffer);
    g_dwPaletteRedirect = 0;
}
