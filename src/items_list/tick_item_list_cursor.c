#include "types.h"
#include "items_list.h"

void TickItemListCursor(Actor *pCursor)
{
    if (g_ItemList.dwCursorTargetSet)
        SetActorMoveTargetWithDuration(pCursor, g_ItemList.nCursorTargetX, g_ItemList.nCursorTargetY, 2);
    else
        SetActorMoveTargetWithDuration(pCursor, g_ItemList.nX - 18,
                                       g_ItemList.nY + g_bItemListCursorRow * ITEM_LIST_ROW_HEIGHT, 2);
}
