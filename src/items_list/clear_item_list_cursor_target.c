#include "types.h"
#include "items_list.h"

void ClearItemListCursorTarget(void)
{
    g_ItemList.dwCursorTargetSet = 0;
    DrawItemListRowText(g_bItemListCursorRow, 1);
    NotifyItemListCursorMove();
}
