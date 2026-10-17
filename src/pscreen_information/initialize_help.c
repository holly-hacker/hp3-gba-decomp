#include "modes.h"
#include "pscreen_information.h"

void InitializeHelp(void)
{
    SetHelpExitMode(InGameMenuFadeIn, 0, 0, 0);
    StartHelpScreen(g_aHelpMenuMain, 0);
}
