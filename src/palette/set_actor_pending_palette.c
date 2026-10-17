#include "actor.h"
#include "palette.h"

void SetActorPendingPalette(Actor *actor, const void *pPalette)
{
    actor->pPendingPalette = pPalette;
    actor->dwPendingPaletteFlags = 0;
}
