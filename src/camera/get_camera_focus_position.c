#include "camera.h"

void GetCameraFocusPosition(FixedPoint *pPosition, u8 slot)
{
    *pPosition = g_aCameraFocusSlots[slot].focus;
}
