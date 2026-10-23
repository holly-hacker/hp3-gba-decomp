#pragma once

#include "actor.h"
#include "combat_gauge.h"

// The body of DestroyLinkedActor, which TickSpGauge compiles inline: destroys the actor and
// clears the links between it and its linked actor.
static inline void DestroyActorAndUnlink(Actor *actor)
{
    actor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
    if (actor->pLinkedActor != NULL)
    {
        if (actor->pLinkedActor->pLinkedActor != NULL)
            actor->pLinkedActor->pLinkedActor = NULL;
        actor->pLinkedActor = NULL;
    }
}

// The body of UpdateSpGaugeFrame, which TickSpGauge compiles inline: shows the frame for the
// gauge's emptied fraction, out of 24 frames for a party member and 16 for an enemy.
static inline void SetSpGaugeFrame(Actor *gauge)
{
    SpGaugeState *state;
    u32 frameCount;

    state = SP_GAUGE_STATE(gauge);
    frameCount = gauge->wActorType <= 3 ? 24 : 16;
    SetActorAnimFrame(gauge, (state->wMax - state->wValue) * frameCount / state->wMax);
}
