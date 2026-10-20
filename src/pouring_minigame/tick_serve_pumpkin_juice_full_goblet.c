#include "types.h"
#include "actor.h"
#include "modes.h"
#include "pouring_minigame.h"

// Slides left along its lane after a short delay; past the left end it falls and smashes,
// which loses the game.
void TickServePumpkinJuiceFullGoblet(Actor *goblet)
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
            if (goblet->wTimedMoveTicks > 4)
            {
                if ((goblet->pos.x >> 16) <= 11)
                {
                    goblet->bActionState = 1;
                    SetActorAnimData(goblet, &g_ServePumpkinJuiceGobletSprite,
                                     g_aabServePumpkinJuiceGobletAnims[ServePumpkinJuiceGobletAnimFullFalling], 0);
                    SetActorMoveTargetWithDuration(goblet, (goblet->pos.x >> 16) - 5, (goblet->pos.y >> 16) + 32, 12);
                }
                else
                {
                    SetActorMoveTargetWithDuration(goblet, (goblet->pos.x >> 16) - 3,
                                                   g_ServePumpkinJuice.aLanePos[goblet->bActionSubState].y - 28, 1);
                }
            }
            else
            {
                goblet->wTimedMoveTicks++;
            }
        }
        else if (goblet->bActionState == 1)
        {
            if (goblet->wTimedMoveTicks == 12)
            {
                goblet->dwFlags &= ~ActorFlagActionAnimDone;
                goblet->bActionState = 2;
                SetActorAnimData(goblet, &g_ServePumpkinJuiceGobletSprite,
                                 g_aabServePumpkinJuiceGobletAnims[ServePumpkinJuiceGobletAnimFullSmash], 0);
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
