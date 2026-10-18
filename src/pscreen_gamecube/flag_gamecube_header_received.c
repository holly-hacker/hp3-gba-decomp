#include "types.h"
#include "save.h"
#include "gamecube.h"
#include "pscreen_gamecube.h"

// Command 0x41: unlocks the Owl Care Kit the first time.
void FlagGameCubeHeaderReceived(u16 *pLength, u16 *pBuffer)
{
    if (!(g_saveManager.header.bHeaderFlags.all & flOwlCareKitUnlocked))
    {
        g_saveManager.header.bHeaderFlags.all |= flOwlCareKitUnlocked;
        g_JoybusLinkState.bLinkProgress = 1;
    }
}
