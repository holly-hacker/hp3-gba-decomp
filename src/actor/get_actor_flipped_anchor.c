#include "actor.h"

// GetActorAnchor, mirrored horizontally when the sprite is flipped.
s32 GetActorFlippedAnchor(Actor *actor, u32 index, IntPoint *out)
{
    s32 found;

    found = GetActorFrameAnchor(actor, actor->anim.pAnimTable->pFrameData, index, out);
    if (actor->oam.hFlip)
        out->x = -out->x;
    return found;
}
