#include "types.h"
#include "font.h"
#include "text.h"
#include "store.h"
#include "cursor.h"
#include "items.h"

void ShowShopQuantitySelect(void)
{
    const void *palette;
    const void *tiles;
    const void *frames;
    const u8 *text;

    g_FredAndGeorgesShop.dwItem = g_FredAndGeorgesShop.dwBuyItem != SHOP_NO_ITEM ? g_FredAndGeorgesShop.dwBuyItem : g_FredAndGeorgesShop.dwSellItem;
    g_FredAndGeorgesShop.nQuantity = 1;
    g_FredAndGeorgesShop.nUnitPrice = g_FredAndGeorgesShop.dwBuyItem == SHOP_NO_ITEM ? GetItemSellPrice(g_FredAndGeorgesShop.dwItem) : GetItemBuyPrice(g_FredAndGeorgesShop.dwItem);

    GetItemImageData(g_FredAndGeorgesShop.dwItem, &palette, &tiles, &frames);
    g_FredAndGeorgesShop.pItemIcon = SpawnActor(0xD, 0x20, 0x30, palette);
    g_FredAndGeorgesShop.pItemIcon->oam.priority = 2;
    g_FredAndGeorgesShop.itemIconGfx.pTileGfx = (void *)tiles;
    g_FredAndGeorgesShop.itemIconGfx.pFrameData = (void *)frames;
    SetActorAssetRecord(g_FredAndGeorgesShop.pItemIcon, &g_FredAndGeorgesShop.itemIconGfx);
    SetActorScaleStep(g_FredAndGeorgesShop.pItemIcon, 0);

    g_FredAndGeorgesShop.pLeftArrow = SpawnMenuCursorActor(2);
    SetActorAnimFrame(g_FredAndGeorgesShop.pLeftArrow, 3);
    SetMenuCursorPosition(g_FredAndGeorgesShop.pLeftArrow, 0x20, 0x68);
    g_FredAndGeorgesShop.pRightArrow = SpawnMenuCursorActor(2);
    SetActorAnimFrame(g_FredAndGeorgesShop.pRightArrow, 1);
    SetMenuCursorPosition(g_FredAndGeorgesShop.pRightArrow, 0xD0, 0x68);

    SelectTextFont(2, 0, -1);
    text = GetDialogText(GetRewardNameTextId(g_FredAndGeorgesShop.dwItem));
    DrawTextLines(1, 0x2F, 0x28, 0x90, 8, &text, 0);
    // "How many do you want to buy?" / "... sell?"
    text = GetDialogText(g_FredAndGeorgesShop.dwBuyItem == SHOP_NO_ITEM ? 0x540 : 0x53F);
    DrawTextLines(0x40, 0x18, 0x40, 0xC0, 0x10, &text, 0);
    DrawShopQuantity();
}
