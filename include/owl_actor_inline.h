#pragma once

#include "types.h"
#include "actor.h"
#include "modes.h"
#include "save.h"
#include "game_state.h"
#include "hedwig_minigame.h"

// SpawnOwlCareKitActors inlines this; initialize_owl_actor_sprite.c defines
// the linkage macro as empty.
#ifndef INITIALIZE_OWL_ACTOR_SPRITE_LINKAGE
#define INITIALIZE_OWL_ACTOR_SPRITE_LINKAGE extern inline
#endif

INITIALIZE_OWL_ACTOR_SPRITE_LINKAGE Actor *InitializeOwlActorSprite(void)
{
    g_OwlCareKitScreen.pOwl = SpawnActor(0, 132, 112, g_apOwlTypePalettes[g_saveStateBlock.owlCareKit.bTypeIndex]);
    if (g_OwlCareKitScreen.pOwl != NULL)
    {
        if (g_GameModeStackContext.dwCurrentGameMode == OwlCareMinigame)
            g_OwlCareKitScreen.pOwl->pfnTick = TickOwlActor;
        SetActorDrawLayer(g_OwlCareKitScreen.pOwl, 1);
        SetOwlState(OwlStateIdle);
    }

    return g_OwlCareKitScreen.pOwl;
}
