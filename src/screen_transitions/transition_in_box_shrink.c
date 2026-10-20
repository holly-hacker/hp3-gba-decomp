#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Reveals the screen from its edges as a backdrop box shrinks to the center.
void TransitionInBoxShrink(u16 blendArg)
{
    s16 left = 0;
    s16 right = SCREEN_WIDTH;
    s16 top = 0;
    s16 bottom = SCREEN_HEIGHT;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = right;
    REG_WIN0V = bottom;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    WaitForVBlankIntr();
    REG_BLDY = 0;

    while (top < SCREEN_HEIGHT / 2)
    {
        WaitForVBlankIntr();
        top += 2;
        bottom -= 2;
        left += 3;
        right -= 3;
        REG_WIN0H = (left << 8) | right;
        REG_WIN0V = (top << 8) | bottom;
    }

    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
