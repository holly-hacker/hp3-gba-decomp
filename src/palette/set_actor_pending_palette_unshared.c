#include "actor.h"
#include "palette.h"

void SetActorPendingPaletteUnshared(Actor *actor, const void *pPalette)
{
    SetActorPendingPalette(actor, pPalette);
    actor->dwPendingPaletteFlags |= ObjPaletteSlotFlagUnshared;
}
