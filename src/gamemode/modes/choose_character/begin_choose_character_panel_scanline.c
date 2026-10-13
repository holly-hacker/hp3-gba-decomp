#include "types.h"
#include "graphics/scanline_effects.h"
#include "hw/io_regs.h"
#include "menu/choose_character.h"

// Runs at the top of the panel: turns window 0 on and scrolls BG2 so the panel row sits at
// the current scanline.
void BeginChooseCharacterPanelScanline(u32 *pPayload0, u32 *pPayload1)
{
    s32 scrollY = g_dwChooseCharacterBgRow * 8 - GetScanlineEffectLine(0) - 1;

    while (!(REG_DISPSTAT & 2))
        ;

    REG_DISPCNT |= 0x2000;
    REG_BG2HOFS = 0;
    REG_BG2VOFS = scrollY;
}
