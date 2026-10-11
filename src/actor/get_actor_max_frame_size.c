#include "actor.h"

// Writes the largest frame width and height of the actor's sprite, in pixels,
// to dims[0] and dims[1].
void GetActorMaxFrameSize(Actor *actor, u32 *dims)
{
    ActorFrameData *frameData;

    frameData = actor->anim.pAnimTable->pFrameData;
    dims[0] = frameData->bMaxFrameWidth;
    dims[1] = frameData->bMaxFrameHeight;
}
