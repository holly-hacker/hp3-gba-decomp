#include "types.h"
#include "actor.h"
#include "palette.h"

void SetObjectPendingPalette(Actor *obj, const void *pPalette)
{
    obj->pPendingPalette = pPalette;
    obj->dwPendingPaletteFlags = 0;
}
