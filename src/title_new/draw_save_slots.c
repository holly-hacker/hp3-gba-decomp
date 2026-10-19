#include "types.h"
#include "modes.h"
#include "save.h"
#include "title_load.h"
#include "title_new.h"

void DrawSaveSlots(void)
{
    u32 slot;

    for (slot = 0; slot < SAVE_SLOT_COUNT; slot++)
        DrawSaveSlot(slot, g_GameModeStackContext.dwModeScratchB);
}
