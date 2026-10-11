#include "types.h"
#include "actor.h"
#include "graphics/graphics.h"

void ReleaseActorAffineSlot(Actor *actor)
{
    u16 slot;

    if (actor->oam.affineMode == 1 || actor->oam.affineMode == 3)
    {
        actor->oam.affineMode = 0;
        slot = GetActorAffineSlotId(&actor->oam);
        SetActorAffineSlotId(&actor->oam, 0);
        FreeAffineSlot(slot);
    }
}
