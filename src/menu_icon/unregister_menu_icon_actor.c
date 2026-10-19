#include "types.h"
#include "menu_icon.h"
#include "actor.h"

void UnregisterMenuIconActor(Actor *pActor)
{
    u32 slot;

    slot = pActor->wCharacterId_candidate;
    if (slot < ARRAY_COUNT(g_apMenuIconActors) && pActor == g_apMenuIconActors[slot])
        g_apMenuIconActors[slot] = NULL;
}
