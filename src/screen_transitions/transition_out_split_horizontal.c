#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Covers the screen from the center column outwards, 3 pixels a step on each side.
void TransitionOutSplitHorizontal(u16 blendArg)
{
    s16 left = SCREEN_WIDTH / 2;
    s16 right;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    right = SCREEN_WIDTH / 2;
    REG_WIN0H = (left << 8) | right;
    REG_WIN0V = SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;

    while (left >= 0)
    {
        WaitForVBlankIntr();
        left -= 3;
        right += 3;
        REG_WIN0H = (left << 8) | right;
    }

    REG_BLDY = 16;
    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
