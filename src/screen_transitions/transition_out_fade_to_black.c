#include "types.h"
#include "hw/io_regs.h"
#include "screen_transitions.h"
#include "screen_transitions_inline.h"

// Darkens the screen two levels a step, stopping at level 14.
void TransitionOutFadeToBlack(u16 blendArg)
{
    s32 level;

    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    for (level = 0; level < 16; level += 2)
    {
        REG_BLDY = level;
        TickTransitionFrame();
    }
}
