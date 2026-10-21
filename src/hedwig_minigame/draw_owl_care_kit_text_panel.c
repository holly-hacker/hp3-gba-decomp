#include "types.h"
#include "background.h"
#include "hedwig_minigame.h"
#include "gen/graphics/menus.h"

// Replaces the menu on BG0 with a plain dialog box.
void DrawOwlCareKitTextPanel(void)
{
    FillBgTile(0, 0x28B, 0);
    FillBgTilemapWithTile(0, 0x28B);
    SetBgPriority(0, 0);
    g_BgState.aLayers[0].pTilemap = LoadGraphicBlobTiles(0, gDialogBackgrounds001, 0x156);
    LoadEmbeddedPalette(gDialogBackgrounds001, 15, 1);
    if (g_BgState.aLayers[0].pTilemap != NULL)
        CopyBgTilemapRect(0, g_BgState.aLayers[0].pTilemap, 0x156, 15, 0, 0, 3, 6, 24, 8);
}
