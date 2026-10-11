#include "types.h"
#include "palette.h"

u32 IsObjPaletteSlotReserved(u32 slotIndex)
{
    return (g_aObjPaletteSlots[slotIndex].wFlags >> 1) & 1;
}
