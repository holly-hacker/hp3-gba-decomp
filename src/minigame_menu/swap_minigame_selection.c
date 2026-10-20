#include "types.h"
#include "modes.h"
#include "minigame_menu.h"

// Draws the newly selected minigame and starts fading it in.
void SwapMinigameSelection(void)
{
    HandleMinigameMenuSelection(g_GameModeStackContext.dwCurrentGameModeArg2);
    g_GameModeStackContext.dwModeTimer = 4;
    g_GameModeStackContext.dwModeState = 2;
}
