#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Reveals the screen from the right edge leftwards, 3 pixels a step.
void TransitionInWipeLeft(u16 blendArg)
{
    s16 right = SCREEN_WIDTH;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = right;
    REG_WIN0V = SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    WaitForVBlankIntr();
    REG_BLDY = 0;

    while (right >= 0)
    {
        WaitForVBlankIntr();
        right -= 3;
        REG_WIN0H = right;
    }

    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
