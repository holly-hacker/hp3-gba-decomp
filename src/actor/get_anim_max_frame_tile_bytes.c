#include "actor.h"

// Returns the byte size of the largest frame's tiles in the animation's sprite.
u16 GetAnimMaxFrameTileBytes(ActorAnimState *anim)
{
    ActorFrameData *frameData;

    frameData = anim->pAnimTable->pFrameData;
    return frameData->wMaxFrameTileBytes;
}
