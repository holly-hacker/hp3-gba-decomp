#include "types.h"
#include "mem.h"
#include "video.h"

void CommitScanlineEffects(void)
{
    if (g_ScanlineEffectState.dwPending != 0)
    {
        CopyMemory(g_ScanlineEffectState.aEntries, g_ScanlineEffectState.aStaging,
                   sizeof(g_ScanlineEffectState.aEntries));
        g_ScanlineEffectState.dwPending = 0;
        g_ScanlineEffectState.dwActiveIndex = 0;
    }
}
