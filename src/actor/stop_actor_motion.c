#include "actor.h"

// Zeroes the velocity and acceleration; the move target is kept.
void StopActorMotion(Actor *actor)
{
    actor->accel.x = 0;
    actor->accel.y = 0;
    actor->vel.x = 0;
    actor->vel.y = 0;
}
