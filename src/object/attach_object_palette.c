#include "types.h"
#include "object.h"
#include "graphics.h"

// Gives obj an OBJ palette bank for pPalette (a 2-byte header followed by 15
// BGR555 colors, loaded into bank colors 1-15). Banks are shared through the
// resource cache: a palette already cached keeps its bank and is not uploaded
// again; a new one takes a free bank (or the last, when none is free) and
// queues its upload. Returns the bank index.
u32 AttachObjectPalette(Object *obj, const ObjPalette *pPalette)
{
    u32 slot = FindResourceCacheSlot(pPalette);

    if (slot != 0xFF)
        pPalette = NULL;
    else
        slot = AllocResourceCacheSlot();

    BindObjectToResourceCacheSlot(slot, obj, pPalette);
    return slot;
}
