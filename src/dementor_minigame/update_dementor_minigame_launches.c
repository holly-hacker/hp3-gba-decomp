#include "types.h"
#include "game/game_modes.h"
#include "dementor_minigame.h"

// Launches the next Dementor once fewer than dwPhase + 1 are flying.
void UpdateDementorMinigameLaunches(void)
{
    u32 allIdle;
    s32 flying;
    s32 i;

    switch (g_DementorMinigame.dwPhase)
    {
    case 0:
        if (g_DementorMinigame.dwStartDelay == 1)
        {
            if (--g_GameModeStackContext.dwModeTimer != 0)
                break;
            g_DementorMinigame.dwStartDelay = 0;
            g_GameModeStackContext.dwModeTimer = 10;
        }

        allIdle = 1;
        for (i = 0; i < 4; i++)
        {
            if (g_DementorMinigame.adwDementorStates[i] != DementorIdle)
                allIdle = 0;
        }
        if (allIdle == 1)
            LaunchRandomDementorMinigameDementor();
        break;
    case 1:
        if (--g_GameModeStackContext.dwModeTimer != 0)
            break;
        g_GameModeStackContext.dwModeTimer = 5;

        flying = 0;
        for (i = 0; i < 4; i++)
        {
            if (g_DementorMinigame.adwDementorStates[i] != DementorIdle)
                flying++;
        }
        if (flying <= 1)
            LaunchRandomDementorMinigameDementor();
        break;
    case 2:
        if (--g_GameModeStackContext.dwModeTimer != 0)
            break;
        g_GameModeStackContext.dwModeTimer = 5;

        flying = 0;
        for (i = 0; i < 4; i++)
        {
            if (g_DementorMinigame.adwDementorStates[i] != DementorIdle)
                flying++;
        }
        if (flying <= 2)
            LaunchRandomDementorMinigameDementor();
        break;
    }
}
