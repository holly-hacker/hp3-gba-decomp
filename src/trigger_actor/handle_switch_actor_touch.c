#include "types.h"
#include "input.h"
#include "math.h"
#include "trigger_actor.h"
#include "trigger_actor_inline.h"

// Collision callback of a switch: starts the flip (action state 4) for the
// actor and input its variant waits for; see TickSwitchActor.
void HandleSwitchActorTouch(Actor *pSelf, Actor *pOther)
{
    u32 range = pSelf->bPauseRange << 16;
    u32 distance = ApproximateDistance(pSelf->posPrev, pOther->posPrev);
    u16 variant = pSelf->wCharacterId_candidate;

    if (variant == 1)
    {
        if (pOther->wActorType != RoomActorType_Player && pOther->wActorType != RoomActorType_FieldSpellEffect
            && pOther->wActorType != RoomActorType_WanderingMonster
            && pOther->modeState.actor.bRoomScriptArg6A_candidate == 0)
            SWITCH_STATE(pSelf)->nPlatePressed = 1;
    }
    else if (variant >= 6 && variant <= 8)
    {
        if (pOther->wActorType == RoomActorType_Player && pOther->bActionState == 0x21 && (g_wKeysPressed & KeyA))
        {
            pSelf->bActionState = 4;
            pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
            SetActorAnimFrame(pSelf, 1);
            if ((pSelf->dwFlags & ActorFlagVisible) && g_bRestoringRoomActors_candidate == 0)
                g_nSwitchSoundHandle = PlaySoundByIdUnlessActive(38, g_nSwitchSoundHandle);
        }
    }
    else if (variant == 0)
    {
        if (pOther->wActorType == RoomActorType_WorldActor)
        {
            pSelf->bActionState = 4;
            pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
            PlaySwitchSound(pSelf);
        }
    }
    else if (variant != 9 && variant != 10 && pOther->wActorType == RoomActorType_Player && distance <= range)
    {
        pSelf->bActionState = 4;
        pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
        PlaySwitchSound(pSelf);
    }
}
