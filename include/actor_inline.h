#pragma once

#include "types.h"
#include "actor.h"
#include "random.h"

// The ROM compiles StartActorAffineScaleTween into SetActorFlippedX/Y and also
// keeps an out-of-line copy, as one translation unit with an inline definition
// would. The file that emits the out-of-line copy defines the linkage macro as
// empty.
#ifndef START_ACTOR_AFFINE_SCALE_TWEEN_LINKAGE
#define START_ACTOR_AFFINE_SCALE_TWEEN_LINKAGE extern inline
#endif

// Ramps nAffineScaleX/Y to the target over nFrames ticks of
// TickActorAffineEffect; with nFrames 0 the scale is set immediately.
START_ACTOR_AFFINE_SCALE_TWEEN_LINKAGE void StartActorAffineScaleTween(Actor *actor, u32 nTargetScaleX,
                                                                       u32 nTargetScaleY, s32 nFrames)
{
    actor->bAffineEffectTimer = nFrames;
    if (nFrames != 0) {
        actor->nAffineScaleVelX = (s32)(nTargetScaleX - actor->nAffineScaleX) / nFrames;
        actor->nAffineScaleVelY = (s32)(nTargetScaleY - actor->nAffineScaleY) / nFrames;
    }
    else {
        SetActorAffineTransform(actor, nTargetScaleX, nTargetScaleY, actor->wAffineAngle, actor->bAffineMode);
    }
}

// The route walkers compile TickActorIdle into their default case; the
// out-of-line copy has no callers.
#ifndef TICK_ACTOR_IDLE_LINKAGE
#define TICK_ACTOR_IDLE_LINKAGE extern inline
#endif

// Sub-states shared by actors that are not walking: 5 returns to action state 1, and 10
// looks in a random direction every 20 ticks.
TICK_ACTOR_IDLE_LINKAGE void TickActorIdle(Actor *actor)
{
    switch (actor->bActionSubState) {
    case 2:
        break;
    case 5:
        SetActorActionState(actor, 1);
        break;
    case 7:
        break;
    case 10:
        if (--actor->dwStateTimer == -1) {
            SetActorActionSubState(actor, 3);
            SetActorFacing(actor, Mt19937RandRange(0, 7));
            actor->dwStateTimer = 20;
        }
        break;
    }
}
