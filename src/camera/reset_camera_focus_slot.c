#include "camera.h"

void ResetCameraFocusSlot(u8 slot)
{
    FixedPoint zero = { 0, 0 };

    g_aCameraFocusSlots[slot].focus = zero;
    g_aCameraFocusSlots[slot].aUnused[0] = zero;
    g_aCameraFocusSlots[slot].aUnused[1] = zero;
    g_aCameraFocusSlots[slot].latched = zero;
    g_aCameraFocusSlots[slot].wPinned = 1;
    g_aCameraFocusSlots[slot].pTarget = 0;
    g_aCameraEffects[slot].wCounter = 0;
    g_aCameraEffects[slot].bState = 0;
}
