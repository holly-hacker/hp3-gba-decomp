#include "types.h"
#include "actor.h"
#include "combat_gauge.h"
#include "combat_gauge_inline.h"
#include "screen_transitions.h"

// pfnTick of a draining gauge: fades it in over 8 ticks, drains it every other tick, then
// fades it out over 6 ticks and destroys it.
void TickSpGauge(Actor *gauge)
{
    SpGaugeState *state;
    u32 timer;
    s32 step;
    s32 remaining;

    timer = --gauge->dwStateTimer;
    switch (gauge->bActionSubState)
    {
    case SpGaugeDrain:
        if (timer != 0)
            break;
        state = SP_GAUGE_STATE(gauge);
        state->nDrainStep += state->wDrainRate;
        step = state->nDrainStep >> 8;
        if (step > 0)
        {
            step = state->wValue <= step ? state->wValue : step;
            remaining = state->wDrainTotal - state->wDrained;
            step = remaining <= step ? remaining : step;
            state->wValue -= step;
            state->wDrained += step;
            SetSpGaugeFrame(gauge);
        }
        if (state->wDrained == state->wDrainTotal)
        {
            gauge->bActionSubState = SpGaugeFadeOut;
            gauge->dwStateTimer = 6;
        }
        else
        {
            gauge->dwStateTimer = 2;
        }
        break;
    case SpGaugeFadeIn:
        if (timer == 0)
        {
            SetAlphaBlendCoefficients(16, 0);
            gauge->bActionSubState = SpGaugeDrain;
            gauge->dwStateTimer = 6;
        }
        else
        {
            SetAlphaBlendCoefficients(16 - timer * 2, timer * 2);
        }
        break;
    case SpGaugeFadeOut:
        if (timer == 0)
            DestroyActorAndUnlink(gauge);
        else
            SetAlphaBlendCoefficients(timer * 2, 16 - timer * 2);
        break;
    }
}
