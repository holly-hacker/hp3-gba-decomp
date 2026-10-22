#include "types.h"
#include "sound.h"
#include "modes.h"
#include "input.h"
#include "title_inline.h"

void MoveMainMenuCursor(void)
{
    u32 previous;

    previous = g_GameModeStackContext.dwModeScratchB;
    PlaySoundById(0);

    if (g_wKeysPressed & KeyUp)
    {
        g_GameModeStackContext.dwModeScratchB--;
        if (g_GameModeStackContext.dwModeScratchB == MainMenuLoadGame
            && !g_MainMenuState.dwLoadGameAvailable)
            g_GameModeStackContext.dwModeScratchB--;
        if (g_GameModeStackContext.dwModeScratchB > MainMenuMiniGames)
            g_GameModeStackContext.dwModeScratchB = MainMenuMiniGames;
    }
    else if (g_wKeysPressed & KeyDown)
    {
        g_GameModeStackContext.dwModeScratchB++;
        if (g_GameModeStackContext.dwModeScratchB == MainMenuLoadGame
            && !g_MainMenuState.dwLoadGameAvailable)
            g_GameModeStackContext.dwModeScratchB = MainMenuOptions;
        if (g_GameModeStackContext.dwModeScratchB > MainMenuMiniGames)
            g_GameModeStackContext.dwModeScratchB = MainMenuNewGame;
    }

    DrawMainMenuEntry(previous, g_GameModeStackContext.dwModeScratchB);
    DrawMainMenuEntry(g_GameModeStackContext.dwModeScratchB, g_GameModeStackContext.dwModeScratchB);
    PositionMainMenuCursorActor(1);
}
