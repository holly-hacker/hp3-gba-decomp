#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "hw/io_regs.h"

void FlushQueuedBattleDma(void)
{
    if (g_queuedBattleBgLoad.dwPending)
    {
        g_queuedBattleBgLoad.dwPending = 0;
        REG_DMA3.src = g_queuedBattleBgLoad.tiles.pSrc;
        REG_DMA3.dst = g_queuedBattleBgLoad.tiles.pDest;
        REG_DMA3.cnt = (g_queuedBattleBgLoad.tiles.dwSize >> 1) | 0x80000000;
        (void)REG_DMA3.cnt;
        REG_DMA3.src = g_pFightState->effectBgTilemap.awCells;
        REG_DMA3.dst = g_queuedBattleBgLoad.pScreenBase;
        REG_DMA3.cnt = (g_queuedBattleBgLoad.tiles.pTilemapBuffer->wHeight << 5) | 0x80000000;
        (void)REG_DMA3.cnt;
    }
}
