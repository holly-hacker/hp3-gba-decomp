#include "types.h"
#include "game/save.h"

// Writes the slot buffer to the EEPROM blocks of the given slot.
void WriteSaveSlot(u32 slot)
{
    EepromWriteBlocks(SAVE_SLOT_FIRST_BLOCK + slot * SAVE_SLOT_BLOCKS, SAVE_SLOT_BLOCKS, g_saveManager.pSlotBuffer);
}
