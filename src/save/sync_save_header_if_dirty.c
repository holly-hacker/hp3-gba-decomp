#include "types.h"
#include "game/save.h"

// Refreshes the RAM header's checksum and rewrites EEPROM blocks 0-1 when
// the stored header differs. Returns whether it wrote.
u32 SyncSaveHeaderIfDirty(void)
{
    u32 stored[sizeof(SaveHeader) / 4];
    u32 *pRam;
    u32 *pStored;
    s32 i;

    EepromReadBlocks(0, 2, stored);
    g_saveManager.header.wChecksum = 0;
    g_saveManager.header.wChecksum = -Sum16(&g_saveManager.header, sizeof(SaveHeader));

    pRam = (u32 *)&g_saveManager.header;
    pStored = stored;
    for (i = sizeof(SaveHeader) / 4; i != 0; i--)
    {
        if (*pRam != *pStored)
            break;
        pRam++;
        pStored++;
    }

    if (i != 0)
    {
        EepromWriteBlocks(0, 2, &g_saveManager.header);
        return 1;
    }
    return 0;
}
