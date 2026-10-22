#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"

void EffectScanlineAdvanceScroll(u32 *pPayload0, u32 *pPayload1)
{
    g_effectStaging.awBandScroll[0] += 3;
    g_effectStaging.awBandScroll[1] += 2;
    g_effectStaging.awBandScroll[2] += 1;
    g_effectStaging.awBandScroll[3] = g_aEffectBgRecords_candidate[0].wScrollX;
}
