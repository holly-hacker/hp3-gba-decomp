#include "types.h"
#include "game/game_modes.h"
#include "dementor_minigame.h"

// Speed in pixels per tick is base + level * step, by difficulty, where level
// is the Dementors repelled (up to 10) times the multiplier.
#define EASY_BASE   0.3
#define EASY_STEP   0.04
#define MEDIUM_BASE 0.4
#define MEDIUM_STEP 0.07
#define HARD_BASE   0.6
#define HARD_STEP   0.1

// A Dementor's speed as 16.16 fixed point, negated when positive is 0.
s32 GetDementorMinigameDementorVelocity(u32 positive, s32 multiplier)
{
    s32 result;
    s32 level;

    if (g_DementorMinigame.dwRepelled > 10)
        level = multiplier * 10;
    else
        level = multiplier * g_DementorMinigame.dwRepelled;

    if (positive)
    {
        if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0)
            result = (level * EASY_STEP + EASY_BASE) * 65536.0;
        else if (g_GameModeStackContext.dwCurrentGameModeArg3 == 1)
            result = (level * MEDIUM_STEP + MEDIUM_BASE) * 65536.0;
        else
            return (level * HARD_STEP + HARD_BASE) * 65536.0;
    }
    else
    {
        if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0)
            result = -(level * EASY_STEP + EASY_BASE) * 65536.0;
        else if (g_GameModeStackContext.dwCurrentGameModeArg3 == 1)
            result = -(level * MEDIUM_STEP + MEDIUM_BASE) * 65536.0;
        else
            result = -(level * HARD_STEP + HARD_BASE) * 65536.0;
    }
    return result;
}
