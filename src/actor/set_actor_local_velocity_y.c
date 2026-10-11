#include "actor.h"

void SetActorLocalVelocityY(Actor *actor, s32 velY)
{
    if (actor->oam.vFlip)
        velY = -velY;
    actor->vel.y = velY;
}
