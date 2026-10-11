#include "actor.h"

// Reads anchor point `index` of the actor's current frame of frameData: a
// signed pixel offset from the actor's position. Returns 0, with a zero
// offset, when the frames have fewer anchors.
s32 GetActorFrameAnchor(Actor *actor, ActorFrameData *frameData, u32 index, IntPoint *out)
{
    s8 *anchor;
    s32 found;

    if (index < frameData->bAnchorCount) {
        anchor = (s8 *)frameData->awFrameOffsets + frameData->awFrameOffsets[actor->anim.bLastAnimFrameValue]
                 + (index * 2 + 10);
        out->x = anchor[0];
        out->y = anchor[1];
        found = 1;
    }
    else {
        out->x = 0;
        out->y = 0;
        found = 0;
    }

    return found;
}
