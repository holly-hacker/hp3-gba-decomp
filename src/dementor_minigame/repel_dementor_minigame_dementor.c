#include "types.h"
#include "dementor_minigame.h"

void RepelDementorMinigameDementor(s32 direction)
{
    g_DementorMinigame.adwDementorStates[direction] = DementorRetreating;
    StartDementorMinigameDementorRetreat(direction);
    AddDementorMinigameScore(GetDementorMinigameRoundPoints());

    if (++g_DementorMinigame.dwRepelled > 55)
        g_DementorMinigame.dwPhase = 2;
    else if (g_DementorMinigame.dwRepelled > 15)
        g_DementorMinigame.dwPhase = 1;
}
