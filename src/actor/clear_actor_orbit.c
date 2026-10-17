#include "mem.h"
#include "actor.h"

void ClearActorOrbit(Actor *actor)
{
    memset(&actor->orbitState, 0, sizeof(actor->orbitState));
}
