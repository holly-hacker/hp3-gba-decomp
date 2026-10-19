#include "types.h"
#include "actor.h"
#include "area.h"
#include "collision.h"

// Collision callback with no known user: the player's first touch turns off
// the actor's collision, sets action state 4 and runs its pair.
void HandleContactTriggerTouch(Actor *pSelf, Actor *pOther)
{
    if (pOther->wActorType != RoomActorType_Player)
        return;

    pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
    SetActorActionState(pSelf, 4);
    RespawnGroupAndRunChain(pSelf->bRespawnRow, pSelf->bChainRow);
}
