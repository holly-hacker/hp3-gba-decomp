#include "types.h"
#include "actor.h"
#include "palette.h"
#include "graphics/display.h"

// Adds a reference to slotIndex. A non-NULL pPalette is stored in the slot and its
// colors 1-15 are queued for upload to OBJ palette bank slotIndex; a non-NULL obj
// is switched to that bank.
void BindObjPaletteSlot(u32 slotIndex, Actor *obj, const ObjPalette *pPalette)
{
    g_aObjPaletteSlots[slotIndex].wRefcount++;
    if (pPalette != NULL)
    {
        g_aObjPaletteSlots[slotIndex].pData = (void *)pPalette;
        QueueObjPaletteLoad(&pPalette->aColors[1], slotIndex * 16 + 1, 15);
    }

    if (obj != NULL)
    {
        obj->oam.paletteNum = slotIndex;
        obj->dwFlags |= ActorFlagHasPaletteSlot;
        obj->pPendingPalette = NULL;
        obj->dwPendingPaletteFlags = 0;
    }
}
