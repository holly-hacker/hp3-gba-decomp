#include "types.h"
#include "hw/mem.h"
#include "game/save.h"

// Clears the live save state and starts a fresh quest state, for the main
// menu's new-game path.
void ResetSaveStateForNewGame(void)
{
    memset(&g_saveStateBlock, 0, sizeof(SaveStateBlock));
    ResetQuestStateForNewGame(0);
}
