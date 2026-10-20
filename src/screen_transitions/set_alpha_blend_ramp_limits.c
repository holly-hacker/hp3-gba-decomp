#include "types.h"
#include "screen_transitions.h"

// Takes whole coefficients.
void SetAlphaBlendRampLimits(s32 evaMin, s32 evaMax, s32 evbMin, s32 evbMax)
{
    g_AlphaBlendEvaRamp.wMin = evaMin << 8;
    g_AlphaBlendEvaRamp.wMax = evaMax << 8;
    g_AlphaBlendEvbRamp.wMin = evbMin << 8;
    g_AlphaBlendEvbRamp.wMax = evbMax << 8;
}
