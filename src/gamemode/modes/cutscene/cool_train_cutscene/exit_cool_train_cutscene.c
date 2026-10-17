#include "types.h"
#include "modes.h"

void ExitCoolTrainCutscene(void)
{
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
    g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
}
