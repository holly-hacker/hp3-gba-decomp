#pragma once

#include "types.h"
#include "actor.h"
#include "menu_icon.h"
#include "modes.h"
#include "random.h"
#include "save.h"
#include "game_state.h"
#include "hedwig_minigame.h"

// TickOwlActor and SpawnOwlCareKitActors inline these; the files that emit
// the out-of-line copies define the linkage macro as empty.
#ifndef SET_OWL_STATE_LINKAGE
#define SET_OWL_STATE_LINKAGE extern inline
#endif
#ifndef FIND_OWL_NEEDIEST_CARE_LINKAGE
#define FIND_OWL_NEEDIEST_CARE_LINKAGE extern inline
#endif
#ifndef SET_OWL_CAGE_DOOR_ANIM_LINKAGE
#define SET_OWL_CAGE_DOOR_ANIM_LINKAGE extern inline
#endif

SET_OWL_STATE_LINKAGE void SetOwlState(u32 state)
{
    g_OwlCareKitScreen.pOwl->bActionState = state;
    SetActorAnimData(g_OwlCareKitScreen.pOwl, g_aOwlAnims[state].pSprite, g_aOwlAnims[state].pAnim, 0);
    switch (state)
    {
    case OwlStateNeedFeed:
    case OwlStateNeedClean:
    case OwlStateNeedPet:
    case OwlStateNeedGroom:
    case OwlStateNeedExercise:
    case OwlStateNeedTeach:
        SpawnOwlThoughtBubble(state);
        break;
    }
}

// The care action with the highest counter, ties broken at random.
FIND_OWL_NEEDIEST_CARE_LINKAGE s32 FindOwlNeediestCare(void)
{
    u32 highest = 0;
    s32 neediest = 0;
    s32 i;

    // BUG: stops before Teach, so its thought bubble never shows.
    for (i = 0; i < 5; i++)
    {
        if (highest < g_saveStateBlock.owlCareKit.abCareCounters[i]
            || (highest == g_saveStateBlock.owlCareKit.abCareCounters[i] && Mt19937Chance(50)))
        {
            neediest = i;
            highest = g_saveStateBlock.owlCareKit.abCareCounters[i];
        }
    }

    return neediest;
}

SET_OWL_CAGE_DOOR_ANIM_LINKAGE void SetOwlCageDoorAnim(u32 anim)
{
    Actor *pDoor = g_apMenuIconActors[2];

    pDoor->bActionSubState = anim;
    SetActorAnimStream(pDoor, g_apOwlCageDoorAnims[anim], 0);
}
