#include "types.h"
#include "background.h"
#include "choose_party_member.h"
#include "hw/io_regs.h"

// Runs at the bottom of the panel: turns window 0 off and restores BG2's own scroll.
void EndChooseCharacterPanelScanline(u32 *pPayload0, u32 *pPayload1)
{
    s32 scroll[2];

    GetBgScroll(2, &scroll[0], &scroll[1]);
    scroll[0] >>= 16;
    scroll[1] >>= 16;

    while (!(REG_DISPSTAT & 2))
        ;

    REG_DISPCNT &= ~0x2000;
    REG_BG2HOFS = scroll[0];
    REG_BG2VOFS = scroll[1];
}
