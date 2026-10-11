#include "actor.h"
#include "math.h"

// Advances the orbit angles and offsets the pending position by
// (radiusX * cos(angleX), radiusY * sin(angleY)).
void ApplyActorOrbitMotion(Actor *actor)
{
    actor->orbitState.orbit.wAngleX += actor->orbitState.orbit.wAngleVelX;
    actor->posPrev.x += g_anSineTable[((actor->orbitState.orbit.wAngleX >> 8) + 0x40) & 0xFF]
                 * actor->orbitState.orbit.wRadiusX;

    actor->orbitState.orbit.wAngleY += actor->orbitState.orbit.wAngleVelY;
    actor->posPrev.y += g_anSineTable[actor->orbitState.orbit.wAngleY >> 8] * actor->orbitState.orbit.wRadiusY;
}
