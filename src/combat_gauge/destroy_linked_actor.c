#include "types.h"
#include "actor.h"
#include "combat_gauge.h"
#include "combat_gauge_inline.h"

void DestroyLinkedActor(Actor *actor)
{
    DestroyActorAndUnlink(actor);
}
