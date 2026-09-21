#include "types.h"
#include "game_modes.h"

void PushGameMode(GameMode mode)
{
    g_dwPendingGameMode.dwCurrentGameMode = mode | 0x80;
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 0;
    g_dwPendingGameMode.dwCurrentGameModeArg2 = 0;
    g_dwPendingGameMode.dwCurrentGameModeArg3 = 0;
    g_dwPendingGameMode.dwModeState = 0;
    g_dwPendingGameMode.dwModeTimer = 0;
}
