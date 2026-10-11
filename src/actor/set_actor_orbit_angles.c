#include "actor.h"

// Angles are in 256ths of a turn.
void SetActorOrbitAngles(Actor *actor, s32 angleX, s32 angleY)
{
    actor->orbitState.orbit.wAngleX = angleX << 8;
    actor->orbitState.orbit.wAngleY = angleY << 8;
}
