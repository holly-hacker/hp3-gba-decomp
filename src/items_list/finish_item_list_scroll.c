#include "types.h"
#include "items.h"
#include "items_list_inline.h"

// Drops the row that scrolled out and moves the incoming row into place;
// direction is 1 after scrolling up, -1 after scrolling down.
void FinishItemListScroll(s32 direction)
{
    s32 i;

    SetActorScaleStep(g_ItemList.apIcons[ITEM_LIST_INCOMING_SLOT], 8);
    g_ItemList.apIcons[ITEM_LIST_INCOMING_SLOT]->oam.objMode = 0;
    g_ItemList.apTextLine1[ITEM_LIST_INCOMING_SLOT]->oam.objMode = 0;
    g_ItemList.apTextLine2[ITEM_LIST_INCOMING_SLOT]->oam.objMode = 0;

    if (direction == 1)
    {
        FreeItemListRow(g_ItemList.bRowCount - 1);
        for (i = g_ItemList.bRowCount - 2; i >= 0; i--)
            MoveItemListRow(i + 1, i);
        MoveItemListRow(0, ITEM_LIST_INCOMING_SLOT);
    }
    else
    {
        FreeItemListRow(0);
        for (i = 0; i <= g_ItemList.bRowCount - 2; i++)
            MoveItemListRow(i, i + 1);
        MoveItemListRow(g_ItemList.bRowCount - 1, ITEM_LIST_INCOMING_SLOT);
    }

    g_ItemList.apIcons[ITEM_LIST_INCOMING_SLOT] = NULL;
    g_ItemList.apTextLine1[ITEM_LIST_INCOMING_SLOT] = NULL;
    g_ItemList.apTextLine2[ITEM_LIST_INCOMING_SLOT] = NULL;
    if (g_ItemList.pfnOnCursorMove)
        g_ItemList.pfnOnCursorMove(g_ItemList.adwItems[g_bItemListScroll + g_bItemListCursorRow]);
}
