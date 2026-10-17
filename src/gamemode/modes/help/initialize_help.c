#include "types.h"
#include "modes.h"
#include "menu/help.h"

void InitializeHelp(void)
{
    SetHelpExitMode(InGameMenuFadeIn, 0, 0, 0);
    StartHelpScreen(g_aHelpMenuMain, 0);
}
