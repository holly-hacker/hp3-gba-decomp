#include "actor.h"

// Like SetActorActionState: no-op if unchanged, otherwise stores the value and
// raises bActionFlags bit 0x4. Also resumes animation (sets ActorFlagHasAnimation,
// clears ActorFlagActionAnimDone).
void SetActorAnimSet_candidate(Actor *actor, u8 animSet)
{
    if (animSet != actor->bAnimSet_candidate) {
        actor->bAnimSet_candidate = animSet;
        actor->dwFlags |= ActorFlagHasAnimation;
        actor->bActionFlags |= 4;
        actor->dwFlags &= ~ActorFlagActionAnimDone;
    }
}
