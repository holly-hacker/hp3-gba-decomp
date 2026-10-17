#include "types.h"
#include "modes.h"
#include "dementor_minigame.h"

// Points for a repelled Dementor: one level per four repelled, up to 20.
s32 GetDementorMinigameRoundPoints(void)
{
    s32 level;
    s32 difficulty;

    level = g_DementorMinigame.dwRepelled / 4;
    if (level > 20)
        level = 20;

    difficulty = g_GameModeStackContext.dwCurrentGameModeArg3 + 1;
    return difficulty * difficulty * level + 10;
}
