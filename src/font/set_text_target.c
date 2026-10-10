#include "types.h"
#include "font.h"

void SetTextTarget(u16 *pTilemap, u8 *pTiles, u32 is8bpp)
{
    gTextRenderState.pTilemap = pTilemap;
    gTextRenderState.pTilemapBase = pTilemap;
    gTextRenderState.pTiles = pTiles;
    gTextRenderState.tileSize = (is8bpp + 1) * 0x20;
    gTextRenderState.is8bpp = is8bpp;
}
