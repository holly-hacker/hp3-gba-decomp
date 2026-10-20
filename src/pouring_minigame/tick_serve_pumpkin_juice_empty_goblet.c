#include "types.h"
#include "actor.h"
#include "modes.h"
#include "pouring_minigame.h"

// Slides right along its lane; past the bartender's spot it falls and smashes, which
// loses the game.
void TickServePumpkinJuiceEmptyGoblet(Actor *goblet)
{
    u32 mode = g_GameModeStackContext.dwModeState;

    if (mode == ServePumpkinJuiceStateRoundOver)
    {
        goblet->dwFlags = (goblet->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
    }
    else if (mode == ServePumpkinJuiceStatePlaying || mode == ServePumpkinJuiceStateResults)
    {
        if (goblet->bActionState == 4)
        {
            goblet->dwFlags = (goblet->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        }
        else if (goblet->bActionState == 0)
        {
            if ((goblet->pos.x >> 16) > g_ServePumpkinJuice.aLanePos[goblet->bActionSubState].x - 10)
            {
                goblet->bActionState = 1;
                SetActorAnimData(goblet, &g_ServePumpkinJuiceGobletSprite,
                                 g_aabServePumpkinJuiceGobletAnims[ServePumpkinJuiceGobletAnimEmptyFalling], 0);
                SetActorMoveTargetWithDuration(goblet, (goblet->pos.x >> 16) + 5, (goblet->pos.y >> 16) + 24, 12);
            }
            else
            {
                SetActorMoveTargetWithDuration(goblet, (goblet->pos.x >> 16) + 2, goblet->pos.y >> 16, 1);
            }
        }
        else if (goblet->bActionState == 1)
        {
            if (goblet->wTimedMoveTicks == 12)
            {
                goblet->dwFlags &= ~ActorFlagActionAnimDone;
                goblet->bActionState = 2;
                SetActorAnimData(goblet, &g_ServePumpkinJuiceGobletSprite,
                                 g_aabServePumpkinJuiceGobletAnims[ServePumpkinJuiceGobletAnimEmptySmash], 0);
            }
            else
            {
                goblet->wTimedMoveTicks++;
            }
        }
        else if (goblet->bActionState == 2)
        {
            if (goblet->dwFlags & ActorFlagActionAnimDone)
            {
                goblet->dwFlags = (goblet->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
                g_GameModeStackContext.dwModeState = ServePumpkinJuiceStateResults;
            }
        }
    }
}
