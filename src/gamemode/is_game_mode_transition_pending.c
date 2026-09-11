#include "types.h"
#include "game_modes.h"

s32 IsGameModeTransitionPending(void)
{
    return g_GameModeStackContext.dwCurrentGameMode != g_dwPendingGameMode.dwCurrentGameMode;
}
