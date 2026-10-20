#include "types.h"
#include "hw/io_regs.h"
#include "screen_transitions.h"
#include "screen_transitions_inline.h"

// Shows backdrop bars over the top 32 and bottom 32 lines, then runs 17 steps of a fade from
// black. The layers outside the windows have no color effect, so the fade does not show. The
// bars stay until TransitionOutLetterbox.
void TransitionInLetterbox(u16 blendArg)
{
    s32 level;

    REG_WININ = 0;
    REG_WINOUT = 0x1F;
    REG_WIN0H = SCREEN_WIDTH;
    REG_WIN0V = 32;
    REG_WIN1H = SCREEN_WIDTH;
    REG_WIN1V = (128 << 8) | SCREEN_HEIGHT;
    REG_DISPCNT |= DISPCNT_WIN0_ON | DISPCNT_WIN1_ON;
    REG_BLDCNT = blendArg | BLDCNT_DARKEN;

    for (level = 16; level >= 0; level--)
    {
        REG_BLDY = level;
        TickTransitionFrame();
    }
}
