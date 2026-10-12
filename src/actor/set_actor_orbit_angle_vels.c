#include "actor.h"

void SetActorOrbitAngleVels(Actor *actor, s16 angleVelX, s16 angleVelY)
{
    actor->orbitState.orbit.wAngleVelX = angleVelX;
    actor->orbitState.orbit.wAngleVelY = angleVelY;
}
