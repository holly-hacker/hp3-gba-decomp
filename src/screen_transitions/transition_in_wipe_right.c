#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Reveals the screen from the left edge rightwards, 3 pixels a step.
void TransitionInWipeRight(u16 blendArg)
{
    s16 left = 0;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = SCREEN_WIDTH;
    REG_WIN0V = SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    WaitForVBlankIntr();
    REG_BLDY = 0;

    while (left <= SCREEN_WIDTH)
    {
        WaitForVBlankIntr();
        left += 3;
        REG_WIN0H = (left << 8) | SCREEN_WIDTH;
    }

    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
