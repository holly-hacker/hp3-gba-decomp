#include "types.h"
#include "background.h"

const u16 *LoadGraphicBlob(u32 bg, const u8 *pBlob, u16 tileOffset, u16 palBank, u32 x, u32 y)
{
    const u16 *pTilemap = LoadGraphicBlobTiles(bg, pBlob, tileOffset);

    if (pTilemap != NULL)
        WriteBgGraphicTilemap(bg, pTilemap, tileOffset, palBank, x, y);

    return pTilemap;
}
