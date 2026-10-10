#include "types.h"
#include "graphics/audio.h"
#include "hw/input.h"
#include "menu/items_menu.h"
#include "shop.h"

void UpdateShopSellList(void)
{
    if (g_FredAndGeorgesShop.dwHasListItems != 0)
    {
        TickItemList();
        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            g_FredAndGeorgesShop.dwSellItem = GetItemListSelection();
            g_FredAndGeorgesShop.dwBuyItem = SHOP_NO_ITEM;
            StartShopScreenTransition(ShopScreenQuantity);
            return;
        }
    }

    if (g_wKeysPressed & KeyB)
    {
        PlaySoundById(2);
        SetItemListTranslucent();
        g_FredAndGeorgesShop.bCursor = 1;
        StartShopScreenTransition(ShopScreenMainMenu);
    }
}
