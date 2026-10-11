#include "types.h"
#include "actor.h"
#include "palette.h"

u32 AttachActorPaletteUnshared(Actor *actor, const ObjPalette *pPalette)
{
    return AttachUnsharedPalette(actor, pPalette);
}
