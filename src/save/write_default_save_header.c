#include "types.h"
#include "mem.h"
#include "save.h"
#include "save_sum16_inline.h"

// Resets the header to its ROM default and writes it to EEPROM blocks 0-1.
void WriteDefaultSaveHeader(void)
{
    CopyMemory(&g_saveManager.header, &g_DefaultSaveHeader, sizeof(SaveHeader));
    g_saveManager.header.wChecksum = -Sum16(&g_saveManager.header, sizeof(SaveHeader));
    EepromWriteBlocks(0, 2, &g_saveManager.header);
}
