#include "types.h"
#include "items_list.h"

u32 OpenItemListFromIds(const u32 *pItems, s32 x, s32 y, u32 textMode, u32 maxRows)
{
    for (g_ItemList.nItemCount = 0; pItems[g_ItemList.nItemCount] != ITEM_COUNT; g_ItemList.nItemCount++)
        g_ItemList.adwItems[g_ItemList.nItemCount] = pItems[g_ItemList.nItemCount];

    InitItemList(x, y, textMode, maxRows, ITEM_LIST_NO_CHARACTER);
    return 1;
}
