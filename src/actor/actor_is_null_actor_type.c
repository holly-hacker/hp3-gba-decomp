#include "actor.h"

s32 ActorIsNullActorType(Actor *actor)
{
    s32 result;

    result = 0;
    if (actor->wActorType == 0)
        result = 1;
    return result;
}
