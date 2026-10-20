#include "types.h"
#include "background.h"
#include "combat_dispatch.h"
#include "gen/graphics/battle.h"

// Draws the battle menu's frame from the HUD panel tilemap: a 19-tile top edge and the two
// corner tiles beside it.
void DrawBattleMenuFrame(void)
{
    const u16 *tilemap;

    tilemap = GetGraphicBlobTilemap(1, gBattleHudPanel);
    CopyBgTilemapRect(0, tilemap, 1, 0, 4, 6, 11, 26, 19, 1);
    CopyBgTilemapRect(0, tilemap, 1, 0, 4, 7, 10, 26, 1, 1);
    CopyBgTilemapRect(0, tilemap, 1, 0, 5, 7, 29, 26, 1, 1);
}
