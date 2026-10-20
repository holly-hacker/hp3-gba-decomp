#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Reveals the screen through a box growing from the center.
void TransitionInBoxExpand(u16 blendArg)
{
    s16 left = SCREEN_WIDTH / 2;
    s16 top = SCREEN_HEIGHT / 2;
    s16 right;
    s16 bottom;

    REG_WININ = 0x3F;
    REG_WINOUT = 0;
    right = SCREEN_WIDTH / 2;
    REG_WIN0H = (left << 8) | right;
    bottom = SCREEN_HEIGHT / 2;
    REG_WIN0V = (top << 8) | bottom;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    WaitForVBlankIntr();
    REG_BLDY = 0;

    while (top >= 0)
    {
        WaitForVBlankIntr();
        top -= 2;
        bottom += 2;
        left -= 3;
        right += 3;
        REG_WIN0H = (left << 8) | right;
        REG_WIN0V = (top << 8) | bottom;
    }

    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
