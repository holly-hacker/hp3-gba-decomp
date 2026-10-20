#include "types.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "color.h"
#include "screen_transitions.h"
#include "screen_transitions_inline.h"

// Saves the palette to g_pScreenPaletteBackup and fades it to g_dwPaletteFadeColor over
// g_dwPaletteFadeStepTicks steps. Palette loads stay redirected into g_pPaletteWorkBuffer
// afterwards, for TransitionInPaletteFade to fade to.
void TransitionOutPaletteFade(u16 blendArg)
{
    u32 color = g_dwPaletteFadeColor;
    s32 i;
    u32 fill;

    ResetPaletteAnimations();
    bios_CPUFastSet(BG_PLTT, g_pScreenPaletteBackup, 0x100);
    g_dwPaletteRedirect = 1;
    g_dwScreenPaletteDarkened = 1;
    fill = color | (color << 16);
    bios_CPUFastSet(&fill, g_pPaletteWorkBuffer, 0x01000100);
    StartPaletteEffect(0, 0x100, g_dwPaletteFadeStepTicks, g_dwPaletteFadeStepTicks, PALETTE_ANIM_ACTIVE,
                       g_pPaletteWorkBuffer);
    StartPaletteEffect(0, 0x100, g_dwPaletteFadeStepTicks, g_dwPaletteFadeStepTicks,
                       PALETTE_ANIM_ACTIVE | PALETTE_ANIM_OBJ, g_pPaletteWorkBuffer + 0x100);

    for (i = g_dwPaletteFadeStepTicks; i >= 0; i--)
        TickTransitionFrame();
}
