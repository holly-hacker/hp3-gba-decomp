#include "types.h"
#include "graphics/object.h"
#include "palette.h"

// Drops obj's reference to its OBJ palette cache slot. The slot's palette
// pointer and flags are saved in the object before the refcount is decremented.
void ReleaseObjectPalette(Object *obj)
{
    u32 slot = obj->oam.paletteNum;

    if (obj->dwFlags & ObjectFlagHasPaletteSlot)
    {
        obj->dwFlags &= ~ObjectFlagHasPaletteSlot;
        obj->pPendingPalette = g_aObjPaletteSlots[slot].pData;
        obj->dwPendingPaletteFlags = g_aObjPaletteSlots[slot].wFlags;
        ReleaseObjPaletteSlot(slot);
    }
}
