#include "types.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "color.h"
#include "screen_transitions.h"
#include "screen_transitions_inline.h"

// Fades palette RAM to g_pPaletteWorkBuffer over g_dwPaletteFadeStepTicks steps. The work buffer
// first takes g_pScreenPaletteBackup while g_dwScreenPaletteDarkened is set, else keeps the
// palette loads redirected into it, else takes the current palette RAM.
void TransitionInPaletteFade(u16 blendArg)
{
    s32 i;

    if (g_dwScreenPaletteDarkened)
    {
        g_dwScreenPaletteDarkened = 0;
        bios_CPUFastSet(g_pScreenPaletteBackup, g_pPaletteWorkBuffer, 0x100);
    }
    else if (!g_dwPaletteRedirect)
        bios_CPUFastSet(BG_PLTT, g_pPaletteWorkBuffer, 0x100);

    g_dwPaletteRedirect = 1;
    StartPaletteEffect(0, 0x100, g_dwPaletteFadeStepTicks, 0, PALETTE_ANIM_ACTIVE, g_pPaletteWorkBuffer);
    StartPaletteEffect(0, 0x100, g_dwPaletteFadeStepTicks, 0, PALETTE_ANIM_ACTIVE | PALETTE_ANIM_OBJ,
                       g_pPaletteWorkBuffer + 0x100);

    for (i = g_dwPaletteFadeStepTicks; i >= 0; i--)
        TickTransitionFrame();

    g_dwPaletteRedirect = 0;
    RestorePalettes(g_pPaletteWorkBuffer);
}
