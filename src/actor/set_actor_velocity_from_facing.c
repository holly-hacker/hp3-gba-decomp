#include "actor.h"

// Moves the actor in its facing direction at nMoveSpeed.
void SetActorVelocityFromFacing(Actor *actor)
{
    FixedPoint vel;

    GetDirectionVector(&vel, actor->dwFlags, actor->bFacing, actor->nMoveSpeed);
    actor->vel.x = vel.x;
    actor->vel.y = vel.y;
}
