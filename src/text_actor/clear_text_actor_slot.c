#include "types.h"
#include "text_actor.h"

// pfnDestructor of slotted text actors: empties the actor's slot if it still
// holds the actor.
void ClearTextActorSlot(Actor *pActor)
{
    u32 slot;

    slot = pActor->wCharacterId_candidate;
    if (slot < ARRAY_COUNT(g_apTextActors) && pActor == g_apTextActors[slot])
        g_apTextActors[slot] = NULL;
}
