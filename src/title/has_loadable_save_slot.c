#include "types.h"
#include "save.h"
#include "title.h"

// A slot can be loaded when its checksum is good and it holds a started game.
u32 HasLoadableSaveSlot(void)
{
    s32 slot;

    for (slot = 0; slot < SAVE_SLOT_COUNT; slot++)
    {
        if (g_saveManager.adwSlotValid[slot]
            && (g_saveManager.aSlotPreview[slot].bSaveFlags & PlaytimeCounterActive))
            return 1;
    }

    return 0;
}
