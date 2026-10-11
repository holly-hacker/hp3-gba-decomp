#include "types.h"
#include "actor.h"
#include "graphics/graphics.h"

void ReleaseActorAffineSlot(Actor *actor)
{
    u16 slot;

    if (actor->oam.affineMode == 1 || actor->oam.affineMode == 3)
    {
        actor->oam.affineMode = 0;
        slot = GetObjectAffineSlotId(&actor->oam);
        SetObjectAffineSlotId(&actor->oam, 0);
        FreeAffineSlot(slot);
    }
}
