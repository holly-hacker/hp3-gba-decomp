#include "types.h"
#include "screen_transitions.h"
#include "items_list.h"

void ScrollItemListUp(s32 rows)
{
    s32 prevScroll;
    s32 scroll;

    scroll = g_bItemListScroll;
    prevScroll = scroll;
    scroll -= rows;
    if (scroll < 0)
        scroll = 0;

    if (prevScroll != scroll)
    {
        SetAlphaBlendTargets(0, 2);
        DrawItemListRowText(g_bItemListCursorRow, 0);
        SpawnItemListRow(-1);
        g_bItemListScroll = scroll;
        g_ItemList.apTextLine1[g_ItemList.bRowCount - 1]->oam.objMode = 1;
        g_ItemList.apTextLine2[g_ItemList.bRowCount - 1]->oam.objMode = 1;
        if (g_ItemList.pfnOnClear)
            g_ItemList.pfnOnClear();
        g_ItemList.dwScrolledUp = 1;
        g_ItemList.bScrollFrames = 4;
        g_ItemList.wBlendCoeffA = 2;
        g_ItemList.wBlendCoeffB = 12;
        g_ItemList.dwState = ItemListScrollingUp;
        UpdateItemListScrollArrows();
    }
}
