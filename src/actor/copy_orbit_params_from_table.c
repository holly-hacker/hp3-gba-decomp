#include "actor.h"

// Copies a 12-byte {angleX, angleY, velX, velY, radiusX, radiusY} row.
void CopyOrbitParamsFromTable(Actor *actor, const ActorOrbit *row)
{
    actor->orbitState.orbit = *row;
}
