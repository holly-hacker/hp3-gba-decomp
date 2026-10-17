#include "camera.h"

#include "scroll.h"

void GetCameraFocusScreenPosition(s32 *pPosition, u8 slot)
{
    GetCameraPosition(pPosition);
    pPosition[0] = (s16)(g_aCameraFocusSlots[slot].focus.x >> 16) - pPosition[0];
    pPosition[1] = (s16)(g_aCameraFocusSlots[slot].focus.y >> 16) - pPosition[1];
}
