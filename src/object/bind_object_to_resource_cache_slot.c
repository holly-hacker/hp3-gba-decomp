#include "types.h"
#include "graphics/object.h"
#include "graphics/graphics.h"
#include "graphics/display.h"

// Adds a reference to slotIndex. A non-NULL pPalette is stored in the slot and its
// colors 1-15 are queued for upload to OBJ palette bank slotIndex; a non-NULL obj
// is switched to that bank.
void BindObjectToResourceCacheSlot(u32 slotIndex, Object *obj, const ObjPalette *pPalette)
{
    g_aResourceCache[slotIndex].wRefcount++;
    if (pPalette != NULL)
    {
        g_aResourceCache[slotIndex].pData = (void *)pPalette;
        sub_0800D264(&pPalette->aColors[1], slotIndex * 16 + 1, 15);
    }

    if (obj != NULL)
    {
        obj->oam.paletteNum = slotIndex;
        obj->dwFlags |= ObjectFlagHasPaletteSlot;
        obj->pEffectData = NULL;
        obj->dwEffectFlags = 0;
    }
}
