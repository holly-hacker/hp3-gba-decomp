#include "types.h"
#include "graphics/scanline_effects.h"

void ClearScanlineEffectStaging(void)
{
    s32 i;

    for (i = 0; i < SCANLINE_EFFECT_TABLE_SIZE; i++)
    {
        g_ScanlineEffectState.aStaging[i].wLine |= 0xFFFF;
        g_ScanlineEffectState.aStaging[i].wParam = 0;
        g_ScanlineEffectState.aStaging[i].dwPayload0 = 0;
        g_ScanlineEffectState.aStaging[i].dwPayload1 = 0;
        g_ScanlineEffectState.aStaging[i].pfnCallback = NULL;
    }
}
