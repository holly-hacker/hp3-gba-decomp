#include "types.h"
#include "items_list.h"

void SetItemListTranslucent(void)
{
    s32 i;

    for (i = 0; i < g_ItemList.bRowCount; i++)
    {
        g_ItemList.apIcons[i]->oam.objMode = 1;
        g_ItemList.apTextLine1[i]->oam.objMode = 1;
        g_ItemList.apTextLine2[i]->oam.objMode = 1;
    }

    g_ItemList.pCursor->oam.objMode = 1;
}
