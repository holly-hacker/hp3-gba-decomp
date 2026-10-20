#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Reveals the screen from the center row outwards, 2 lines a step on each side.
void TransitionInSplitVertical(u16 blendArg)
{
    s16 top = SCREEN_HEIGHT / 2;
    s16 bottom = SCREEN_HEIGHT / 2;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = SCREEN_WIDTH;
    REG_WIN0V = top;
    REG_WIN1H = SCREEN_WIDTH;
    REG_WIN1V = (bottom << 8) | SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON | DISPCNT_WIN1_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    WaitForVBlankIntr();
    REG_BLDY = 0;

    while (top >= 0)
    {
        WaitForVBlankIntr();
        top -= 2;
        bottom += 2;
        REG_WIN0V = top;
        REG_WIN1V = (bottom << 8) | SCREEN_HEIGHT;
    }

    REG_DISPCNT &= ~(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
}
