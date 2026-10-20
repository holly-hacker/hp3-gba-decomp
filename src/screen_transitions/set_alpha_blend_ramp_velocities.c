#include "types.h"
#include "screen_transitions.h"

// Takes 8.8 fixed-point steps.
void SetAlphaBlendRampVelocities(s32 evaVelocity, s32 evbVelocity)
{
    g_AlphaBlendEvaRamp.wVelocity = evaVelocity;
    g_AlphaBlendEvbRamp.wVelocity = evbVelocity;
}
