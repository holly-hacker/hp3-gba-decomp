#include "types.h"
#include "menu_icon.h"
#include "actor.h"

void UnregisterMenuIconActor(Actor *pActor)
{
    u32 slot;

    slot = pActor->wSubtype;
    if (slot < ARRAY_COUNT(g_apMenuIconActors) && pActor == g_apMenuIconActors[slot])
        g_apMenuIconActors[slot] = NULL;
}
