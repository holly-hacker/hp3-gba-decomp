#include "types.h"
#include "hw/mem.h"
#include "game/save.h"

// Loads and validates each slot, unpacking the preview of a valid one and
// clearing the preview of an invalid one.
void LoadSaveSlotPreviews(void)
{
    u32 slot;
    s32 retries;

    for (slot = 0; slot < SAVE_SLOT_COUNT; slot++)
    {
        retries = 0;
        do
        {
            LoadSaveSlot(slot);
            if (ValidateSaveSlot(slot))
                break;
        } while (retries-- > 0);

        if (g_saveManager.adwSlotValid[slot])
        {
            g_saveManager.pStreamCursor = g_saveManager.pSlotBuffer;
            g_saveManager.dwStreamBitPos = 0;
            g_saveManager.dwStreamMode = SaveStreamUnpacking;
            UnpackSaveSlotPreview(&g_saveManager.aSlotPreview[slot]);
            g_saveManager.dwStreamMode = SaveStreamIdle;
        }
        else
        {
            memset(&g_saveManager.aSlotPreview[slot], 0, sizeof(SaveSlotPreview));
        }
    }
}
