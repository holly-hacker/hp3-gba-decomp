#include "mem.h"
#include "save.h"
#include "save_sum16_inline.h"

// Resets the options block to its ROM default and writes it to EEPROM
// blocks 2-6.
void WriteDefaultSaveOptions(void)
{
    CopyMemory(&g_saveManager.options, &g_DefaultSaveOptions, sizeof(SaveOptions));
    g_saveManager.options.wChecksum = -Sum16(&g_saveManager.options, sizeof(SaveOptions));
    EepromWriteBlocks(2, 5, &g_saveManager.options);
}
