#include "types.h"
#include "background.h"
#include "combat_effects_hblank.h"
#include "gen/graphics/battle.h"

void RestoreBattleHudPanelTilemap(u32 *pPayload0, u32 *pPayload1)
{
    CopyBgTilemapRect(1, GetGraphicBlobTilemap(1, gBattleHudPanel), 1, 0, 0, 0, 0, 19, 30, 6);
}
