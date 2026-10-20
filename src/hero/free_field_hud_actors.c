#include "actor.h"
#include "hero.h"

void FreeFieldHudActors(void)
{
    if (g_pFieldSpellIconActor != NULL)
    {
        FreeActor(g_pFieldSpellIconActor);
        g_pFieldSpellIconActor = NULL;
    }
    if (g_pFieldSpellNameActor != NULL)
    {
        FreeActor(g_pFieldSpellNameActor);
        g_pFieldSpellNameActor = NULL;
    }
    if (g_pMapNameTextActor != NULL)
    {
        FreeActor(g_pMapNameTextActor);
        g_pMapNameTextActor = NULL;
    }
    if (g_pMapNamePopupActor != NULL)
    {
        FreeActor(g_pMapNamePopupActor);
        g_pMapNamePopupActor = NULL;
    }
    if (g_pFieldSpellPortraitActor != NULL)
    {
        FreeActor(g_pFieldSpellPortraitActor);
        g_pFieldSpellPortraitActor = NULL;
    }
}
