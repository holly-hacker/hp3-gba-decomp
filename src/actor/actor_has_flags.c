#include "types.h"
#include "actor.h"

s32 ActorHasFlags(Actor *actor, ActorFlags flags)
{
    if ((actor->dwFlags & flags) == flags)
        return 1;
    return 0;
}
