#include "actor.h"

// Switches to the given animation frame, reloading its cells when the frame changed
// or the actor is flagged for a reload; always clears ActorFlagActionAnimDone.
void SetActorAnimFrame(Actor *actor, u8 frameIndex)
{
    if (actor->anim.bLastAnimFrameValue != frameIndex || (actor->dwFlags & ActorFlagAnimFrameLoaded)) {
        actor->anim.bLastAnimFrameValue = frameIndex;
        actor->anim.bAnimFrameCounter = actor->anim.bAnimFrameDelay;
        LoadActorAnimFrameBounds(actor);
    }

    actor->dwFlags &= ~ActorFlagActionAnimDone;
}
