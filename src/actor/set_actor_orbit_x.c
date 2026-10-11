#include "actor.h"

// angle is in 256ths of a turn.
void SetActorOrbitX(Actor *actor, s32 angle, s16 angleVel, s16 radius)
{
    actor->orbitState.orbit.wAngleX = angle << 8;
    actor->orbitState.orbit.wAngleVelX = angleVel;
    actor->orbitState.orbit.wRadiusX = radius;
}
