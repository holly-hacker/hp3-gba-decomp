#include "types.h"
#include "actor.h"
#include "palette.h"

void SetObjectPendingPaletteUnshared(Object *obj, const void *pPalette)
{
    SetObjectPendingPalette(obj, pPalette);
    obj->dwPendingPaletteFlags |= ObjPaletteSlotFlagUnshared;
}
