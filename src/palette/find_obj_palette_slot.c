#include "types.h"
#include "palette.h"

// Returns the shared, unreserved slot already holding pPalette, or 0xFF.
u32 FindObjPaletteSlot(const ObjPalette *pPalette)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aObjPaletteSlots); i++)
    {
        if (g_aObjPaletteSlots[i].pData == pPalette
            && !(g_aObjPaletteSlots[i].wFlags & (ObjPaletteSlotFlagUnshared | ObjPaletteSlotFlagReserved)))
            return i;
    }

    return 0xFF;
}
