#include "types.h"
#include "dementor_minigame_inline.h"

void AddDementorMinigameScore(s32 points)
{
    g_DementorMinigame.dwScore += points;
    if (g_DementorMinigame.dwScore > 999999)
        g_DementorMinigame.dwScore = 999999;

    DrawDementorMinigameScore();
}
