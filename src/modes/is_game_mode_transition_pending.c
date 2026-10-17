#include "types.h"
#include "modes.h"

s32 IsGameModeTransitionPending(void)
{
    return g_GameModeStackContext.dwCurrentGameMode != g_dwPendingGameMode.dwCurrentGameMode;
}
