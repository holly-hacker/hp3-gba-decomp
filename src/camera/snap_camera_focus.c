#include "camera.h"

void SnapCameraFocus(FixedPoint position, u8 slot)
{
    g_aCameraFocusSlots[slot].latched = position;
    g_aCameraFocusSlots[slot].focus = position;
}
