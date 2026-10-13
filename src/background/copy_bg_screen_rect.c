#include "types.h"
#include "background.h"

void CopyBgScreenRect(u32 bg, s32 w, s32 h, u32 srcX, u32 srcY, u32 dstX, u32 dstY)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    u16 *pSrc = pLayer->pScreenBaseAlt + srcY * 32 + srcX;
    u16 *pDest = pLayer->pScreenBaseAlt + dstY * 32 + dstX;
    s32 row;
    s32 col;

    for (row = h; row > 0; row--)
    {
        for (col = w; col > 0; col--)
            *pDest++ = *pSrc++;

        pSrc += 0x20 - w;
        pDest += 0x20 - w;
    }
}
