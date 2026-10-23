#pragma once

#include "types.h"
#include "actor.h"
#include "sound.h"
#include "trigger_actor.h"

// A visible switch plays its sound when it flips, except for the first flip of
// one respawned by RestoreRoomActorState (action flag 0x20).
static inline void PlaySwitchSound(Actor *pActor)
{
    if ((pActor->dwFlags & ActorFlagVisible) && g_bRestoringRoomActors == 0)
    {
        if (pActor->bActionFlags == 0)
            g_nSwitchSoundHandle = PlaySoundByIdUnlessActive(38, g_nSwitchSoundHandle);
        else
            pActor->bActionFlags &= ~0x20;
    }
}
