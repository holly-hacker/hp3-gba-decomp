#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Reveals the screen from both side edges towards the center, 3 pixels a step on each side.
void TransitionInConvergeHorizontal(u16 blendArg)
{
    s16 left = 0;
    s16 right = SCREEN_WIDTH;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = right;
    REG_WIN0V = SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    WaitForVBlankIntr();
    REG_BLDY = 0;

    while (left < SCREEN_WIDTH / 2)
    {
        WaitForVBlankIntr();
        left += 3;
        right -= 3;
        REG_WIN0H = (left << 8) | right;
    }

    REG_DISPCNT &= ~DISPCNT_WIN0_ON;
}
