#include "types.h"
#include "hw/io_regs.h"
#include "screen_transitions.h"
#include "screen_transitions_inline.h"

// Unbrightens the screen from full white, two levels a step.
void TransitionInFadeFromWhite(u16 blendArg)
{
    s32 level;

    REG_BLDCNT = blendArg | BLDCNT_BRIGHTEN;
    for (level = 16; level >= 0; level -= 2)
    {
        REG_BLDY = level;
        TickTransitionFrame();
    }
}
