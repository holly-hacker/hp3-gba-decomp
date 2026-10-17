#include "types.h"
#include "modes.h"
#include "store.h"

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
