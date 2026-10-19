#include "types.h"
#include "mem.h"
#include "video.h"

// Removes the staging entry on `line`, shifting the later entries down. The
// move reads one entry past the end of the table. Unused.
void RemoveScanlineEffectEntry(u16 line)
{
    u32 i = 0;
    u32 size;

    while (g_ScanlineEffectState.dwPending != 0)
        ;

    while (g_ScanlineEffectState.aStaging[i].wLine != line)
        i++;

    size = (SCANLINE_EFFECT_TABLE_SIZE - i) * sizeof(ScanlineEffectEntry);
    MoveMemory(&g_ScanlineEffectState.aStaging[i], &g_ScanlineEffectState.aStaging[i + 1], size);
    g_ScanlineEffectState.dwPending = 1;
}
