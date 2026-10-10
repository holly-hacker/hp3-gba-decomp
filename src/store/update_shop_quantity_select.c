#include "types.h"
#include "font.h"
#include "game/items.h"
#include "game/rewards.h"
#include "game/save.h"
#include "graphics/audio.h"
#include "input.h"
#include "menu/dialog.h"
#include "overworld/room_script.h"
#include "shop.h"
#include "shop_inline.h"

void UpdateShopQuantitySelect(void)
{
    s32 quantity;
    s32 i;

    if (g_wKeysPressed & (KeyRight | KeyUp))
    {
        if (g_wKeysPressed & KeyRight)
            quantity = g_FredAndGeorgesShop.nQuantity + 1;
        else
            quantity = g_FredAndGeorgesShop.nQuantity + 10;

        if (g_FredAndGeorgesShop.dwBuyItem == SHOP_NO_ITEM)
        {
            while (quantity > (s32)GetItemQuantity(g_FredAndGeorgesShop.dwItem))
                quantity--;
        }
        else
        {
            while (quantity * g_FredAndGeorgesShop.nUnitPrice > GetSickles()
                   || (GetItemQuantity(g_FredAndGeorgesShop.dwItem) + quantity > MAX_ITEM_QUANTITY
                       && g_FredAndGeorgesShop.dwItem != SHOP_ITEM_CHOCOLATE_FROGS))
                quantity--;
        }

        if (quantity == g_FredAndGeorgesShop.nQuantity)
        {
            PlaySoundById(3);
            return;
        }
        PlaySoundById(0);
        g_FredAndGeorgesShop.nQuantity = quantity;
        DrawShopQuantity();
    }
    else if (g_wKeysPressed & (KeyLeft | KeyDown))
    {
        if (g_wKeysPressed & KeyLeft)
            quantity = g_FredAndGeorgesShop.nQuantity - 1;
        else
            quantity = g_FredAndGeorgesShop.nQuantity - 10;

        if (quantity < 1)
            quantity = 1;

        if (quantity == g_FredAndGeorgesShop.nQuantity)
        {
            PlaySoundById(3);
            return;
        }
        PlaySoundById(0);
        g_FredAndGeorgesShop.nQuantity = quantity;
        DrawShopQuantity();
    }
    else if (g_wKeysPressed & KeyA)
    {
        PlaySoundById(1);
        if (g_FredAndGeorgesShop.dwBuyItem == SHOP_NO_ITEM)
        {
            ConsumeBattleItemSlot(g_FredAndGeorgesShop.dwItem, g_FredAndGeorgesShop.nQuantity);
            AddSickles(g_FredAndGeorgesShop.nQuantity * g_FredAndGeorgesShop.nUnitPrice);
        }
        else if (g_FredAndGeorgesShop.dwBuyItem == SHOP_ITEM_CHOCOLATE_FROGS)
        {
            AddSickles(-(g_FredAndGeorgesShop.nQuantity * g_FredAndGeorgesShop.nUnitPrice));
            DrawShopSickles();
            for (i = 0; i < g_FredAndGeorgesShop.nQuantity; i++)
                GrantRandomChocolateFrogCard();
            SetTextMacro1Number(g_FredAndGeorgesShop.nQuantity);
            g_FredAndGeorgesShop.dwMessageTextId = 0x546;  // "Congratulations, you receive @1 collector's cards ..."
            StartShopScreenTransition(ShopScreenMessage);
            return;
        }
        else
        {
            GrantReward(g_FredAndGeorgesShop.dwItem, g_FredAndGeorgesShop.nQuantity);
            AddSickles(-(g_FredAndGeorgesShop.nQuantity * g_FredAndGeorgesShop.nUnitPrice));
        }

        DrawShopSickles();
        if (g_FredAndGeorgesShop.dwBuyItem != SHOP_NO_ITEM)
        {
            StartShopScreenTransition(ShopScreenBuyList);
        }
        else
        {
            g_FredAndGeorgesShop.bSoldItem = 1;
            StartShopScreenTransition(ShopScreenSellList);
        }
    }
    else if (g_wKeysPressed & KeyB)
    {
        PlaySoundById(2);
        StartShopScreenTransition(g_FredAndGeorgesShop.dwBuyItem == SHOP_NO_ITEM ? ShopScreenSellList : ShopScreenBuyList);
    }
}
