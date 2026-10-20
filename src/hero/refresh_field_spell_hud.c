#include "actor.h"
#include "color.h"
#include "hero.h"
#include "overworld/overworld.h"

void RefreshFieldSpellHud(Actor *iconActor)
{
    QueueObjPaletteLoad(
        g_aFieldSpellIconAssets[g_aFieldSpells[g_bSelectedFieldSpell].dwSpell].pPalette->aColors,
        0x20, 16);
    if (iconActor != NULL)
    {
        SetActorAssetRecord(iconActor,
                            &g_aFieldSpellIconAssets[g_aFieldSpells[g_bSelectedFieldSpell].dwSpell]);
        SetActorAnimFrame(iconActor, 0);
        iconActor->dwFlags |= ActorFlagVisible;
        DrawFieldSpellHud(g_bSelectedFieldSpell);
    }
}
