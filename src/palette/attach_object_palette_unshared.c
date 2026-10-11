#include "types.h"
#include "actor.h"
#include "palette.h"

u32 AttachObjectPaletteUnshared(Object *obj, const ObjPalette *pPalette)
{
    return AttachUnsharedPalette(obj, pPalette);
}
