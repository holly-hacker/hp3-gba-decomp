#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Covers the screen from the top down, 2 lines a step.
void TransitionOutWipeDown(u16 blendArg)
{
    s16 bottom = 0;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = SCREEN_WIDTH;
    REG_WIN0V = bottom;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;

    while (bottom <= SCREEN_HEIGHT)
    {
        WaitForVBlankIntr();
        bottom += 2;
        REG_WIN0V = bottom;
    }

    REG_BLDY = 16;
    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
