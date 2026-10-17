#include "types.h"
#include "game/items.h"
#include "items.h"

// Writes the ids of the owned items that pass `filter` to pItems, after a
// leading ITEM_REMOVE row when withRemove is set, and returns the row count.
u32 BuildFilteredItemList(u32 filter, u32 *pItems, u32 withRemove)
{
    u32 item;
    u32 count;

    item = 0;
    count = 0;
    if (withRemove)
        pItems[count++] = ITEM_REMOVE;

    for (; item < ITEM_COUNT; item++)
    {
        if (g_ItemInventory.abQuantities[item] != 0)
        {
            u32 category = g_pItemTable[item].dwCategory;

            if (category == filter
                || (filter == ITEM_FILTER_NON_EQUIPMENT && category >= ItemCategoryPotion)
                || (filter == ITEM_FILTER_SELLABLE && g_pItemTable[item].nSellPrice != 0))
                pItems[count++] = item;
        }
    }

    return count;
}
