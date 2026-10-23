#include "types.h"
#include "menu_icon.h"
#include "actor.h"

void RegisterMenuIconActor(u32 slot, Actor *pActor)
{
    g_apMenuIconActors[slot] = pActor;
    pActor->wSubtype = slot;
    pActor->pfnDestructor = UnregisterMenuIconActor;
}
