#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Covers the screen from the right edge leftwards, 3 pixels a step.
void TransitionOutWipeLeft(u16 blendArg)
{
    s16 left = SCREEN_WIDTH;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = (left << 8) | SCREEN_WIDTH;
    REG_WIN0V = SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;

    while (left >= 0)
    {
        WaitForVBlankIntr();
        left -= 3;
        REG_WIN0H = (left << 8) | SCREEN_WIDTH;
    }

    REG_BLDY = 16;
    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
