#include "types.h"
#include "menu_icon.h"
#include "actor.h"

Actor *SpawnMenuIconActor(u32 slot, void (*pfnTick)(Actor *actor))
{
    Actor *pActor;

    pActor = AllocActorOfType(0x13);
    g_apMenuIconActors[slot] = pActor;
    pActor->wCharacterId_candidate = slot;
    pActor->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic;
    pActor->pfnTick = pfnTick;
    pActor->pfnDestructor = UnregisterMenuIconActor;
    return pActor;
}
