#include "types.h"
#include "text_actor.h"
#include "text_actor_inline.h"

Actor *SpawnTextActor(const u8 **ppText, u32 slot)
{
    Actor *pActor;

    pActor = AllocTextActor(ppText);
    g_apTextActors[slot] = pActor;
    pActor->wCharacterId_candidate = slot;
    pActor->pfnDestructor = ClearTextActorSlot;
    return pActor;
}
