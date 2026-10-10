#include "types.h"
#include "game/game_modes.h"
#include "graphics/display.h"
#include "shop.h"

void TickShopFadeIn(void)
{
    g_GameModeStackContext.dwModeSubState += 2;
    SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState, 0x10 - g_GameModeStackContext.dwModeSubState);
    if (g_GameModeStackContext.dwModeSubState == 0x10)
        g_GameModeStackContext.dwModeState = g_FredAndGeorgesShop.dwNextState;
}
