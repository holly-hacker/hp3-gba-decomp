#include "types.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "screen_transitions.h"

// Covers the screen with a backdrop box growing from the center.
void TransitionOutBoxExpand(u16 blendArg)
{
    s16 left = SCREEN_WIDTH / 2;
    s16 top = SCREEN_HEIGHT / 2;
    s16 right;
    s16 bottom;

    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    right = SCREEN_WIDTH / 2;
    REG_WIN0H = (left << 8) | right;
    bottom = SCREEN_HEIGHT / 2;
    REG_WIN0V = (top << 8) | bottom;
    REG_DISPCNT |= DISPCNT_WIN0_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;

    while (top >= 0)
    {
        WaitForVBlankIntr();
        top -= 2;
        bottom += 2;
        left -= 3;
        right += 3;
        REG_WIN0H = (left << 8) | right;
        REG_WIN0V = (top << 8) | bottom;
    }

    REG_BLDY = 16;
    REG_DISPCNT &= ~(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
}
