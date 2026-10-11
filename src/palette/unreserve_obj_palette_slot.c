#include "types.h"
#include "palette.h"

void UnreserveObjPaletteSlot(u32 slotIndex)
{
    g_aObjPaletteSlots[slotIndex].wFlags &= ~ObjPaletteSlotFlagReserved;
}
