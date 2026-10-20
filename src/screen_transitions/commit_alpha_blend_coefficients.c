#include "types.h"
#include "hw/io_regs.h"
#include "screen_transitions.h"

void CommitAlphaBlendCoefficients(void)
{
    REG_BLDALPHA = g_AlphaBlendEvbRamp.wValue | (g_AlphaBlendEvaRamp.wValue >> 8);
}
