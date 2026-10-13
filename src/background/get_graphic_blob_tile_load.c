#include "types.h"
#include "background.h"
#include "hw/io_regs.h"

const u16 *GetGraphicBlobTileLoad(u32 bg, const u8 *pBlob, u16 tileOffset, BgTileLoadInfo *pInfo)
{
    const u16 *pTilemap = NULL;
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    const u8 *pData = pBlob + 2;
    u32 paletteSize;
    u32 length;
    s32 cells;
    u8 *pDest;

    if (pBlob[0] & 1)
        paletteSize = 0x200;
    else
        paletteSize = (pBlob[0] & 2) ? 0x20 : 0;

    pData += paletteSize;

    if (pBlob[0] & 4)
    {
        length = *(u16 *)pData;
        pData += 2;
        pInfo->pDest = VRAM_BASE;
        pInfo->pSrc = pData;
        pInfo->dwSize = length;
    }

    if (pBlob[0] & 0x10)
    {
        if (pBlob[0] & 8)
        {
            pTilemap = (const u16 *)pData;
            cells = pTilemap[0] * pTilemap[1];
            if (cells & 1)
                cells++;
            if (pBlob[1] & 1)
                cells /= 2;
            pData = (const u8 *)pTilemap + (cells * 2 + 4);
        }

        pDest = (u8 *)VRAM_BASE + pLayer->control.bCharBlock * 0x4000;
        pInfo->pDest = pDest;
        if (!(pBlob[0] & 0x80))
            pInfo->pDest = pDest + tileOffset * 32;
        else
            pInfo->pDest = pDest + tileOffset * 64;

        length = *(u16 *)pData;
        pData += 2;
        pInfo->pSrc = pData;
        pInfo->dwSize = length;
    }

    return pTilemap;
}
