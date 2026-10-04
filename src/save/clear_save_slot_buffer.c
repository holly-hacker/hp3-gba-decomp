#include "types.h"
#include "hw/mem.h"
#include "game/save.h"

void ClearSaveSlotBuffer(void)
{
    memset(g_saveManager.pSlotBuffer, 0, SAVE_SLOT_SIZE);
}
