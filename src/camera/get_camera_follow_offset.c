#include "camera.h"

void GetCameraFollowOffset(CameraFocusOffset *pOffset, u8 slot)
{
    *pOffset = g_aCameraFollowOffsets[slot];
}
