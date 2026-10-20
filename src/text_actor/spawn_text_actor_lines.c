#include "types.h"
#include "text_actor.h"
#include "text_actor_inline.h"

// Unreferenced. Spawns one text actor per line of *ppText into consecutive
// slots from `slot`, and returns the number spawned.
u8 SpawnTextActorLines(const u8 **ppText, u32 slot)
{
    Actor *pActor;
    u8 count;

    count = 0;
    do
    {
        pActor = AllocTextActor(ppText);
        g_apTextActors[slot] = pActor;
        pActor->wCharacterId_candidate = slot;
        pActor->pfnDestructor = ClearTextActorSlot;
        count++;
        slot++;
    } while (**ppText != 0);
    return count;
}
