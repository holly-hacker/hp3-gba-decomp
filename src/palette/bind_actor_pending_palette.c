#include "types.h"
#include "actor.h"
#include "palette.h"

// Rebinds the palette ReleaseActorPalette saved in pPendingPalette, keeping its
// unshared flag, then clears the saved state.
void BindActorPendingPalette(Actor *actor)
{
    const ObjPalette *pPalette = actor->pPendingPalette;

    if (pPalette != NULL)
    {
        if (actor->dwPendingPaletteFlags & ObjPaletteSlotFlagUnshared)
            AttachUnsharedPalette(actor, pPalette);
        else
            AttachSharedPalette(actor, pPalette);

        actor->pPendingPalette = NULL;
        actor->dwPendingPaletteFlags = 0;
    }
}
