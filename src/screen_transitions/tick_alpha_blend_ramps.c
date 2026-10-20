#include "types.h"
#include "screen_transitions.h"
#include "screen_transitions_inline.h"

static inline void StepAlphaBlendRamp(AlphaBlendRamp *pRamp)
{
    pRamp->wValue += pRamp->wVelocity;
    if (pRamp->wValue <= pRamp->wMin)
    {
        pRamp->wValue = pRamp->wMin;
        pRamp->wVelocity = -pRamp->wVelocity;
    }
    else if (pRamp->wValue >= pRamp->wMax)
    {
        pRamp->wValue = pRamp->wMax;
        pRamp->wVelocity = -pRamp->wVelocity;
    }
}

void TickAlphaBlendRamps(void)
{
    StepAlphaBlendRamp(&g_AlphaBlendEvaRamp);
    StepAlphaBlendRamp(&g_AlphaBlendEvbRamp);
    SetAlphaBlendCoefficientsInline(g_AlphaBlendEvaRamp.wValue >> 8, g_AlphaBlendEvbRamp.wValue >> 8);
}
