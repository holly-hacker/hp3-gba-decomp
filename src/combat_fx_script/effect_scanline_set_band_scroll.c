#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "mode7.h"
#include "hw/io_regs.h"

void EffectScanlineSetBandScroll(u32 *pPayload0, u32 *pPayload1)
{
    REG_BGHOFS(1) = g_effectStaging.awBandScroll[*pPayload1];
    REG_BGVOFS(1) = 16;
    if (*pPayload1 == 0)
        StartFloorAffineHBlankDma(NULL, NULL);
}
