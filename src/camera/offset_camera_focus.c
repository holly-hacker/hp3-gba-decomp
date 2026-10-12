#include "camera.h"

void OffsetCameraFocus(FixedPoint delta, u8 slot)
{
    g_aCameraFocusSlots[slot].focus.x += delta.x;
    g_aCameraFocusSlots[slot].focus.y += delta.y;
    g_aCameraFocusSlots[slot].latched = g_aCameraFocusSlots[slot].focus;
}
