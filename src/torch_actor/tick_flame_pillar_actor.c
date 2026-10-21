#include "types.h"
#include "actor.h"
#include "sound.h"
#include "torch_actor.h"

// Flame pillars burn for wLitTicks (sub state 8), die down and stay out for
// wFlameOutTicks (sub state 6), then reignite. Outside action state 4 the
// flame stays out.
void TickFlamePillarActor(Actor *pActor)
{
    if (pActor->bActionState == 4)
    {
        switch (pActor->bActionSubState)
        {
        case 0:
            pActor->dwStateTimer = pActor->modeState.flamePillar.wLitTicks;
            SetActorActionSubState(pActor, 8);
            break;
        case 1:
            break;
        case 6:
            if (--pActor->dwStateTimer == -1)
            {
                pActor->dwStateTimer = pActor->modeState.flamePillar.wLitTicks;
                SetActorAnimData(pActor, g_apRoomFlamePillarAnimFrames[pActor->wCharacterId_candidate],
                                 g_abRoomFlamePillarAnimData, 0);
                SetActorActionSubState(pActor, 8);
                g_nFlamePillarSoundHandle = PlaySoundByIdUnlessActive(18, g_nFlamePillarSoundHandle);
            }
            break;
        case 8:
            if (--pActor->dwStateTimer == -1)
            {
                pActor->dwStateTimer = pActor->scriptState.wFlameOutTicks;
                SetActorAnimData(pActor, g_apRoomFlamePillarAnimFrames[pActor->wCharacterId_candidate],
                                 g_abRoomFlamePillarAnimData, 6);
                SetActorActionSubState(pActor, 6);
            }
            break;
        case 5:
            if (pActor->pLinkedActor_candidate != NULL)
                pActor->pLinkedActor_candidate->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
            pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
            break;
        }
    }
    else
    {
        SetActorAnimData(pActor, g_apRoomFlamePillarAnimFrames[pActor->wCharacterId_candidate],
                         g_abRoomFlamePillarAnimData, 6);
    }
}
