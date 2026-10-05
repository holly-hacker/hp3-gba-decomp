#include "types.h"
#include "hw/vblank.h"
#include "graphics/scanline_effects.h"

void StartScanlineEffects(void)
{
    g_ScanlineEffectState.dwActiveIndex = 0;
    EnableVCountInterrupt(g_ScanlineEffectState.aEntries[g_ScanlineEffectState.dwActiveIndex].wLine);
}
