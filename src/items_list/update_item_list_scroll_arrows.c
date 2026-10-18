#include "types.h"
#include "items_list.h"

void UpdateItemListScrollArrows(void)
{
    if (g_bItemListScroll > 0)
        g_ItemList.pUpArrow->dwFlags |= ActorFlagVisible;
    else
        g_ItemList.pUpArrow->dwFlags &= ~ActorFlagVisible;

    if (g_bItemListScroll + g_ItemList.bRowCount < g_ItemList.nItemCount)
        g_ItemList.pDownArrow->dwFlags |= ActorFlagVisible;
    else
        g_ItemList.pDownArrow->dwFlags &= ~ActorFlagVisible;
}
