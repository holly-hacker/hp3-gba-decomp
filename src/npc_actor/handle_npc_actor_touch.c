#include "types.h"
#include "input.h"
#include "modes.h"
#include "npc_actor.h"

// Collision callback of an NPC: the player talking to it with A starts the
// interaction (action state 4), unless it is used up or cooling down.
void HandleNpcActorTouch(Actor *pSelf, Actor *pOther)
{
    u8 flags = pSelf->bTypeFlags;

    if (pOther->wActorType == RoomActorType_Player && (g_wKeysPressed & KeyA) && !(flags & 1)
        && pOther->bActionState == 0x21 && !IsGameModeTransitionPending())
    {
        if (pSelf->bKind == 0 && !(flags & 2))
        {
            pSelf->bTypeFlags |= 3;
        }
        else
        {
            if (pSelf->bKind != 1 || pSelf->timer84.wInteractCooldown != 0)
                return;
            pSelf->bTypeFlags |= 1;
        }

        SetActorPrevActionState(pSelf, pSelf->bActionState);
        SetActorActionState(pSelf, 4);
        pSelf->dwFlags &= ~ActorFlagHasAnimation;
    }
}
