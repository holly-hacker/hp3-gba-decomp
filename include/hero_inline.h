#pragma once

#include "types.h"
#include "actor.h"
#include "color.h"
#include "combat.h"
#include "hero.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

// The party actor ticks and CycleSelectedFieldSpell compile these in; the
// files that emit the out-of-line copies define the linkage macros as empty.
#ifndef DESTROY_PARTY_MEMBER_ACTOR_LINKAGE
#define DESTROY_PARTY_MEMBER_ACTOR_LINKAGE extern inline
#endif

DESTROY_PARTY_MEMBER_ACTOR_LINKAGE void DestroyPartyMemberActor(Actor *actor)
{
    actor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
    if (actor->pLinkedActor != NULL)
        actor->pLinkedActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
    actor->pShadowActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
}

#ifndef FREE_FIELD_HUD_ACTORS_LINKAGE
#define FREE_FIELD_HUD_ACTORS_LINKAGE extern inline
#endif

FREE_FIELD_HUD_ACTORS_LINKAGE void FreeFieldHudActors(void)
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

#ifndef GET_CHARACTER_FIGHTER_TYPE_LINKAGE
#define GET_CHARACTER_FIGHTER_TYPE_LINKAGE extern inline
#endif

// The FighterType of a party character id; the outfit variants map to their character.
GET_CHARACTER_FIGHTER_TYPE_LINKAGE u32 GetCharacterFighterType(u32 characterId)
{
    switch (characterId)
    {
    case 1:
    case 6:
        return Hermione;
    case 2:
    case 7:
        return Ron;
    case 8:
        return Buckbeak;
    case 0:
    case 3:
    case 4:
    case 5:
    default:
        return Harry;
    }
}

#ifndef REFRESH_FIELD_SPELL_HUD_LINKAGE
#define REFRESH_FIELD_SPELL_HUD_LINKAGE extern inline
#endif

REFRESH_FIELD_SPELL_HUD_LINKAGE void RefreshFieldSpellHud(Actor *iconActor)
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
