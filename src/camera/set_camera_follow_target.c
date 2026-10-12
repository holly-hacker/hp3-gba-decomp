#include "camera.h"

void SetCameraFollowTarget_candidate(Actor *pTarget, CameraFocusOffset offset, u8 slot)
{
    g_aCameraFocusSlots[slot].pTarget = pTarget;
    g_aCameraFollowOffsets[slot] = offset;
    g_aCameraFocusSlots[slot].latched = pTarget->pos;
    g_aCameraFocusSlots[slot].focus = g_aCameraFocusSlots[slot].latched;
}
