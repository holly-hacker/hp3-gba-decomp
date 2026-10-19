#include "types.h"
#include "background.h"
#include "combat.h"
#include "combat_effects_hblank.h"
#include "video.h"
#include "hw/io_regs.h"

void EndBattleWallScanline(u32 *pPayload0, u32 *pPayload1)
{
    SetBgPriority(1, 0);
    REG_BGVOFS(1) = 0;

    if (g_pFightState->bWallEndLine != GetScanlineEffectLine(1))
        QueueScanlineEffectEntry(1, g_pFightState->bWallEndLine, 0, EndBattleWallScanline);
}
