#include "types.h"
#include "combat_fx_script.h"
#include "mode7.h"

void EffectScanlineStopHBlankDma(u32 *pPayload0, u32 *pPayload1)
{
    StartFloorAffineHBlankDma(NULL, NULL);
}
