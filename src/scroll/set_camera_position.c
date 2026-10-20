#include "types.h"
#include "scroll.h"

void SetCameraPosition(const s32 *pPosition)
{
    g_CameraPosition.nX = pPosition[0];
    g_CameraPosition.nY = pPosition[1];
}
