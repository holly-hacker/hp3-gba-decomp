#include "actor.h"

void SetActorPosition(Actor *actor, s32 x, s32 y)
{
    actor->pos.x = x << 16;
    actor->pos.y = y << 16;
    actor->posPrev.x = actor->pos.x;
    actor->posPrev.y = actor->pos.y;
}
