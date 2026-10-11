#include "types.h"
#include "actor.h"
#include "palette.h"

// Drops actor's reference to its OBJ palette cache slot. The slot's palette
// pointer and flags are saved in the actor before the refcount is decremented.
void ReleaseActorPalette(Actor *actor)
{
    u32 slot = actor->oam.paletteNum;

    if (actor->dwFlags & ActorFlagHasPaletteSlot)
    {
        actor->dwFlags &= ~ActorFlagHasPaletteSlot;
        actor->pPendingPalette = g_aObjPaletteSlots[slot].pData;
        actor->dwPendingPaletteFlags = g_aObjPaletteSlots[slot].wFlags;
        ReleaseObjPaletteSlot(slot);
    }
}
