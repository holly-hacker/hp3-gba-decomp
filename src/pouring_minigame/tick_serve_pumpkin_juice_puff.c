#include "types.h"
#include "actor.h"
#include "pouring_minigame.h"

void TickServePumpkinJuicePuff(Actor *puff)
{
    if (puff->dwFlags & ActorFlagActionAnimDone)
        puff->dwFlags = (puff->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
}
