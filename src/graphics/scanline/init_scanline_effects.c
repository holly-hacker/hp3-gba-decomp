#include "types.h"
#include "mem.h"
#include "interrupts.h"
#include "graphics/scanline_effects.h"

void InitScanlineEffects(void)
{
    g_ScanlineEffectState.dwActiveIndex = 0;
    ClearScanlineEffectStaging();
    QueueScanlineEffectTable(g_aDefaultScanlineEffects, ARRAY_COUNT(g_aDefaultScanlineEffects));
    CopyMemory(g_ScanlineEffectState.aEntries, g_ScanlineEffectState.aStaging,
               sizeof(g_ScanlineEffectState.aEntries));
    SetVCountCallback(ScanlineEffectVCountCallback);
    StartScanlineEffects();
}
