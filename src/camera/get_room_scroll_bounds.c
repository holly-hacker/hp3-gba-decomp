#include "camera.h"

void GetRoomScrollBounds(IntPoint *pMin, IntPoint *pMax, s32 defaultMaxX, s32 defaultMaxY)
{
    CameraFocusSlot *pSlot = &g_aCameraFocusSlots[0];
    s32 any = pSlot->scrollMin.x | pSlot->scrollMin.y | pSlot->scrollMax.x | pSlot->scrollMax.y;

    if (any != 0)
    {
        *pMin = pSlot->scrollMin;
        *pMax = pSlot->scrollMax;
    }
    else
    {
        pMin->x = any;
        pMin->y = any;
        pMax->x = defaultMaxX;
        pMax->y = defaultMaxY;
    }
}
