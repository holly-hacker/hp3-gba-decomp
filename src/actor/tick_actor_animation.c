#include "actor.h"

// Counts down the current frame's ticks. When they run out, an actor with a
// command stream runs its next commands; one without cycles through every frame
// of its sprite record, reloading the counter from bAnimFrameDelay.
void TickActorAnimation(Actor *actor)
{
    u8 *cursor;
    u8 frame;
    ActorFrameData *frameData;

    if (!(actor->dwFlags & ActorFlagHasAnimation) || actor->anim.bAnimFrameCounter == 0
        || (actor->dwFlags & ActorFlagAnimPaused))
        return;

    if (--actor->anim.bAnimFrameCounter != 0)
        return;

    cursor = actor->anim.pAnimFrameCursor;
    if (cursor == NULL) {
        actor->anim.bLastAnimFrameValue++;
        if (actor->anim.bLastAnimFrameValue >= actor->anim.pAnimTable->pFrameData->wFrameCount)
            actor->anim.bLastAnimFrameValue = 0;

        frame = actor->anim.bLastAnimFrameValue;
        frameData = actor->anim.pAnimTable->pFrameData;
        if (frame == frameData->wFrameCount - 1 || frameData->wFrameCount == 1)
            actor->dwFlags |= ActorFlagActionAnimDone;

        actor->anim.bAnimFrameCounter = actor->anim.bAnimFrameDelay;
        LoadActorAnimFrameBounds(actor);
    }
    else if (!(actor->dwFlags & ActorFlagActionAnimDone)) {
        actor->anim.pAnimFrameCursor = cursor + 2;
        RunActorAnimCommands(actor);
        LoadActorAnimFrameBounds(actor);
    }
}
