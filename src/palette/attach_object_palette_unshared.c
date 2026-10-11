#include "types.h"
#include "graphics/object.h"
#include "palette.h"

u32 AttachObjectPaletteUnshared(Object *obj, const ObjPalette *pPalette)
{
    return AttachUnsharedPalette(obj, pPalette);
}
