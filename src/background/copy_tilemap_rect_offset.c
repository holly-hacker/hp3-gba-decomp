#include "types.h"
#include "background.h"

void CopyTilemapRectOffset(u16 *pDest, const u16 *pSrc, u32 w, u32 h, u32 srcStride, u32 palBank, u32 tileOffset)
{
    u32 row;
    u32 col;

    for (row = h; row > 0; row--)
    {
        for (col = w; col > 0; col--)
        {
            *pDest = *pSrc + (palBank << 12) + tileOffset;
            pDest++;
            pSrc++;
        }

        pDest += 0x20 - w;
        pSrc += srcStride - w;
    }
}
