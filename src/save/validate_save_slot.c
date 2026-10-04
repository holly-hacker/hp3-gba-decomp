#include "types.h"
#include "game/save.h"

// Checksums the slot buffer (holding the given slot) and records the result.
u32 ValidateSaveSlot(u32 slot)
{
    u32 valid;

    if (Sum16(g_saveManager.pSlotBuffer, SAVE_SLOT_SIZE) == 0)
        valid = 1;
    else
        valid = 0;

    g_saveManager.adwSlotValid[slot] = valid;
    return valid;
}
