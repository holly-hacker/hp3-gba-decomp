#include "types.h"
#include "modes.h"
#include "store.h"
#include "screen_transitions.h"

void TickShopFadeIn(void)
{
    g_GameModeStackContext.dwModeSubState += 2;
    SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState, 0x10 - g_GameModeStackContext.dwModeSubState);
    if (g_GameModeStackContext.dwModeSubState == 0x10)
        g_GameModeStackContext.dwModeState = g_FredAndGeorgesShop.dwNextState;
}
