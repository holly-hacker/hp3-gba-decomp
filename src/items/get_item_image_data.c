#include "types.h"
#include "constants/items.h"
#include "game/items.h"
#include "game/rewards.h"
#include "gen/graphics/menus.h"
#include "items.h"

// Cards share the Chocolate Frogs icon; ITEM_REMOVE has an icon of its own.
void GetItemImageData(u32 item, const void **ppPalette, const void **ppTileData, const void **ppFrameData)
{
    if (item == ITEM_REMOVE)
    {
        *ppPalette = gItemRemovePalette;
        *ppTileData = gItemRemoveTiles;
        *ppFrameData = gItemRemoveFrames;
    }
    else if (item >= REWARD_ID_FIRST_CARD)
    {
        *ppPalette = gItemChocolateFrogsPalette;
        *ppTileData = gItemChocolateFrogsTiles;
        *ppFrameData = gItemChocolateFrogsFrames;
    }
    else
    {
        *ppPalette = g_pItemTable[item].pPalette;
        *ppTileData = g_pItemTable[item].pTileData;
        *ppFrameData = g_pItemTable[item].pFrameData;
    }
}
