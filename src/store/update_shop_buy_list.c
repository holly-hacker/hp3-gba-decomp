#include "types.h"
#include "game/items.h"
#include "game/rewards.h"
#include "save.h"
#include "game_state.h"
#include "sound.h"
#include "input.h"
#include "pscreen_items.h"
#include "store.h"
#include "items.h"

void UpdateShopBuyList(void)
{
    if (g_FredAndGeorgesShop.dwHasListItems != 0)
    {
        TickItemList();
        if (g_wKeysPressed & KeyA)
        {
            if (GetItemBuyPrice(GetItemListSelection()) <= GetSickles() && GetItemQuantity(GetItemListSelection()) < MAX_ITEM_QUANTITY)
            {
                PlaySoundById(1);
                g_FredAndGeorgesShop.dwBuyItem = GetItemListSelection();
                g_FredAndGeorgesShop.dwSellItem = SHOP_NO_ITEM;
                StartShopScreenTransition(ShopScreenQuantity);
            }
            else
            {
                PlaySoundById(3);
            }
            return;
        }
    }

    if (g_wKeysPressed & KeyB)
    {
        PlaySoundById(2);
        SetItemListTranslucent();
        StartShopScreenTransition(ShopScreenCategories);
    }
}
