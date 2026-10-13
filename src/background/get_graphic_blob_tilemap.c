#include "types.h"
#include "background.h"

const u16 *GetGraphicBlobTilemap(u32 unused, const u8 *pBlob)
{
    const u16 *pTilemap = NULL;
    const u8 *pData = pBlob + 2;
    u32 paletteSize;

    if (pBlob[0] & 1)
        paletteSize = 0x200;
    else
        paletteSize = (pBlob[0] & 2) ? 0x20 : 0;

    pData += paletteSize;
    if (pBlob[0] & 0x10)
    {
        if (pBlob[0] & 8)
            pTilemap = (const u16 *)pData;
    }

    return pTilemap;
}
