#include "types.h"
#include "actor.h"
#include "map.h"

void HandleWanderingMonsterCollision(Actor *pSelf, Actor *pOther)
{
    if (pSelf->wActorType == RoomActorType_WanderingMonster && pOther->wActorType == RoomActorType_Player)
        g_pTouchedWanderingMonster = pSelf;
    else if (pOther->dwFlags & ActorFlagVisible)
    {
        SetActorActionSubState(pSelf, 2);
        pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
        pSelf->dwStateTimer = 15;
    }
}
