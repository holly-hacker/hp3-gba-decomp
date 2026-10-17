#include "types.h"
#include "modes.h"
#include "boggart_minigame.h"

// Speed in pixels per tick is base + round * step, by difficulty.
#define EASY_BASE   0.3
#define EASY_STEP   0.03
#define MEDIUM_BASE 0.4
#define MEDIUM_STEP 0.06
#define HARD_BASE   0.6
#define HARD_STEP   0.1

// The Boggart's speed as 16.16 fixed point, negated when forward is 0.
s32 GetBoggartMinigameBoggartVelocity(u32 forward)
{
    s32 result;

    if (forward)
    {
        if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0)
            result = (g_BoggartMinigame.bRound * EASY_STEP + EASY_BASE) * 65536.0;
        else if (g_GameModeStackContext.dwCurrentGameModeArg3 == 1)
            result = (g_BoggartMinigame.bRound * MEDIUM_STEP + MEDIUM_BASE) * 65536.0;
        else
            return (g_BoggartMinigame.bRound * HARD_STEP + HARD_BASE) * 65536.0;
    }
    else
    {
        if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0)
            result = -(g_BoggartMinigame.bRound * EASY_STEP + EASY_BASE) * 65536.0;
        else if (g_GameModeStackContext.dwCurrentGameModeArg3 == 1)
            result = -(g_BoggartMinigame.bRound * MEDIUM_STEP + MEDIUM_BASE) * 65536.0;
        else
            result = -(g_BoggartMinigame.bRound * HARD_STEP + HARD_BASE) * 65536.0;
    }
    return result;
}
