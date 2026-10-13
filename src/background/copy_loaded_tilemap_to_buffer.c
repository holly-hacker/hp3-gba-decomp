#include "types.h"
#include "background.h"

void CopyLoadedTilemapToBuffer(u32 bg)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    u32 w;
    u32 h;
    u32 bit;

    w = pLayer->pTilemap[0] <= 0x1F ? pLayer->pTilemap[0] : 0x20;
    h = pLayer->pTilemap[1] <= 0x1F ? pLayer->pTilemap[1] : 0x20;
    CopyTilemapRect(w, h, 0, 0, pLayer->pTilemap[0], pLayer->pTilemap + 2, 0, 0, 0x20, pLayer->pTilemapBuffer);
    bit = 2 << bg;
    g_BgState.dwFlags |= bit;
}
