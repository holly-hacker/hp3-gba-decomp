#include "types.h"
#include "game/items.h"
#include "inventory.h"
#include "inventory_inline.h"

// Lists the owned non-equipment items with dwFlags bit 0 set (only potions
// carry it) and returns the count.
u32 BuildBattleItemList_candidate(u32 *pItems)
{
    u32 count = 0;
    u32 item = 0;

    for (item = 0; item < ITEM_COUNT; item++)
    {
        if (g_pItemTable[item].dwCategory >= ItemCategoryPotion
            && (g_pItemTable[item].dwFlags & 1)
            && GetItemQuantityInline(item) != 0)
            pItems[count++] = item;
    }

    return count;
}
