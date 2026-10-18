#include "types.h"
#include "items.h"
#include "items_list.h"

u32 OpenFilteredItemList(u32 filter, s32 x, s32 y, u32 textMode, u32 withRemove, u32 maxRows,
                         s32 character)
{
    g_ItemList.nItemCount = BuildFilteredItemList(filter, g_ItemList.adwItems, withRemove);
    if (g_ItemList.nItemCount == 0)
        return 0;

    InitItemList(x, y, textMode, maxRows, character);
    g_ItemList.dwWithRemove = withRemove;
    return 1;
}
