#include "actor.h"

void SetActorMoveTarget(Actor *actor, u32 x, u32 y)
{
    actor->moveTarget.x = x;
    actor->moveTarget.y = y;
}
