#include "types.h"
#include "game/items.h"
#include "pscreen_items.h"
#include "gen/graphics/overworld.h"

const ListMenuEntry g_aItemsSectionEntries[3] = {
    { ItemsItemSelect, 0x586, 0 },  // "All"
    { ItemsItemSelect, 0x587, 0 },  // "Potions"
    { ItemsItemSelect, 0x589, 0 },  // "Miscellaneous"
};

const u32 g_aItemsSectionFilters[3] = { 0xA, ItemCategoryPotion, ItemCategoryMisc };

const ActorAssetRecord g_aItemsSectionRowActors[3] = {
    { (void *)gItemsSectionIconAllTiles, (void *)gItemsSectionIconAllFrames, (const ObjPalette *)gItemsSectionIconAllPalette, 0 },
    { (void *)gItemsSectionIconPotionsTiles, (void *)gItemsSectionIconPotionsFrames, (const ObjPalette *)gItemsSectionIconPotionsPalette, 0 },
    { (void *)gItemsSectionIconMiscTiles, (void *)gItemsSectionIconMiscFrames, (const ObjPalette *)gItemsSectionIconMiscPalette, 0 },
};

const ListMenuDefinition g_ItemsSectionMenuDefinition = {
    0x531,  // title: "Items"
    ARRAY_COUNT(g_aItemsSectionEntries),
    4,
    { 72, 26 },
    { 0, 16 },
    g_aItemsSectionEntries,
    ARRAY_COUNT(g_aItemsSectionRowActors),
    { -32, 0 },
    g_aItemsSectionRowActors,
    { -48, 8 },
};
