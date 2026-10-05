#include "types.h"
#include "overworld/room.h"

void SetCameraPosition(const s32 *pPosition)
{
    g_CameraPosition_candidate.nX = pPosition[0];
    g_CameraPosition_candidate.nY = pPosition[1];
}
