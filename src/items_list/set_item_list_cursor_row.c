#include "types.h"
#include "items_list.h"

void SetItemListCursorRow(s32 row)
{
    if (g_bItemListCursorRow != row)
    {
        DrawItemListRowText(g_bItemListCursorRow, 0);
        g_bItemListCursorRow = row;
        DrawItemListRowText(g_bItemListCursorRow, 1);

        if (g_ItemList.pfnOnCursorMove)
            g_ItemList.pfnOnCursorMove(g_ItemList.adwItems[g_bItemListScroll + g_bItemListCursorRow]);
    }
}
