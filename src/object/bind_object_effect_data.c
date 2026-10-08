#include "types.h"
#include "graphics/object.h"
#include "graphics/graphics.h"

// Rebinds the palette ReleaseObjectPalette saved in pEffectData, keeping its
// unshared flag, then clears the saved state.
void BindObjectEffectData(Object *obj)
{
    const ObjPalette *pPalette = obj->pEffectData;

    if (pPalette != NULL)
    {
        if (obj->dwEffectFlags & ResourceCacheFlagUnshared)
            AttachUnsharedPalette(obj, pPalette);
        else
            AttachSharedPalette(obj, pPalette);

        obj->pEffectData = NULL;
        obj->dwEffectFlags = 0;
    }
}
