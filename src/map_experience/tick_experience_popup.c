#include "types.h"
#include "actor.h"
#include "map_experience.h"

void TickExperiencePopup(Actor *pActor)
{
    if (--pActor->dwStateTimer == 0)
        pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
}
