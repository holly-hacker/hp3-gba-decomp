#include "graphics/object.h"
#include "math.h"

// Advances the orbit angles and offsets the pending position by
// (radiusX * cos(angleX), radiusY * sin(angleY)).
void ApplyObjectOrbitMotion(Object *obj)
{
    obj->orbitState.orbit.wAngleX += obj->orbitState.orbit.wAngleVelX;
    obj->posPrev.x += g_anSineTable[((obj->orbitState.orbit.wAngleX >> 8) + 0x40) & 0xFF]
                 * obj->orbitState.orbit.wRadiusX;

    obj->orbitState.orbit.wAngleY += obj->orbitState.orbit.wAngleVelY;
    obj->posPrev.y += g_anSineTable[obj->orbitState.orbit.wAngleY >> 8] * obj->orbitState.orbit.wRadiusY;
}
