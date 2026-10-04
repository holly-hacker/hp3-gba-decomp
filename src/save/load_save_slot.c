#include "types.h"
#include "game/save.h"

// Reads a slot from EEPROM into the slot buffer.
void LoadSaveSlot(u32 slot)
{
    EepromReadBlocks(SAVE_SLOT_FIRST_BLOCK + slot * SAVE_SLOT_BLOCKS, SAVE_SLOT_BLOCKS,
                     g_saveManager.pSlotBuffer);
}
