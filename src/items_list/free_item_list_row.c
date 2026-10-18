#include "types.h"
#include "items_list.h"

void FreeItemListRow(s32 slot)
{
    FreeActor(g_ItemList.apIcons[slot]);
    g_ItemList.apIcons[slot] = NULL;
    g_ItemList.apTextLine1[slot]->dwFlags &= ~ActorFlagSkipSpriteFrameUpdate;
    FreeActor(g_ItemList.apTextLine1[slot]);
    g_ItemList.apTextLine1[slot] = NULL;
    g_ItemList.apTextLine2[slot]->dwFlags &= ~ActorFlagSkipSpriteFrameUpdate;
    FreeActor(g_ItemList.apTextLine2[slot]);
    g_ItemList.apTextLine2[slot] = NULL;
    FreeItemListIconGfx(g_ItemList.abIconGfxSlot[slot]);
}
