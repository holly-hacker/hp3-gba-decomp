#pragma once

#include "types.h"
#include "items_list.h"

// Item list logic that the ROM compiles inline.

// Moves an item list row's actors and icon graphics entry between slots.
static inline void MoveItemListRow(s32 to, s32 from)
{
    g_ItemList.apIcons[to] = g_ItemList.apIcons[from];
    g_ItemList.apTextLine1[to] = g_ItemList.apTextLine1[from];
    g_ItemList.apTextLine2[to] = g_ItemList.apTextLine2[from];
    g_ItemList.abIconGfxSlot[to] = g_ItemList.abIconGfxSlot[from];
}
