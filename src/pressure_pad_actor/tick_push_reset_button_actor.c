#include "types.h"
#include "actor.h"
#include "area.h"
#include "sound.h"
#include "pressure_pad_actor.h"

// Action state 4 plays the press animation; its ANIM_EVENT frees and respawns
// the eight (group, member) targets. Action state 1 destroys the button.
void TickPushResetButtonActor(Actor *pActor)
{
    u8 i;

    switch (pActor->bActionState)
    {
    case 0:
        if (pActor->dwFlags & ActorFlagSpecialMoveTrigger)
        {
            pActor->dwFlags &= ~ActorFlagSpecialMoveTrigger;
            for (i = 0; i < 8; i++)
            {
                if (PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[i] != 0
                    || PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[i] != 0)
                {
                    Actor *pTarget;

                    pTarget = GetRoomActorPtr(PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[i],
                                              PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[i]);

                    if (pTarget != NULL)
                        FreeActor(pTarget);
                    SpawnRoomGroupMember(PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[i],
                                         PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[i]);
                }
            }
        }
        break;
    case 4:
        PlaySoundById(4);
        SetActorAnimData(pActor, g_apPushResetButtonSprites[pActor->wCharacterId_candidate],
                         g_aabPushResetButtonPressAnims[pActor->wCharacterId_candidate], 0);
        pActor->bActionState = 0;
        break;
    case 1:
        pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;
    }
}
