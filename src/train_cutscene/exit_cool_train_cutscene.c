#include "modes.h"
#include "train_cutscene.h"
#include "map.h"

void ExitCoolTrainCutscene(void)
{
    g_dwPendingGameMode.dwCurrentGameModeArg1 = OverworldEntryReturn;
    g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
}
