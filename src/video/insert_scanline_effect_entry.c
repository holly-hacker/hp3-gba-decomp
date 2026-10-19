#include "types.h"
#include "mem.h"
#include "video.h"

// Inserts a staging entry before the first one with a line at or after
// `line`, dropping the last entry. Unused.
void InsertScanlineEffectEntry(u16 line, u16 param,
                               void (*pfnCallback)(u32 *pPayload0, u32 *pPayload1))
{
    u32 i = 0;
    u32 size;

    while (g_ScanlineEffectState.dwPending != 0)
        ;

    while (g_ScanlineEffectState.aStaging[i].wLine < line)
        i++;

    size = (SCANLINE_EFFECT_TABLE_SIZE - 1 - i) * sizeof(ScanlineEffectEntry);
    MoveMemory(&g_ScanlineEffectState.aStaging[i + 1], &g_ScanlineEffectState.aStaging[i], size);
    g_ScanlineEffectState.aStaging[i].wLine = line;
    g_ScanlineEffectState.aStaging[i].wParam = param;
    g_ScanlineEffectState.aStaging[i].pfnCallback = pfnCallback;
    g_ScanlineEffectState.dwPending = 1;
}
