#include "types.h"
#include "background.h"
#include "hw/io_regs.h"

// Writes a loaded tilemap to the BG screen at (x, y), adding palBank and tileOffset. Text BGs (mode 0,
// or BG0/BG1) are clipped to the layer and split across its 32x32-tile screen blocks; affine BGs take
// byte cells and are not clipped.
void WriteBgGraphicTilemap(u32 bg, const u16 *pTilemap, u16 tileOffset, u16 palBank, s32 x, s32 y)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    const u16 *pSrc = pTilemap + 2;
    u16 *pDest = pLayer->pScreenBase;
    u32 cols;
    u32 rows;
    u32 stride;
    u8 *pBytes;
    const u8 *pByteSrc;
    u32 col;
    u32 row;

    if ((REG_DISPCNT & 7) == 0 || bg < 2)
    {
        // Top-left screen block. A count of 0 means the tilemap starts in the next block over.
        pDest += y * 32 + x;
        cols = MAX(MIN(32 - x, pTilemap[0]), 0);
        rows = MAX(MIN(32 - y, pTilemap[1]), 0);
        CopyTilemapRectOffset(pDest, pSrc, cols, rows, pTilemap[0], palBank, tileOffset);

        pDest = pLayer->pScreenBase + 0x400;
        if ((pLayer->control.abBytes[1] & 0xC0) == 0x40 || (pLayer->control.abBytes[1] & 0xC0) == 0xC0)
        {
            // Top-right
            pDest += y * 32 + ((cols == 0) ? x - 32 : 0);
            pSrc = pTilemap + 2 + cols;
            cols = MIN((cols == 0) ? 64 - x : 32, pTilemap[0] - cols);
            CopyTilemapRectOffset(pDest, pSrc, cols, rows, pTilemap[0], palBank, tileOffset);
            pDest = pLayer->pScreenBase + 0x800;
        }

        if ((pLayer->control.abBytes[1] & 0xC0) == 0x80 || (pLayer->control.abBytes[1] & 0xC0) == 0xC0)
        {
            // Bottom-left
            pDest += ((rows == 0) ? (y - 32) * 32 : 0) + x;
            pSrc = pTilemap + 2 + rows * pTilemap[0];
            cols = MAX(MIN(32 - x, pTilemap[0]), 0);
            rows = MIN((rows == 0) ? 64 - y : 32, pTilemap[1] - rows);
            CopyTilemapRectOffset(pDest, pSrc, cols, rows, pTilemap[0], palBank, tileOffset);
            pDest = pLayer->pScreenBase + 0xC00;

            if ((pLayer->control.abBytes[1] & 0xC0) == 0xC0)
            {
                // Bottom-right
                rows = MAX(MIN(32 - y, pTilemap[1]), 0);
                pDest += ((rows == 0) ? (y - 32) * 32 : 0) + ((cols == 0) ? x - 32 : 0);
                pSrc = pTilemap + 2 + rows * pTilemap[0] + cols;
                cols = MIN((cols == 0) ? 64 - x : 32, pTilemap[0] - cols);
                rows = MIN((rows == 0) ? 64 - y : 32, pTilemap[1] - rows);
                CopyTilemapRectOffset(pDest, pSrc, cols, rows, pTilemap[0], palBank, tileOffset);
            }
        }
    }
    else
    {
        stride = 0x10 << pLayer->control.bits.bSize;
        pBytes = (u8 *)pDest + stride * y + x;
        pByteSrc = (const u8 *)pSrc;
        for (row = pTilemap[1]; row != 0; row--)
        {
            pDest = (u16 *)((u32)pBytes & ~1);
            for (col = pTilemap[0]; col != 0; col--)
            {
                // BUG: tileOffset lands on the preserved low byte; it should be added before the shift.
                if ((u32)pBytes & 1)
                    *pDest = *(u8 *)pDest | ((*pByteSrc << 8) + tileOffset);
                else if (col == 1)
                    *pDest = (*pDest & 0xFF00) | (*pByteSrc + tileOffset);
                else
                {
                    *pDest = (*pByteSrc + tileOffset) | ((pByteSrc[1] + tileOffset) << 8);
                    pBytes++;
                    pByteSrc++;
                    col--;
                }
                pDest++;
                pBytes++;
                pByteSrc++;
            }
            pBytes += stride - pTilemap[0];
        }
    }
}
