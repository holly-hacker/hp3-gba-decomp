#include "actor.h"

void SetActorOrbitAngleVels(Actor *actor, u16 angleVelX, u16 angleVelY)
{
    actor->orbitState.orbit.wAngleVelX = angleVelX;
    actor->orbitState.orbit.wAngleVelY = angleVelY;
}
