#include "actor.h"
#include "actor_inline.h"

// An affine actor is mirrored by the sign of its X scale instead of the OAM flip
// bit. Either way any running scale tween is cancelled.
void SetActorFlippedX(Actor *actor, s32 flip)
{
    if (actor->oam.affineMode == 0)
        actor->oam.hFlip = flip;
    else if (flip)
        StartActorAffineScaleTween(actor, -actor->nAffineScaleX, actor->nAffineScaleY, 0);
    else
        StartActorAffineScaleTween(actor, actor->nAffineScaleX, actor->nAffineScaleY, 0);
}
