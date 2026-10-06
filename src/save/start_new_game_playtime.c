#include "types.h"
#include "game/save.h"

// Starts the playtime counter at zero and marks the save as started, then
// levels the party to 1.
void StartNewGamePlaytime(void)
{
    CopyPlaytime(&g_saveStateBlock.stPlaytime, &g_stPlaytimeZero);
    g_saveStateBlock.bSaveFlags |= PlaytimeCounterActive;
    ResetAllPartyLevelsTo1();
}
