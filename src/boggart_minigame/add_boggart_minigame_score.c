#include "types.h"
#include "boggart_minigame_inline.h"

void AddBoggartMinigameScore(s32 points)
{
    g_BoggartMinigame.dwScore += points;
    if (g_BoggartMinigame.dwScore > 999999)
        g_BoggartMinigame.dwScore = 999999;

    DrawBoggartMinigameScore();
}
