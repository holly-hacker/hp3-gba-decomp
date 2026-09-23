#include "types.h"
#include "object.h"
#include "graphics.h"

// Drops obj's reference to its OBJ palette cache slot. The slot's palette
// pointer and flags are saved in the object before the refcount is decremented.
void ReleaseObjectPalette(Object *obj)
{
    u32 slot = obj->bGfxSlotAndFlags >> 4;

    if (obj->dwFlags & ObjectFlagHasPaletteSlot)
    {
        obj->dwFlags &= ~ObjectFlagHasPaletteSlot;
        obj->pEffectData = g_aResourceCache[slot].pData;
        obj->dwEffectFlags = g_aResourceCache[slot].wFlags;
        DecrementResourceCacheRefcount(slot);
    }
}
