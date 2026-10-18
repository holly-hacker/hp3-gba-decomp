#include "types.h"
#include "items_list.h"

void SetItemListCursorTarget(s32 x, s32 y)
{
    g_ItemList.dwCursorTargetSet = 1;
    g_ItemList.nCursorTargetX = x;
    g_ItemList.nCursorTargetY = y;
    DrawItemListRowText(g_bItemListCursorRow, 0);
}
