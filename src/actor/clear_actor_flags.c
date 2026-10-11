#include "types.h"
#include "actor.h"

void ClearActorFlags(Actor *actor, ActorFlags flags)
{
    actor->dwFlags &= ~flags;
}
