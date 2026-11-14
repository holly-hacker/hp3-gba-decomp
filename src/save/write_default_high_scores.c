#include "mem.h"
#include "save.h"
#include "save_sum16_inline.h"

// Resets the high score block to its ROM default and writes it to EEPROM
// blocks 2-6.
void WriteDefaultHighScores(void)
{
    CopyMemory(&g_saveManager.highScores, &g_DefaultHighScores, sizeof(SaveHighScores));
    g_saveManager.highScores.wChecksum = -Sum16(&g_saveManager.highScores, sizeof(SaveHighScores));
    EepromWriteBlocks(2, 5, &g_saveManager.highScores);
}
