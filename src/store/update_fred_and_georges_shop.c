#include "types.h"
#include "game/game_modes.h"
#include "shop.h"

void UpdateFredAndGeorgesShop(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case ShopStateFadeOut:
        TickShopFadeOut();
        break;
    case ShopStateFadeIn:
        TickShopFadeIn();
        break;
    case ShopStateMainMenu:
        UpdateShopMainMenu();
        break;
    case ShopStateCategories:
        UpdateShopCategoryMenu();
        break;
    case ShopStateSellList:
        UpdateShopSellList();
        break;
    case ShopStateBuyList:
        UpdateShopBuyList();
        break;
    case ShopStateQuantity:
        UpdateShopQuantitySelect();
        break;
    case ShopStateMessage:
        UpdateShopMessage();
        break;
    }
}
