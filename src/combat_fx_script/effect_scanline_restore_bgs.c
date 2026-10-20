#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "background.h"
#include "mode7.h"
#include "hw/io_regs.h"

void EffectScanlineRestoreBgs(u32 *pPayload0, u32 *pPayload1)
{
    StartFloorAffineHBlankDma(NULL, NULL);
    REG_BGVOFS(1) = 0;
    SetBgPriority(0, g_effectStaging.bBg0Priority);
    SetBgPriority(1, g_effectStaging.bBg1Priority);
    REG_WINOUT &= ~2;
}
