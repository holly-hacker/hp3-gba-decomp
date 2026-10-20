#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Covers the screen from the left edge rightwards, 3 pixels a step.
void TransitionOutWipeRight(u16 blendArg)
{
    s16 right = 0;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = right;
    REG_WIN0V = SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;

    while (right <= SCREEN_WIDTH)
    {
        WaitForVBlankIntr();
        right += 3;
        REG_WIN0H = right;
    }

    REG_BLDY = 16;
    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
