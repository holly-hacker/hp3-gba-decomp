#include "types.h"
#include "actor.h"
#include "palette.h"

void SetObjectPendingPaletteUnshared(Actor *obj, const void *pPalette)
{
    SetObjectPendingPalette(obj, pPalette);
    obj->dwPendingPaletteFlags |= ObjPaletteSlotFlagUnshared;
}
