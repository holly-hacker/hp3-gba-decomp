#include "types.h"
#include "hw/mem.h"
#include "graphics/text.h"
#include "game/save.h"

// Allocates the slot buffer and loads the header, options and slot previews
// from EEPROM. An invalid header means an uninitialized or foreign save: the
// header and options are reset, and each slot's first two blocks are zeroed
// so that no slot validates.
void InitSaveSystem(void)
{
    u32 i;
    u32 block;

    g_saveManager.pSlotBuffer = AllocZeroed(SAVE_SLOT_SIZE);

    if (!ValidateSaveHeader())
    {
        WriteDefaultSaveHeader();
        WriteDefaultSaveOptions();
        ClearSaveSlotBuffer();
        for (i = 0, block = SAVE_SLOT_FIRST_BLOCK; i < SAVE_SLOT_COUNT; block += SAVE_SLOT_BLOCKS, i++)
            EepromWriteBlocks(block, 2, g_saveManager.pSlotBuffer);
    }

    if (!ValidateSaveOptions())
        WriteDefaultSaveOptions();

    SetLanguage(g_saveManager.header.language.bLanguageIndex);
    LoadSaveSlotPreviews();
}
