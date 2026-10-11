#include "types.h"
#include "palette.h"

// Keeps slotIndex's bank out of FindObjPaletteSlot and AllocObjPaletteSlot,
// for screens that load that OBJ palette bank directly.
void ReserveObjPaletteSlot(u32 slotIndex)
{
    g_aObjPaletteSlots[slotIndex].wFlags |= ObjPaletteSlotFlagReserved;
}
