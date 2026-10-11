#include "types.h"
#include "palette.h"

void ReleaseObjPaletteSlot(s32 slotIndex)
{
    if (--g_aObjPaletteSlots[slotIndex].wRefcount == 0)
        g_aObjPaletteSlots[slotIndex].wFlags &= ~1;
}
