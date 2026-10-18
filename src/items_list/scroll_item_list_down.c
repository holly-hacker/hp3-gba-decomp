#include "types.h"
#include "screen_transitions.h"
#include "items_list.h"

void ScrollItemListDown(u32 rows)
{
    s32 prevScroll;
    u32 scroll;

    scroll = g_bItemListScroll;
    prevScroll = scroll;
    scroll += rows;
    if (scroll + g_ItemList.bRowCount > g_ItemList.nItemCount)
        scroll = g_ItemList.nItemCount - g_ItemList.bRowCount;

    if (prevScroll != scroll)
    {
        SetAlphaBlendTargets(0, 2);
        DrawItemListRowText(g_bItemListCursorRow, 0);
        SpawnItemListRow(g_ItemList.bRowCount);
        g_bItemListScroll = scroll;
        g_ItemList.apTextLine1[0]->oam.objMode = 1;
        g_ItemList.apTextLine2[0]->oam.objMode = 1;
        if (g_ItemList.pfnOnClear)
            g_ItemList.pfnOnClear();
        g_ItemList.dwScrolledDown = 1;
        g_ItemList.bScrollFrames = 4;
        g_ItemList.wBlendCoeffA = 12;
        g_ItemList.wBlendCoeffB = 2;
        g_ItemList.dwState = ItemListScrollingDown;
        UpdateItemListScrollArrows();
    }
}
