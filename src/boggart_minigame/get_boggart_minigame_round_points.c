#include "types.h"
#include "game/game_modes.h"
#include "boggart_minigame.h"

s32 GetBoggartMinigameRoundPoints(void)
{
    s32 difficulty = g_GameModeStackContext.dwCurrentGameModeArg3 + 1;

    return difficulty * difficulty * g_BoggartMinigame.bRound + 10;
}
