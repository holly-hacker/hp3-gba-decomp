#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Covers the screen from the top and bottom edges towards the center, 2 lines a step on each
// side.
void TransitionOutConvergeVertical(u16 blendArg)
{
    s16 top = 0;
    s16 bottom = SCREEN_HEIGHT;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_WIN0H = SCREEN_WIDTH;
    REG_WIN0V = top;
    REG_WIN1H = SCREEN_WIDTH;
    REG_WIN1V = (bottom << 8) | SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON | DISPCNT_WIN1_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;

    while (top <= SCREEN_HEIGHT / 2)
    {
        WaitForVBlankIntr();
        top += 2;
        bottom -= 2;
        REG_WIN0V = top;
        REG_WIN1V = (bottom << 8) | SCREEN_HEIGHT;
    }

    REG_BLDY = 16;
    REG_DISPCNT &= ~(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
}
