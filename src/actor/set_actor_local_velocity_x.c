#include "actor.h"

// Sets a velocity component in the sprite's own frame: mirrored on the axis
// the sprite is flipped on.
void SetActorLocalVelocityX(Actor *actor, s32 velX)
{
    if (actor->oam.hFlip)
        velX = -velX;
    actor->vel.x = velX;
}
