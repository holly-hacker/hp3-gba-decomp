#include "actor.h"

void SetActorVelocity(Actor *actor, u32 velX, u32 velY)
{
    actor->vel.x = velX;
    actor->vel.y = velY;
}
