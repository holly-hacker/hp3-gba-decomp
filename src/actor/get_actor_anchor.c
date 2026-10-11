#include "actor.h"

s32 GetActorAnchor(Actor *actor, u32 index, IntPoint *out)
{
    return GetActorFrameAnchor(actor, actor->anim.pAnimTable->pFrameData, index, out);
}
