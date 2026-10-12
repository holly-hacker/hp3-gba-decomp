#include "camera.h"

void SetCameraFollowOffset(CameraFocusOffset offset, u8 slot)
{
    g_aCameraFollowOffsets[slot] = offset;
}
