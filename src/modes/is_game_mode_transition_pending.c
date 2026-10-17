#include "types.h"
#include "game/game_modes.h"

s32 IsGameModeTransitionPending(void)
{
    return g_GameModeStackContext.dwCurrentGameMode != g_dwPendingGameMode.dwCurrentGameMode;
}
