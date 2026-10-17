#include "types.h"
#include "graphics/audio.h"
#include "modes.h"
#include "title.h"

void SelectMainMenuEntry(void)
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
