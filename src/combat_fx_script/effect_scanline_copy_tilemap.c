#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "background.h"
#include "gen/graphics/battle.h"

void EffectScanlineCopyTilemap(u32 *pPayload0, u32 *pPayload1)
{
    CopyBgTilemapRect(1, GetGraphicBlobTilemap(1, gBattleHudPanel), 1, 0, 0, 0, 0, 19, 30, 6);
}
