#include "types.h"
#include "npc_actor.h"

// Plays script animation animId; TickNpcActor runs its events (action state 0x16).
void StartNpcScriptAnimation(Actor *pActor, u16 animId)
{
    SetActorAnimData(pActor, &g_aActorTypeAssets[110 + animId], g_aabNpcScriptAnims[animId], 0);
    pActor->bRespawnRow = animId;
    SetActorActionState(pActor, 0x16);

    if ((pActor->dwFlags & ActorFlagRoomScriptYield) && animId == 9)
        pActor->dwFlags &= ~ActorFlagVisible;
}
