#include "types.h"
#include "save.h"
#include "save_sum16_inline.h"

// Reads the options block from EEPROM blocks 2-6 and returns whether its
// checksum holds.
u32 ValidateSaveOptions(void)
{
    EepromReadBlocks(2, 5, &g_saveManager.options);
    if (Sum16(&g_saveManager.options, sizeof(SaveOptions)) != 0)
        return 0;

    return 1;
}
