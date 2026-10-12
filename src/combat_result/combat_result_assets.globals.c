#include "types.h"
#include "actor.h"
#include "combat_result.h"
#include "gen/graphics/menus.h"
#include "gen/graphics/overworld.h"

// The coin next to the Sickles total of the drop phase.
const ActorAssetRecord g_CombatResultCoinAsset = { (void *)gUnnamed004Tiles, (void *)gUnnamed004Frames,
                                                   (const ObjPalette *)gUnnamed004Palette, 0 };

const ActorAssetRecord g_CombatResultUnusedItemsAsset = {
    (void *)gInGameMenuIconItemsTiles, (void *)gInGameMenuIconItemsFrames,
    (const ObjPalette *)gInGameMenuIconItemsPalette, 0
};

// Sparkle shown over a party member's portrait on a level-up.
const ActorAssetRecord g_CombatResultLevelUpSparkleAsset = {
    (void *)gLumosParticle001Tiles, (void *)gLumosParticle001Frames,
    (const ObjPalette *)gLumosParticle001Palette, 2
};
