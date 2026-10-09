#include "types.h"
#include "overworld/room.h"

void GetCameraPosition(s32 *pPosition)
{
    pPosition[0] = g_CameraPosition_candidate.nX;
    pPosition[1] = g_CameraPosition_candidate.nY;
}
