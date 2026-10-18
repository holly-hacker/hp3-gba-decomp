#include "types.h"
#include "background.h"
#include "hw/io_regs.h"

// Copies cols x rows cells into the 32-wide screen, adding palBank and tileOffset; pDest and pSrc
// are left one row past the block.
#define COPY_RECT(cols, rows)                                              \
    for (row = (rows); row > 0; row--)                                     \
    {                                                                      \
        for (col = (cols); col > 0; col--)                                 \
        {                                                                  \
            *pDest = *pSrc + (palBank << 12) + tileOffset;                 \
            pDest++;                                                       \
            pSrc++;                                                        \
        }                                                                  \
        pDest += 0x20 - (cols);                                            \
        pSrc += pTilemap[0] - (cols);                                      \
    }

// Text BGs (mode 0, or BG0/BG1) take halfword cells in 32x32-tile screen blocks; affine BGs take
// byte cells.
void CopyBgTilemapRect(u32 bg, const u16 *pTilemap, u16 tileOffset, u16 palBank, u32 srcX, u32 srcY, u32 dstX,
                       u32 dstY, u32 w, u32 h)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    const u16 *pSrc = pTilemap + 2;
    u16 *pDest = (u16 *)((u8 *)VRAM_BASE + pLayer->control.bits.bScreenBlock * 0x800);
    u32 cols;
    u32 rows;
    u32 stride;
    u8 *pBytes;
    const u8 *pByteSrc;
    u32 col;
    u32 row;

    if ((REG_DISPCNT & 7) == 0 || bg == 0 || bg == 1)
    {
        pSrc += srcY * pTilemap[0] + srcX;
        pDest += dstY * 32 + dstX;
        cols = (0x20 - dstX <= w) ? 0x20 - dstX : w;
        rows = (0x20 - dstY <= h) ? 0x20 - dstY : h;
        COPY_RECT(cols, rows);

        if (dstX + w > 0x20)
        {
            if ((pLayer->control.abBytes[1] & 0xC0) == 0x40 || (pLayer->control.abBytes[1] & 0xC0) == 0xC0)
            {
                pDest += (0x20 - rows) * 0x20 - dstX;
                pSrc += cols - rows * pTilemap[0];
                cols = (w - cols <= 0x20) ? w - cols : 0x20;
                COPY_RECT(cols, rows);
                pDest += dstX;
            }
        }

        if (dstY + h > 0x20)
        {
            if ((pLayer->control.abBytes[1] & 0xC0) == 0x80 || (pLayer->control.abBytes[1] & 0xC0) == 0xC0)
            {
                pSrc = pTilemap + 2 + (srcY + rows) * pTilemap[0] + srcX;
                cols = (0x20 - dstX <= w) ? 0x20 - dstX : w;
                rows = (h - rows <= 0x20) ? h - rows : 0x20;
                COPY_RECT(cols, rows);
            }
        }

        if (dstX + w > 0x20 && dstY + h > 0x20)
        {
            if ((pLayer->control.abBytes[1] & 0xC0) == 0xC0)
            {
                pDest += (0x20 - rows) * 0x20 - dstX;
                pSrc += cols - rows * pTilemap[0];
                cols = (w - cols <= 0x20) ? w - cols : 0x20;
                COPY_RECT(cols, rows);
            }
        }
    }
    else
    {
        stride = 0x10 << pLayer->control.bits.bSize;
        pBytes = (u8 *)pDest + stride * dstY + dstX;
        pByteSrc = (const u8 *)pSrc + pTilemap[0] * srcY + srcX;
        for (row = h; row != 0; row--)
        {
            pDest = (u16 *)((u32)pBytes & ~1);
            for (col = w; col != 0; col--)
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
