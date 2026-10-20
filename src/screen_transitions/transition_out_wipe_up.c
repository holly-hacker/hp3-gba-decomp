#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Covers the screen from the bottom up, 2 lines a step.
void TransitionOutWipeUp(u16 blendArg)
{
    s16 top = SCREEN_HEIGHT;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = SCREEN_WIDTH;
    REG_WIN0V = (top << 8) | SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;

    while (top >= 0)
    {
        WaitForVBlankIntr();
        top -= 2;
        REG_WIN0V = (top << 8) | SCREEN_HEIGHT;
    }

    REG_BLDY = 16;
    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
