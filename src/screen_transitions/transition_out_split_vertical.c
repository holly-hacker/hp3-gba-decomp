#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Covers the screen from the center row outwards, 2 lines a step on each side.
void TransitionOutSplitVertical(u16 blendArg)
{
    s16 top = SCREEN_HEIGHT / 2;
    s16 bottom;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = SCREEN_WIDTH;
    bottom = SCREEN_HEIGHT / 2;
    REG_WIN0V = (top << 8) | bottom;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;

    while (top >= 0)
    {
        WaitForVBlankIntr();
        top -= 2;
        bottom += 2;
        REG_WIN0V = (top << 8) | bottom;
    }

    REG_BLDY = 16;
    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
