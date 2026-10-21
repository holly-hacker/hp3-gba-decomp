#include "actor.h"

// angle is in 256ths of a turn.
void SetActorOrbitY(Actor *actor, u16 angle, s16 angleVel, s16 radius)
{
    actor->orbitState.orbit.wAngleY = angle << 8;
    actor->orbitState.orbit.wAngleVelY = angleVel;
    actor->orbitState.orbit.wRadiusY = radius;
}
