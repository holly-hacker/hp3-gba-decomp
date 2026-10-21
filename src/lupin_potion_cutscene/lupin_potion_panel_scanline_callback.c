#include "lupin_potion_cutscene.h"
#include "background.h"
#include "modes.h"
#include "hw/io_regs.h"

// Line 120 (payload 1) brings BG2 to the front with the panel scrolled into view while
// the dialog runs; line 159 (payload 0) sends it back behind the scene.
void LupinPotionPanelScanlineCallback(u32 *pPayload0, u32 *pPayload1)
{
    BgLayer *pLayer = &g_BgState.aLayers[2];
    u16 control;

    while (!(REG_DISPSTAT & DISPSTAT_HBLANK))
        ;

    if (*pPayload0 == 1 && g_GameModeStackContext.dwModeState != 0)
    {
        pLayer->control.bits.bPriority = 0;
        g_BgState.aLayers[2].dwFlags |= BG_LAYER_COMMIT;
        g_bForcePendingBgWritesFlush = 1;
        REG_BGHOFS(2) = 0;
        REG_BGVOFS(2) = 70 - g_LupinPotionCutscene.nPanelOffset;
    }
    else
    {
        pLayer->control.bits.bPriority = 3;
        g_BgState.aLayers[2].dwFlags |= BG_LAYER_COMMIT;
        g_bForcePendingBgWritesFlush = 1;
    }
    control = pLayer->control.wRegister;
    REG_BGCNT(2) = control;
}
