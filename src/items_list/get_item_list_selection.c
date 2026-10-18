#include "types.h"
#include "items_list.h"

u32 GetItemListSelection(void)
{
    return g_ItemList.adwItems[g_bItemListScroll + g_bItemListCursorRow];
}
