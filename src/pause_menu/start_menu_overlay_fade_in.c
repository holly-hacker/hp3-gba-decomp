#include "pause_menu.h"
#include "screen_transitions.h"

void StartMenuOverlayFadeIn(void)
{
    g_GameModeStackContext.dwModeSubState = 0x10;
    SetAlphaBlendTargets(2, 9);
    SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                              g_GameModeStackContext.dwModeSubState);
}
