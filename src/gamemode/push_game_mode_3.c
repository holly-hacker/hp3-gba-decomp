#include "types.h"
#include "game_modes.h"

void PushGameMode_3(GameMode mode, s32 arg1, s32 arg2, s32 arg3)
{
    g_dwPendingGameMode.dwCurrentGameMode = mode | 0x80;
    g_dwPendingGameMode.dwCurrentGameModeArg1 = arg1;
    g_dwPendingGameMode.dwCurrentGameModeArg2 = arg2;
    g_dwPendingGameMode.dwCurrentGameModeArg3 = arg3;
    g_dwPendingGameMode.dwModeState = 0;
    g_dwPendingGameMode.dwModeTimer = 0;
}
