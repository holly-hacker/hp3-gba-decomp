#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "main_menu.h"

void SelectMainMenuEntry_candidate(void)
{
    switch (g_GameModeStackContext.dwModeScratchB)
    {
    case MainMenuNewGame:
        PushGameMode(NewGameMenu);
        break;
    case MainMenuLoadGame:
        PushGameMode(LoadGame);
        break;
    case MainMenuOptions:
        PushGameMode(Options);
        break;
    case MainMenuMiniGames:
        PushGameMode_2(MinigameMenu, 0, 0);
        break;
    }

    PlaySoundById(1);
}
