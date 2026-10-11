#include "types.h"
#include "actor.h"
#include "graphics/graphics.h"

u32 AllocActorAffineSlot(Actor *actor)
{
    u16 slot;

    if (actor->oam.affineMode == 1 || actor->oam.affineMode == 3)
    {
        slot = GetObjectAffineSlotId(&actor->oam);
    }
    else
    {
        slot = AllocAffineSlot();
        SetObjectAffineSlotId(&actor->oam, slot);
    }

    return slot;
}
