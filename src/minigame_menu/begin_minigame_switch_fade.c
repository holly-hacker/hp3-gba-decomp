#include "types.h"
#include "modes.h"
#include "screen_transitions.h"
#include "minigame_menu.h"

// Starts fading BG2 and BG3 (the selected minigame's title and preview) out over 4 frames.
void BeginMinigameSwitchFade(void)
{
    g_GameModeStackContext.dwModeTimer = 4;
    SetAlphaBlendTargets(0xC, 3);
    SetAlphaBlendCoefficients(16, 0);
}
