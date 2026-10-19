#include "types.h"
#include "combat_fx.h"
#include "interrupts.h"

// Builds BG graphic pBlob for bg in pTilemapBuffer (at most 32x32 cells,
// with palBank and tileOffset applied) and queues its tiles and tilemap for
// FlushQueuedBattleDma, first waiting out a load still pending. Returns
// pTilemapBuffer.
BgTilemapBuffer *QueueBattleBgLoad(u32 bg, const u8 *pBlob, u16 tileOffset, u16 palBank,
                                   BgTilemapBuffer *pTilemapBuffer)
{
    BgTileLoadInfo tiles;
    u16 *pDest;
    const u16 *pSrc;
    u32 w;
    u32 h;

    while (g_queuedBattleBgLoad.dwPending == 1)
        WaitForVBlankIntr();

    g_queuedBattleBgLoad.pTilemap = GetGraphicBlobTileLoad(bg, pBlob, tileOffset, &tiles);
    pTilemapBuffer->wWidth = g_queuedBattleBgLoad.pTilemap[0];
    pTilemapBuffer->wHeight = g_queuedBattleBgLoad.pTilemap[1];
    tiles.pTilemapBuffer = pTilemapBuffer;
    g_queuedBattleBgLoad.pScreenBase = g_BgState.aLayers[bg].pScreenBase;
    pSrc = g_queuedBattleBgLoad.pTilemap + 2;
    pDest = pTilemapBuffer->awCells;
    w = MAX(0, MIN(32, pTilemapBuffer->wWidth));
    h = MAX(0, MIN(32, pTilemapBuffer->wHeight));
    CopyTilemapRectOffset(pDest, pSrc, w, h, pTilemapBuffer->wWidth, palBank, tileOffset);
    g_queuedBattleBgLoad.tiles = tiles;
    g_queuedBattleBgLoad.dwPending = 1;
    return tiles.pTilemapBuffer;
}
