#include "types.h"
#include "cursor.h"
#include "items_list.h"

void SpawnItemListScrollArrows(void)
{
    g_ItemList.pUpArrow = SpawnMenuCursorActor(6);
    SetMenuCursorPosition(g_ItemList.pUpArrow, g_ItemList.nX - 18, g_ItemList.nY - 16);
    g_ItemList.pDownArrow = SpawnMenuCursorActor(7);
    SetMenuCursorPosition(g_ItemList.pDownArrow, g_ItemList.nX - 18,
                          g_ItemList.nY + g_ItemList.bRowCount * ITEM_LIST_ROW_HEIGHT - 8);
}
