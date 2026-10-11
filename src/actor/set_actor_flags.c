#include "types.h"
#include "actor.h"

void SetActorFlags(Actor *actor, ActorFlags flags)
{
    actor->dwFlags |= flags;
}
