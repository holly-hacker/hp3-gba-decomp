#include "types.h"
#include "game/game_modes.h"
#include "graphics/display.h"
#include "menu/main_menu.h"
#include "shop.h"

void InitializeFredAndGeorgesShop(void)
{
    s32 i;
    u32 zero;
    Object *clear;

    g_FredAndGeorgesShop.bSoldItem = 0;
    clear = NULL;
    for (i = ARRAY_COUNT(g_FredAndGeorgesShop.apRowObjects) - 1; i >= 0; i--)
        g_FredAndGeorgesShop.apRowObjects[i] = clear;

    zero = 0;
    InitializeMenuScreen(0x53A, 9, 0, NULL, 0, 0);  // "Fred and George's Shop"
    SetBgControl(1, g_dwFredAndGeorgesShopBg1Control);
    ClearBgTilemap(1);
    DrawShopSickles();
    g_FredAndGeorgesShop.bCursor = zero;
    ShowShopMainMenu();

    PlayScreenTransitionInByIndex(0x3F, 2);
    SetAlphaBlendTargets(2, 1);
    SetAlphaBlendCoefficients(0x10, 0);
    g_GameModeStackContext.dwModeState = ShopStateMainMenu;
}
