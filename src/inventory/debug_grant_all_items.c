#include "types.h"
#include "game/rewards.h"
#include "game/save.h"
#include "inventory.h"

// Unreferenced: adds `count` of every real item, three of every card, and
// sets every monster's Folio Bruti level to 4.
void DebugGrantAllItems(u32 count)
{
    s32 i;

    for (i = 0; i < SIMPLE_ITEMS_END; i++)
        g_ItemInventory.abQuantities[i] += count;

    for (i = REWARD_ID_FIRST_CARD; i < REWARD_ID_GOLD; i++)
        GrantRewardInline(i, 3);

    for (i = 0; i < ARRAY_COUNT(g_saveStateBlock.abMonsterDocLevel); i++)
        g_saveStateBlock.abMonsterDocLevel[i] = 4;
}
