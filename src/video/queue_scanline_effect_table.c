#include "types.h"
#include "mem.h"
#include "interrupts.h"
#include "video.h"

// Waits until the previously queued table has been committed, then stages
// `count` entries for CommitScanlineEffects.
void QueueScanlineEffectTable(const void *pEntries, u32 count)
{
    while (g_ScanlineEffectState.dwPending != 0)
        WaitForVBlankIntr();

    ClearScanlineEffectStaging();
    CopyMemory(g_ScanlineEffectState.aStaging, pEntries, count * sizeof(ScanlineEffectEntry));
    g_ScanlineEffectState.dwPending = 1;
}
