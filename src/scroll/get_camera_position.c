#include "types.h"
#include "scroll.h"

void GetCameraPosition(s32 *pPosition)
{
    pPosition[0] = g_CameraPosition.nX;
    pPosition[1] = g_CameraPosition.nY;
}
