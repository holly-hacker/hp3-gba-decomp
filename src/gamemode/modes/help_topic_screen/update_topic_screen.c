#include "types.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "input.h"
#include "menu/help.h"

void UpdateTopicScreen(void)
{
    u32 backMask = 0;
    u32 confirmMask = KeyA | KeyB;

    // From the minigame menus, B backs out to the menu and A starts the minigame.
    if (g_PrevGameModeStackContext.dwCurrentGameMode == MinigameMenu
        || g_PrevGameModeStackContext.dwCurrentGameMode == MinigameDifficultySelect)
    {
        backMask = KeyB;
        confirmMask = KeyA;
    }

    if (g_GameModeStackContext.dwCurrentGameModeArg2 <= 4)
    {
        if (g_wKeysPressed & backMask)
        {
            PlaySoundById(2);
            SetHelpExitMode(g_PrevGameModeStackContext.dwCurrentGameMode, 6,
                         g_GameModeStackContext.dwCurrentGameModeArg2,
                         g_GameModeStackContext.dwCurrentGameModeArg3);
            LeaveHelpScreen();
            return;
        }

        if (g_wKeysPressed & confirmMask)
        {
            PlaySoundById(1);
            LeaveHelpScreen();
            return;
        }
    }

    UpdateHelp();
}
