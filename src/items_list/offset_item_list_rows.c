#include "types.h"
#include "items.h"
#include "items_list.h"

void OffsetItemListRows(s32 dy)
{
    s32 i;

    for (i = 0; i < ITEM_LIST_SLOT_COUNT; i++)
    {
        if (i < g_ItemList.bRowCount || i == ITEM_LIST_INCOMING_SLOT)
        {
            OffsetActorPosition(g_ItemList.apIcons[i], 0, dy);
            OffsetActorPosition(g_ItemList.apTextLine1[i], 0, dy);
            OffsetActorPosition(g_ItemList.apTextLine2[i], 0, dy);
        }
    }

    SetActorScaleStep(g_ItemList.apIcons[ITEM_LIST_INCOMING_SLOT], g_ItemList.bScrollFrames);
    if (dy > 0)
        SetActorScaleStep(g_ItemList.apIcons[g_ItemList.bRowCount - 1], g_ItemList.bScrollFrames);
    else
        SetActorScaleStep(g_ItemList.apIcons[0], g_ItemList.bScrollFrames);
}
