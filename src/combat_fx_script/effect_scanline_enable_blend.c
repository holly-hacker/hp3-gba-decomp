#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "screen_transitions.h"

void EffectScanlineEnableBlend(u32 *pPayload0, u32 *pPayload1)
{
    g_effectStaging.dwBgPrioritiesPending = 1;
    SetAlphaBlendTargets(g_effectStaging.wBlendFirstTargets, g_effectStaging.wBlendSecondTargets);
}
