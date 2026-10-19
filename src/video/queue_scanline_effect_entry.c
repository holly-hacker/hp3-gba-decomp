#include "types.h"
#include "video.h"

void QueueScanlineEffectEntry(u32 index, u16 line, u16 param,
                              void (*pfnCallback)(u32 *pPayload0, u32 *pPayload1))
{
    while (g_ScanlineEffectState.dwPending != 0)
        ;

    g_ScanlineEffectState.aStaging[index].wLine = line;
    g_ScanlineEffectState.aStaging[index].wParam = param;
    g_ScanlineEffectState.aStaging[index].pfnCallback = pfnCallback;
    g_ScanlineEffectState.dwPending = 1;
}
