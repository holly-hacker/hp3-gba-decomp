#include "types.h"
#include "hw/io_regs.h"
#include "screen_transitions.h"
#include "screen_transitions_inline.h"

// Runs 16 steps of a fade to black, then removes TransitionInLetterbox's bars.
void TransitionOutLetterbox(u16 blendArg)
{
    u16 level;

    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    for (level = 0; level < 16; level++)
    {
        REG_BLDY = level;
        TickTransitionFrame();
    }

    REG_DISPCNT &= ~(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
}
