#include "types.h"
#include "save.h"

// Refreshes the RAM high scores' checksum and rewrites EEPROM blocks 2-6 when
// the stored high scores differ. Returns whether it wrote.
u32 SyncHighScoresIfDirty(void)
{
    u32 stored[sizeof(SaveHighScores) / 4];
    u32 *pRam;
    u32 *pStored;
    s32 i;

    EepromReadBlocks(2, 5, stored);
    g_saveManager.highScores.wChecksum = 0;
    g_saveManager.highScores.wChecksum = -Sum16(&g_saveManager.highScores, sizeof(SaveHighScores));

    pRam = (u32 *)&g_saveManager.highScores;
    pStored = stored;
    for (i = sizeof(SaveHighScores) / 4; i != 0; i--)
    {
        if (*pRam != *pStored)
            break;
        pRam++;
        pStored++;
    }

    if (i != 0)
    {
        EepromWriteBlocks(2, 5, &g_saveManager.highScores);
        return 1;
    }
    return 0;
}
