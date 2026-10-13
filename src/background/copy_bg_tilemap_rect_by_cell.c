#include "types.h"
#include "background.h"
#include "hw/io_regs.h"

// Address of tile (x, y) in a screen made of 32x32-tile blocks; size is BgControl.bSize.
static inline u16 *GetScreenCell(u16 *pScreen, u32 size, u32 x, u32 y)
{
    switch (size)
    {
    case 0:
        break;
    case 1:
        if (x > 0x1F)
        {
            pScreen += 0x400;
            x -= 0x20;
        }
        break;
    case 2:
        if (y > 0x1F)
        {
            pScreen += 0x400;
            y -= 0x20;
        }
    case 3:
        if (x > 0x1F)
        {
            pScreen += 0x400;
            x -= 0x20;
        }
        if (y > 0x1F)
        {
            pScreen += 0x800;
            y -= 0x20;
        }
        break;
    }

    pScreen += y * 32 + x;
    return pScreen;
}

// Copies a rect of a loaded tilemap to the BG screen at (dstX, dstY), adding palBank and tileOffset.
void CopyBgTilemapRectByCell(u32 bg, const u16 *pTilemap, u16 tileOffset, u16 palBank, u32 srcX, u32 srcY,
                             u32 dstX, u32 dstY, u32 w, u32 h)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    u32 size = pLayer->control.bits.bSize;
    u16 *pScreen = (u16 *)((u8 *)VRAM_BASE + pLayer->control.bits.bScreenBlock * 0x800);
    const u16 *pSrc = pTilemap + 2 + srcY * pTilemap[0] + srcX;
    u32 xEnd;
    u32 yEnd;
    u32 x;
    u32 y;
    u32 skip;

    w = (pTilemap[0] - srcX <= w) ? pTilemap[0] - srcX : w;
    h = (pTilemap[1] - srcY <= h) ? pTilemap[1] - srcY : h;
    xEnd = dstX + w;
    yEnd = dstY + h;
    xEnd = xEnd < ((size == 3 || size == 1) ? 0x40 : 0x20) ? xEnd : ((size == 3 || size == 1) ? 0x40 : 0x20);
    yEnd = yEnd < ((size == 2 || size == 3) ? 0x40 : 0x20) ? yEnd : ((size == 2 || size == 3) ? 0x40 : 0x20);

    skip = pTilemap[0] - w;
    for (y = dstY; y < yEnd; y++)
    {
        for (x = dstX; x < xEnd; x++)
        {
            *GetScreenCell(pScreen, size, x, y) = *pSrc + (palBank << 12) + tileOffset;
            pSrc++;
        }

        pSrc += skip;
    }
}
