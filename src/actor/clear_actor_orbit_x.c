#include "actor.h"

void ClearActorOrbitX(Actor *actor)
{
    actor->orbitState.orbit.wAngleX = 0;
    actor->orbitState.orbit.wAngleVelX = 0;
    actor->orbitState.orbit.wRadiusX = 0;
}
