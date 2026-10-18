#include "pause_menu.h"
#include "screen_transitions.h"

void TickMenuFadeIn(void)
{
    g_GameModeStackContext.dwModeSubState -= 2;
    SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                              g_GameModeStackContext.dwModeSubState);
}
