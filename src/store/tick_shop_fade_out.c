#include "types.h"
#include "game/game_modes.h"
#include "graphics/display.h"
#include "shop.h"
#include "shop_inline.h"

void TickShopFadeOut(void)
{
    g_GameModeStackContext.dwModeSubState -= 2;
    SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState, 0x10 - g_GameModeStackContext.dwModeSubState);
    if (g_GameModeStackContext.dwModeSubState != 0)
        return;

    switch (g_FredAndGeorgesShop.dwPrevState)
    {
    case ShopStateMainMenu:
        ExitShopMainMenu();
        break;
    case ShopStateCategories:
        ExitShopCategoryMenu();
        break;
    case ShopStateSellList:
        ExitShopSellList();
        break;
    case ShopStateBuyList:
        ExitShopBuyList();
        break;
    case ShopStateQuantity:
        ExitShopQuantitySelect();
        break;
    case ShopStateMessage:
        ExitShopMessage();
        break;
    }

    switch (g_FredAndGeorgesShop.dwNextState)
    {
    case ShopStateMainMenu:
        ShowShopMainMenu();
        break;
    case ShopStateCategories:
        ShowShopCategoryMenu();
        break;
    case ShopStateSellList:
        ShowShopSellList();
        break;
    case ShopStateBuyList:
        ShowShopBuyList();
        break;
    case ShopStateQuantity:
        ShowShopQuantitySelect();
        break;
    case ShopStateMessage:
        ShowShopMessage();
        break;
    }

    SetAlphaBlendTargets(0x12, 1);
    g_GameModeStackContext.dwModeState = ShopStateFadeIn;
}
