#include "types.h"
#include "video.h"

u32 IsScanlineEffectQueueIdle(void)
{
    u32 idle = 0;

    if (g_ScanlineEffectState.dwPending == 0)
        idle = 1;

    return idle;
}
