#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Reveals the screen from the top down, 2 lines a step.
void TransitionInWipeDown(u16 blendArg)
{
    s16 top = 0;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = SCREEN_WIDTH;
    REG_WIN0V = SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    WaitForVBlankIntr();
    REG_BLDY = 0;

    while (top <= SCREEN_HEIGHT)
    {
        WaitForVBlankIntr();
        top += 2;
        REG_WIN0V = (top << 8) | SCREEN_HEIGHT;
    }

    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
