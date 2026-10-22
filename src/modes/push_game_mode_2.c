#include "types.h"
#include "modes.h"

void PushGameMode_2(GameMode mode, s32 arg1, s32 arg2)
{
    g_dwPendingGameMode.dwCurrentGameMode = mode | GameModeSwitchPending;
    g_dwPendingGameMode.dwCurrentGameModeArg1 = arg1;
    g_dwPendingGameMode.dwCurrentGameModeArg2 = arg2;
    g_dwPendingGameMode.dwCurrentGameModeArg3 = 0;
    g_dwPendingGameMode.dwModeState = 0;
    g_dwPendingGameMode.dwModeTimer = 0;
}
