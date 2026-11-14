#include "types.h"
#include "save.h"
#include "save_sum16_inline.h"

// Reads the high score block from EEPROM blocks 2-6 and returns whether its
// checksum holds.
u32 ValidateHighScores(void)
{
    EepromReadBlocks(2, 5, &g_saveManager.highScores);
    if (Sum16(&g_saveManager.highScores, sizeof(SaveHighScores)) != 0)
        return 0;

    return 1;
}
