#include "types.h"
#include "random.h"
#include "dementor_minigame.h"

// Launches a random idle Dementor, if one other than the last launched is idle.
void LaunchRandomDementorMinigameDementor(void)
{
    u32 available;
    s32 direction;

    available = 0;
    for (direction = 0; direction < 4; direction++)
    {
        if (g_DementorMinigame.adwDementorStates[direction] == DementorIdle
            && direction != g_DementorMinigame.dwLastDementor)
            available = 1;
    }

    if (available)
    {
        do
            direction = Mt19937RandRange(0, 3);
        while (g_DementorMinigame.adwDementorStates[direction] != DementorIdle);

        g_DementorMinigame.dwLastDementor = direction;
        g_DementorMinigame.adwDementorStates[direction] = DementorApproaching;
        LaunchDementorMinigameDementor(direction);
    }
}
