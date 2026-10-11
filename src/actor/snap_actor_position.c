#include "actor.h"

void SnapActorPosition(Actor *actor, u32 x, u32 y)
{
    actor->pos.x = x;
    actor->pos.y = y;
    actor->posPrev.x = x;
    actor->posPrev.y = y;
}
