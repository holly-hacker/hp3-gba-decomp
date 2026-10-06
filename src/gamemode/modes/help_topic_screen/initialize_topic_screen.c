#include "types.h"
#include "battle/battle.h"
#include "game/game_modes.h"
#include "menu/help.h"

// Argument 2 of the pushed mode selects the topic: the minigame whose instructions to show,
// and the mode to return to.
void InitializeTopicScreen(void)
{
    switch (g_GameModeStackContext.dwCurrentGameModeArg2)
    {
    case 0:
        StartHelpScreen(g_aHelpWizardCrackerPopIt, 1);
        SetHelpExitMode(WizardCrackerPopItMinigame, 6, 0, g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    case 1:
        StartHelpScreen(g_aHelpHippogriffGlide, 1);
        SetHelpExitMode(HippogriffGlideMinigame, 6, 0, g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    case 2:
        StartHelpScreen(g_aHelpRiddikulus, 1);
        SetHelpExitMode(RiddikulusMinigame, 6, 0, g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    case 3:
        StartHelpScreen(g_aHelpTeaLeafDivination, 1);
        SetHelpExitMode(DivinationTeaMinigame, 6, 0, g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    case 4:
        StartHelpScreen(g_aHelpDementors, 1);
        SetHelpExitMode(HarryVsDementorsMinigame, 6, 0, g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    case 6:
        StartHelpScreen(g_aHelpMenuMain, 1);
        SetHelpExitMode(Battle, g_pFightState->abHelpReturnArgs_candidate[0],
                     g_pFightState->abHelpReturnArgs_candidate[1],
                     g_pFightState->abHelpReturnArgs_candidate[2]);
        break;
    }
}
