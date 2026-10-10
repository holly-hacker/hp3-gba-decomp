#include "types.h"
#include "font.h"

// Copies tileCount tiles of the column buffer to consecutive tiles from
// tileIndex and points the tilemap entries from pEntry down at them. Without a
// background color the entries keep their palette.
void WriteTextTileColumn(u32 *pBuf, u32 tileCount, u16 *pEntry, u8 *pTiles, u32 tileIndex)
{
    u32 *pDest;
    u32 words;

    while (tileCount--)
    {
        pDest = (u32 *)(pTiles + tileIndex * gTextRenderState.tileSize);
        words = gTextRenderState.tileSize / 4;
        while (words--)
            *pDest++ = *pBuf++;
        if (gTextRenderState.is8bpp == 1)
            *pEntry = tileIndex;
        else if (gTextRenderState.bgColor == -1)
            *pEntry = (*pEntry & 0xF000) | tileIndex;
        else
            *pEntry = gTextRenderState.tilemapAttr | tileIndex;
        pEntry += 32;
        tileIndex++;
    }
}
