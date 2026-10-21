#include "types.h"
#include "actor.h"
#include "area.h"
#include "torch_actor.h"

// Collision callback: the player touching the flame runs its respawn/chain
// rows.
void HandleFlamePillarTouch(Actor *pSelf, Actor *pOther)
{
    if (pOther->wActorType == RoomActorType_Player && pSelf->modeState.flamePillar.touch.wPair != 0)
        RespawnGroupAndRunChain(pSelf->modeState.flamePillar.touch.rows.bRespawnRow,
                                pSelf->modeState.flamePillar.touch.rows.bChainRow);
}
