#include "modes.h"

void PushGameMode(GameMode mode)
{
    g_dwPendingGameMode.dwCurrentGameMode = mode | GameModeSwitchPending;
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 0;
    g_dwPendingGameMode.dwCurrentGameModeArg2 = 0;
    g_dwPendingGameMode.dwCurrentGameModeArg3 = 0;
    g_dwPendingGameMode.dwModeState = 0;
    g_dwPendingGameMode.dwModeTimer = 0;
}
