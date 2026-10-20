#include "types.h"
#include "scroll.h"

void QueueBgStripRelease(s32 x, s32 y, u32 axis)
{
    g_aBgStripReleases[axis].x = x;
    g_aBgStripReleases[axis].y = y;
}
