#include "types.h"
#include "background.h"
#include "graphics/graphics.h"
#include "hw/dma.h"
#include "hw/io_regs.h"

const u16 *LoadGraphicBlobTiles(u32 bg, const u8 *pBlob, u16 tileOffset)
{
    const u16 *pTilemap = NULL;
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    const u8 *pData = pBlob + 2;
    u32 paletteSize;
    s32 length;
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
        REG_DMA3.src = pData;
        REG_DMA3.dst = VRAM_BASE;
        REG_DMA3.cnt = (length / 2) | 0x80000000;
        (void)REG_DMA3.cnt;
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

        pDest = (u8 *)VRAM_BASE + pLayer->control.bits.bCharBlock * 0x4000;
        if (!(pBlob[0] & 0x80))
            pDest += tileOffset * 32;
        else
            pDest += tileOffset * 64;

        length = *(u16 *)pData;
        pData += 2;
        UnpackTileData((const TileDataHeader *)pBlob, pData, length, pDest);
    }

    return pTilemap;
}
