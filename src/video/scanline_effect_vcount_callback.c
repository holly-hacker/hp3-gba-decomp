#include "types.h"
#include "hw/io_regs.h"
#include "video.h"

// Runs the active entry's callback, advances to the next entry (wrapping at
// the null terminator) and sets the VCOUNT compare line to its line.
void ScanlineEffectVCountCallback(void)
{
    ScanlineEffectEntry *pEntry = &g_ScanlineEffectState.aEntries[g_ScanlineEffectState.dwActiveIndex];

    pEntry->pfnCallback(&pEntry->dwPayload0, &pEntry->dwPayload1);

    g_ScanlineEffectState.dwActiveIndex++;
    if (g_ScanlineEffectState.aEntries[g_ScanlineEffectState.dwActiveIndex].pfnCallback == NULL)
        g_ScanlineEffectState.dwActiveIndex = 0;

    REG_DISPSTAT &= 0xFF;
    REG_DISPSTAT |= g_ScanlineEffectState.aEntries[g_ScanlineEffectState.dwActiveIndex].wLine << 8;
}
