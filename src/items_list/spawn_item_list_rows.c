#include "types.h"
#include "items_list.h"

void SpawnItemListRows(void)
{
    u32 rowCount;
    s32 i;

    rowCount = g_ItemList.nItemCount > g_ItemList.dwMaxRows ? g_ItemList.dwMaxRows
                                                             : g_ItemList.nItemCount;
    g_ItemList.bRowCount = rowCount;

    for (i = 0; i < g_ItemList.bRowCount; i++)
        SpawnItemListRow(i);
}
