#include "camera.h"

void SetCameraFocusPinned(u32 pinned, u8 slot)
{
    g_aCameraFocusSlots[slot].wPinned = pinned;
    g_aCameraEffects_candidate[slot].bState = 0;
    switch (pinned)
    {
    case 0:
        break;
    case 1:
        g_aCameraFocusSlots[slot].pTarget = 0;
        break;
    }
}
