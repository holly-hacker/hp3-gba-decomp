#include "types.h"
#include "actor.h"

// See SortObjectsByDepth and TickActorList's per-layer particle flush.
void SetActorDrawLayer(Actor *actor, u8 layer)
{
    u32 type;

    if (actor == NULL)
        return;

    type = layer;
    actor->oam.priority = type;
}
