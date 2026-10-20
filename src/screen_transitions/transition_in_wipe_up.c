#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Reveals the screen from the bottom up, 2 lines a step.
void TransitionInWipeUp(u16 blendArg)
{
    s16 bottom = SCREEN_HEIGHT;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = SCREEN_WIDTH;
    REG_WIN0V = bottom;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    WaitForVBlankIntr();
    REG_BLDY = 0;

    while (bottom >= 0)
    {
        WaitForVBlankIntr();
        bottom -= 2;
        REG_WIN0V = bottom;
    }

    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
