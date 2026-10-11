#include "types.h"
#include "actor.h"

void TickActorAffineEffect(Actor *actor)
{
    actor->bAffineEffectTimer--;
    actor->nAffineScaleX += actor->nAffineScaleVelX;
    actor->nAffineScaleY += actor->nAffineScaleVelY;
    SetActorAffineTransform(actor, actor->nAffineScaleX, actor->nAffineScaleY, actor->wAffineAngle,
                             actor->bAffineMode);
}
