#include "lupin_potion_cutscene.h"

void TickLupinPotionEffectActor(Actor *pActor)
{
    if (pActor->dwFlags & ActorFlagActionAnimDone)
        pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
}
