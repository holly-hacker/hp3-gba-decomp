#include "types.h"
#include "game/game_modes.h"
#include "graphics/display.h"
#include "menu/fred_and_georges_shop.h"
#include "menu/main_menu.h"

void InitializeFredAndGeorgesShop(void)
{
    s32 i;
    u32 zero;
    u32 clear;

    g_FredAndGeorgesShop.bUnk5C = 0;
    clear = 0;
    for (i = ARRAY_COUNT(g_FredAndGeorgesShop.adwUnk20) - 1; i >= 0; i--)
        g_FredAndGeorgesShop.adwUnk20[i] = clear;

    zero = 0;
    InitializeMenuScreen(0x53A, 9, 0, NULL, 0, 0);
    SetBgControl(1, g_dwFredAndGeorgesShopBg1Control);
    ClearBgTilemap(1);
    sub_08041360();
    g_FredAndGeorgesShop.bUnk08 = zero;
    sub_08040720();

    PlayScreenTransitionInByIndex(0x3F, 2);
    SetAlphaBlendTargets(2, 1);
    SetAlphaBlendCoefficients(0x10, 0);
    g_GameModeStackContext.dwModeState = 4;
}
