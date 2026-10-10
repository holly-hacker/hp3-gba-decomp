#include "types.h"
#include "font.h"

void RestoreTextTarget(void)
{
    gTextRenderState.pTilemap = gSavedTextTarget.pTilemap;
    gTextRenderState.pTilemapBase = gSavedTextTarget.pTilemapBase;
    gTextRenderState.pTiles = gSavedTextTarget.pTiles;
    gTextRenderState.tileSize = gSavedTextTarget.tileSize;
    gTextRenderState.is8bpp = gSavedTextTarget.is8bpp;
}
