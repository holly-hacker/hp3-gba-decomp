#include "actor.h"

u16 GetAnimFrameCount(ActorAnimState *anim)
{
    ActorFrameData *frameData;

    frameData = anim->pAnimTable->pFrameData;
    return frameData->wFrameCount;
}
