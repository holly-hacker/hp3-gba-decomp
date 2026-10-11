#include "types.h"
#include "actor.h"
#include "palette.h"

// Rebinds the palette ReleaseObjectPalette saved in pPendingPalette, keeping its
// unshared flag, then clears the saved state.
void BindObjectPendingPalette(Object *obj)
{
    const ObjPalette *pPalette = obj->pPendingPalette;

    if (pPalette != NULL)
    {
        if (obj->dwPendingPaletteFlags & ObjPaletteSlotFlagUnshared)
            AttachUnsharedPalette(obj, pPalette);
        else
            AttachSharedPalette(obj, pPalette);

        obj->pPendingPalette = NULL;
        obj->dwPendingPaletteFlags = 0;
    }
}
