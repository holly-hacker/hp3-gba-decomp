#include "camera.h"

void SetCameraFocusPosition(FixedPoint position, u8 slot)
{
    g_aCameraFocusSlots[slot].focus = position;
}
