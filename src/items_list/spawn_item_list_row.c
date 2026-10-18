#include "types.h"
#include "font.h"
#include "text_actor.h"
#include "items.h"
#include "items_list.h"

// Spawns the icon and text of list row `row` (-1 or bRowCount for the row
// scrolling in, which goes in ITEM_LIST_INCOMING_SLOT).
void SpawnItemListRow(s32 row)
{
    s32 item;
    s32 slot;
    u32 scale;
    const void *pPalette;
    const void *pTileData;
    const void *pFrameData;
    const u8 *pText;
    Actor *pActor;

    item = row + g_bItemListScroll;
    slot = ITEM_LIST_INCOMING_SLOT;
    if (row >= 0 && row < g_ItemList.bRowCount)
        slot = row;
    scale = slot != ITEM_LIST_INCOMING_SLOT ? 8 : 0;

    GetItemImageData(g_ItemList.adwItems[item], &pPalette, &pTileData, &pFrameData);
    pActor = SpawnActor(slot, g_ItemList.nX, g_ItemList.nY + row * ITEM_LIST_ROW_HEIGHT, pPalette);
    pActor->oam.priority = 2;
    g_ItemList.abIconGfxSlot[slot] = AllocItemListIconGfx();
    g_ItemList.aIconGfx[g_ItemList.abIconGfxSlot[slot]].pTileGfx = (void *)pTileData;
    g_ItemList.aIconGfx[g_ItemList.abIconGfxSlot[slot]].pFrameData = (void *)pFrameData;
    SetActorAssetRecord(pActor, &g_ItemList.aIconGfx[g_ItemList.abIconGfxSlot[slot]]);
    SetActorScaleStep(pActor, scale);
    g_ItemList.apIcons[slot] = pActor;

    SelectTextFont(1, 7, 0);
    pText = g_abItemListPlaceholderText;
    g_ItemList.apTextLine1[slot] = SpawnUnslottedTextActor(&pText);
    g_ItemList.apTextLine1[slot]->oam.priority = 2;
    if (slot == ITEM_LIST_INCOMING_SLOT)
        g_ItemList.apTextLine1[ITEM_LIST_INCOMING_SLOT]->oam.objMode = 1;
    SetActorPosition(g_ItemList.apTextLine1[slot], g_ItemList.nX + 15, g_ItemList.nY + row * ITEM_LIST_ROW_HEIGHT - 8);

    pText = g_abItemListPlaceholderText;
    g_ItemList.apTextLine2[slot] = SpawnUnslottedTextActor(&pText);
    g_ItemList.apTextLine2[slot]->oam.priority = 2;
    if (slot == ITEM_LIST_INCOMING_SLOT)
        g_ItemList.apTextLine2[ITEM_LIST_INCOMING_SLOT]->oam.objMode = 1;
    SetActorPosition(g_ItemList.apTextLine2[slot], g_ItemList.nX + 15, g_ItemList.nY + row * ITEM_LIST_ROW_HEIGHT);

    DrawItemListRowText(row, slot == g_bItemListCursorRow || slot == ITEM_LIST_INCOMING_SLOT);
}
