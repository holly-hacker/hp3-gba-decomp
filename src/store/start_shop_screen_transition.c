#include "types.h"
#include "game/game_modes.h"
#include "graphics/display.h"
#include "shop.h"

void StartShopScreenTransition(ShopScreen screen)
{
    SetAlphaBlendTargets(0x12, 1);
    g_FredAndGeorgesShop.dwPrevState = g_GameModeStackContext.dwModeState;
    switch (screen)
    {
    case ShopScreenMainMenu:
        g_FredAndGeorgesShop.dwNextState = ShopStateMainMenu;
        break;
    case ShopScreenCategories:
        g_FredAndGeorgesShop.dwNextState = ShopStateCategories;
        break;
    case ShopScreenSellList:
        g_FredAndGeorgesShop.dwNextState = ShopStateSellList;
        break;
    case ShopScreenBuyList:
        g_FredAndGeorgesShop.dwNextState = ShopStateBuyList;
        break;
    case ShopScreenQuantity:
        g_FredAndGeorgesShop.dwNextState = ShopStateQuantity;
        break;
    case ShopScreenMessage:
        g_FredAndGeorgesShop.dwNextState = ShopStateMessage;
        break;
    }
    g_GameModeStackContext.dwModeSubState = 0x10;
    g_GameModeStackContext.dwModeState = ShopStateFadeOut;
}
