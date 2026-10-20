#include "types.h"
#include "hw/io_regs.h"
#include "screen_transitions.h"
#include "screen_transitions_inline.h"

// Brightens the screen two levels a step up to full white.
void TransitionOutFadeToWhite(u16 blendArg)
{
    s32 level;

    REG_BLDCNT = blendArg | BLDCNT_BRIGHTEN;
    for (level = 0; level <= 16; level += 2)
    {
        REG_BLDY = level;
        TickTransitionFrame();
    }
}
