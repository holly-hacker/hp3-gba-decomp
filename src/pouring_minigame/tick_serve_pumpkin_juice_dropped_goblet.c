#include "types.h"
#include "actor.h"
#include "pouring_minigame.h"

// Thrown by the bartender: flies left on a parabola from its start position, held in
// moveTarget by the spawner, for 20 ticks, then smashes.
void TickServePumpkinJuiceDroppedGoblet(Actor *goblet)
{
    if (++goblet->wTimedMoveTicks == 20)
        SetActorAnimData(goblet, &g_ServePumpkinJuiceGobletSprite,
                         g_aabServePumpkinJuiceGobletAnims[ServePumpkinJuiceGobletAnimEmptySmash], 0);

    if (goblet->wTimedMoveTicks < 20)
    {
        s32 t = goblet->wTimedMoveTicks;

        SnapActorPosition(goblet, (goblet->moveTarget.x - t * 90 / 20) << 16,
                          (goblet->moveTarget.y + t * t / 14) << 16);
    }

    if (goblet->dwFlags & ActorFlagActionAnimDone)
        goblet->dwFlags = (goblet->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
}
