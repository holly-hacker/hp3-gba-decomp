#include "types.h"
#include "items_list.h"

void FreeItemListRows(void)
{
    s32 i;

    for (i = 0; i < g_ItemList.bRowCount; i++)
        FreeItemListRow(i);
}
