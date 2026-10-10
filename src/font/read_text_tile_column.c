#include "types.h"
#include "font.h"

// Copies the tiles mapped by tileCount tilemap entries, from pEntry down, into
// the column buffer, mirroring those whose entry has the horizontal flip bit.
void ReadTextTileColumn(u32 *pBuf, u32 tileCount, u16 *pEntry, u8 *pTiles)
{
    u32 *pSrc;
    u32 words;

    while (tileCount--)
    {
        pSrc = (u32 *)(pTiles + (*pEntry & 0x3FF) * gTextRenderState.tileSize);
        words = gTextRenderState.tileSize / 4;
        while (words--)
            *pBuf++ = *pSrc++;
        if (*pEntry & 0x400)
            FlipTileHorizontally((u8 *)pBuf - gTextRenderState.tileSize);
        pEntry += 32;
    }
}
