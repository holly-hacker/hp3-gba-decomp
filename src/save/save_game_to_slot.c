#include "types.h"
#include "hw/mem.h"
#include "graphics/audio.h"
#include "game/save.h"
#include "game/save_slot_preview.h"

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
