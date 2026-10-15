#include "types.h"
#include "mode7.h"

void SetFloorCameraPositionAndHeading(u16 x, u16 y, u8 heading)
{
    g_FloorEffect.dwCameraX = x << 8;
    g_FloorEffect.dwCameraY = y << 8;
    g_FloorEffect.bHeading = heading;
}
