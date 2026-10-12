#include "camera.h"

void SetRoomScrollBounds(u16 minX, u16 minY, u16 maxX, u16 maxY)
{
    CameraFocusSlot *pSlot = &g_aCameraFocusSlots[0];

    pSlot->scrollMin.x = minX;
    pSlot->scrollMin.y = minY;
    pSlot->scrollMax.x = maxX;
    pSlot->scrollMax.y = maxY;
}
