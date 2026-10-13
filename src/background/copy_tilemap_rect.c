#include "types.h"
#include "background.h"

void CopyTilemapRect(s32 w, s32 h, u32 srcX, u32 srcY, u32 srcStride, const u16 *pSrc, u32 dstX, u32 dstY,
                  u32 dstStride, u16 *pDest)
{
    s32 row;
    s32 col;

    pSrc += srcY * srcStride + srcX;
    pDest += dstY * dstStride + dstX;
    for (row = h; row > 0; row--)
    {
        for (col = w; col > 0; col--)
            *pDest++ = *pSrc++;

        pSrc += srcStride - w;
        pDest += dstStride - w;
    }
}
