#include "types.h"
#include "actor.h"
#include "palette.h"

// Gives actor an OBJ palette bank for pPalette, whose colors 1-15 are loaded into
// the bank. Banks are shared through g_aObjPaletteSlots: a palette already
// cached keeps its bank and is not uploaded again; a new one takes a bank from
// AllocObjPaletteSlot and queues its upload. Returns the bank index.
u32 AttachActorPalette(Actor *actor, const ObjPalette *pPalette)
{
    return AttachSharedPalette(actor, pPalette);
}
