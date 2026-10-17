#include "types.h"
#include "mem.h"
#include "graphics/audio.h"
#include "save.h"
#include "save_slot_preview_inline.h"

// Packs the game state, writes it to the slot's EEPROM blocks and reads it
// back to refresh the slot's validity and preview. The audio engine is
// stopped around the EEPROM transfer.
void SaveGameToSlot(u32 slot)
{
    PackAndChecksumSaveSlot();
    DisableKrawall();
    WriteSaveSlot(slot);
    LoadSaveSlot(slot);
    EnableKrawall();
    ValidateSaveSlot(slot);
    RefreshSaveSlotPreview(slot);
    g_saveManager.dwActiveSlot = slot;
}
