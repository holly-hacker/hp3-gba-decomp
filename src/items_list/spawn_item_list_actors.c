#include "types.h"
#include "cursor.h"
#include "items_list.h"

void SpawnItemListActors(void)
{
    SpawnItemListRows();

    if (g_ItemList.pfnOnCursorMove)
        g_ItemList.pfnOnCursorMove(g_ItemList.adwItems[g_bItemListScroll + g_bItemListCursorRow]);

    SpawnItemListScrollArrows();
    UpdateItemListScrollArrows();

    g_ItemList.pCursor = SpawnMenuCursorActor(4);
    g_ItemList.pCursor->pfnTick = TickItemListCursor;
    g_ItemList.pCursor->oam.objMode = 1;
    g_ItemList.pCursor->oam.hFlip = 1;
    SetMenuCursorPosition(g_ItemList.pCursor, g_ItemList.nX - 18,
                          g_ItemList.nY + g_bItemListCursorRow * ITEM_LIST_ROW_HEIGHT);
}
