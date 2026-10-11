#include "actor.h"

void ClearActorOrbitY(Actor *actor)
{
    actor->orbitState.orbit.wAngleY = 0;
    actor->orbitState.orbit.wAngleVelY = 0;
    actor->orbitState.orbit.wRadiusY = 0;
}
