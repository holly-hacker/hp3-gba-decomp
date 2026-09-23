#include "types.h"
#include "game_modes.h"

void ExitCoolTrainCutscene(void)
{
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
    g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
}
