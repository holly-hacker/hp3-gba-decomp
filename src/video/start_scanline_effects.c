#include "interrupts.h"
#include "video.h"

void StartScanlineEffects(void)
{
    g_ScanlineEffectState.dwActiveIndex = 0;
    EnableVCountInterrupt(g_ScanlineEffectState.aEntries[g_ScanlineEffectState.dwActiveIndex].wLine);
}
