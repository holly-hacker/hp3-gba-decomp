#include "camera.h"

void ResetCameraFocusSlot(u8 slot)
{
    FixedPoint zero = { 0, 0 };

    g_aCameraFocusSlots[slot].focus = zero;
    g_aCameraFocusSlots[slot].unk08 = zero;
    g_aCameraFocusSlots[slot].unk10 = zero;
    g_aCameraFocusSlots[slot].latched = zero;
    g_aCameraFocusSlots[slot].wPinned = 1;
    g_aCameraFocusSlots[slot].pTarget = 0;
    g_aCameraEffects_candidate[slot].wCounter = 0;
    g_aCameraEffects_candidate[slot].bState = 0;
}
