#include "actor.h"
#include "overworld/overworld.h"

void DestroyPartyMemberActor(Actor *actor)
{
    actor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
    if (actor->pLinkedActor_candidate != NULL)
        actor->pLinkedActor_candidate->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
    actor->pShadowActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
}
