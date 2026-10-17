#include "modes.h"
#include "train_cutscene.h"

void ExitCoolTrainCutscene(void)
{
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
    g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
}
