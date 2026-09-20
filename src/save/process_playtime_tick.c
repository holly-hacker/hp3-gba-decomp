#include "save.h"

void ProcessPlaytimeTick(void)
{
    if (g_saveStateBlock.bSaveFlags & PlaytimeCounterActive)
    {
        if (ComparePlaytimeField(&g_saveStateBlock.stPlaytime, &g_stPlaytimeHourLimit, 4) == 1)
        {
            AddPlaytimeDelta(&g_saveStateBlock.stPlaytime, &g_stPlaytimeFrameDelta);
        }
    }
}
