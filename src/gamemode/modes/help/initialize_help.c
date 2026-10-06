#include "types.h"
#include "game/game_modes.h"
#include "menu/help.h"

void InitializeHelp(void)
{
    SetHelpExitMode(InGameMenuFadeIn, 0, 0, 0);
    StartHelpScreen(g_aHelpMenuMain, 0);
}
