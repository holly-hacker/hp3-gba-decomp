#include "pause_menu.h"
#include "screen_transitions.h"

void StartMenuOverlayFadeOut(void)
{
    g_GameModeStackContext.dwModeSubState = 0;
    SetAlphaBlendTargets(2, 9);
    SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                              g_GameModeStackContext.dwModeSubState);
}
