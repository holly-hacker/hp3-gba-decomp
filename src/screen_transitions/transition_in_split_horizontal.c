#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Reveals the screen from the center column outwards, 3 pixels a step on each side.
void TransitionInSplitHorizontal(u16 blendArg)
{
    s16 left = SCREEN_WIDTH / 2;
    s16 right = SCREEN_WIDTH / 2;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = left;
    REG_WIN0V = SCREEN_HEIGHT;
    REG_WIN1H = (right << 8) | SCREEN_WIDTH;
    REG_WIN1V = SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON | DISPCNT_WIN1_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    WaitForVBlankIntr();
    REG_BLDY = 0;

    while (left >= 0)
    {
        WaitForVBlankIntr();
        left -= 3;
        right += 3;
        REG_WIN0H = left;
        REG_WIN1H = (right << 8) | SCREEN_WIDTH;
    }

    REG_DISPCNT &= ~(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
}
