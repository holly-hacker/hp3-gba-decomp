#include "actor.h"

void SetActorOrbitRadii(Actor *actor, s16 radiusX, s16 radiusY)
{
    actor->orbitState.orbit.wRadiusX = radiusX;
    actor->orbitState.orbit.wRadiusY = radiusY;
}
