#include "actor.h"
#include "actor_inline.h"

// An affine actor is mirrored by the sign of its Y scale instead of the OAM flip
// bit. Either way any running scale tween is cancelled.
void SetActorFlippedY(Actor *actor, s32 flip)
{
    if (actor->oam.affineMode == 0)
        actor->oam.vFlip = flip;
    else if (flip)
        StartActorAffineScaleTween(actor, actor->nAffineScaleX, -actor->nAffineScaleY, 0);
    else
        StartActorAffineScaleTween(actor, actor->nAffineScaleX, actor->nAffineScaleY, 0);
}
