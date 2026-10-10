#include "types.h"
#include "font.h"
#include "hw/dma.h"

// Clears tilemap entries left..right of a row.
void ClearTilemapRow(s32 left, s32 row, s32 right)
{
    volatile u16 value;
    u16 *pDest;
    s32 size;

    if (left <= right)
    {
        pDest = &gTextRenderState.pTilemap[row * 32 + left];
        size = (right - left + 1) * 2;
        value = 0;
        REG_DMA3.src = (const void *)&value;
        REG_DMA3.dst = pDest;
        REG_DMA3.cnt = 0x81000000 | size / 2;
        (void)REG_DMA3.cnt;
    }
}
