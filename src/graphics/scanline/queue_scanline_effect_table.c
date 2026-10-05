#include "types.h"
#include "hw/mem.h"
#include "hw/vblank.h"
#include "graphics/scanline_effects.h"

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
