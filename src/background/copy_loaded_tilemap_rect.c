#include "types.h"
#include "background.h"

void CopyLoadedTilemapRect(u32 bg, s32 w, s32 h, u32 srcX, u32 srcY, u32 dstX, u32 dstY)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    u32 srcStride = pLayer->pTilemap[0];
    const u16 *pSrc = pLayer->pTilemap + 2;
    u16 *pDest = pLayer->pScreenBaseAlt;
    s32 row;
    s32 col;
    s32 srcSkip;
    s32 dstSkip;

    pSrc += srcY * srcStride + srcX;
    pDest += dstY * 32 + dstX;
    for (row = h; row > 0; row--)
    {
        srcSkip = srcStride - w;
        dstSkip = 0x20 - w;
        for (col = w; col > 0; col--)
            *pDest++ = *pSrc++;
        pSrc += srcSkip;
        pDest += dstSkip;
    }
}
