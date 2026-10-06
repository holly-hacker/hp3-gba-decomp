#include "types.h"
#include "game/save.h"

// Refreshes the RAM options' checksum and rewrites EEPROM blocks 2-6 when
// the stored options differ. Returns whether it wrote.
u32 SyncSaveOptionsIfDirty(void)
{
    u32 stored[sizeof(SaveOptions) / 4];
    u32 *pRam;
    u32 *pStored;
    s32 i;

    EepromReadBlocks(2, 5, stored);
    g_saveManager.options.wChecksum = 0;
    g_saveManager.options.wChecksum = -Sum16(&g_saveManager.options, sizeof(SaveOptions));

    pRam = (u32 *)&g_saveManager.options;
    pStored = stored;
    for (i = sizeof(SaveOptions) / 4; i != 0; i--)
    {
        if (*pRam != *pStored)
            break;
        pRam++;
        pStored++;
    }

    if (i != 0)
    {
        EepromWriteBlocks(2, 5, &g_saveManager.options);
        return 1;
    }
    return 0;
}
