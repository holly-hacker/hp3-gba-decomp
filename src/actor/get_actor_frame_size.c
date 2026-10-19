#include "actor.h"

// Writes the pixel width and height of the actor's current animation frame to
// dims[0] and dims[1].
void GetActorFrameSize(Actor *actor, u32 *dims)
{
    ActorFrameData *frameData;
    ActorFrameDesc *frameDesc;

    frameData = actor->anim.pAnimTable->pFrameData;
    frameDesc = ACTOR_FRAME_DESC(frameData, actor->anim.bLastAnimFrameValue);
    dims[0] = frameDesc->bWidth;
    dims[1] = frameDesc->bHeight;
}
