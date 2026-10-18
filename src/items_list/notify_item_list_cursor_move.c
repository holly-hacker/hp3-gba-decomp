#include "types.h"
#include "items_list.h"

void NotifyItemListCursorMove(void)
{
    if (g_ItemList.pfnOnCursorMove)
        g_ItemList.pfnOnCursorMove(g_ItemList.adwItems[g_bItemListScroll + g_bItemListCursorRow]);
}
