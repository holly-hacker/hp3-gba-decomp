#include "types.h"
#include "font.h"

void SaveTextTarget(void)
{
    gSavedTextTarget.pTilemap = gTextRenderState.pTilemap;
    gSavedTextTarget.pTilemapBase = gTextRenderState.pTilemapBase;
    gSavedTextTarget.pTiles = gTextRenderState.pTiles;
    gSavedTextTarget.tileSize = gTextRenderState.tileSize;
    gSavedTextTarget.is8bpp = gTextRenderState.is8bpp;
}
