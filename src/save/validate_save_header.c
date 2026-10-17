#include "types.h"
#include "save.h"
#include "save_sum16_inline.h"

// Reads the header from EEPROM blocks 0-1. It is valid when its checksum
// holds and its magic matches the ROM default's.
u32 ValidateSaveHeader(void)
{
    s32 i;

    EepromReadBlocks(0, 2, &g_saveManager.header);
    if (Sum16(&g_saveManager.header, sizeof(SaveHeader)) != 0)
        return 0;

    for (i = 0; i < 8; i++)
    {
        if (g_saveManager.header.szMagic[i] != g_DefaultSaveHeader.szMagic[i])
            return 0;
    }

    return 1;
}
