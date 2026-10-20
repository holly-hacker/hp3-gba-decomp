#include "types.h"
#include "actor.h"
#include "input.h"
#include "modes.h"
#include "pouring_minigame.h"
#include "gen/graphics/minigames/pumpkin.h"

// Action states: 0 stands, 1 fills a goblet while A is held, 2 serves it, 8 runs, 17 and
// 16 play the end of a round, in which the bartender throws a goblet. Up/down switch
// lanes and left/right run along the bar.
void TickServePumpkinJuiceBartender(Actor *bartender)
{
    IntPoint anchor;
    s32 x;

    if (g_GameModeStackContext.dwModeState == ServePumpkinJuiceStateRoundOver)
    {
        switch (bartender->bActionState)
        {
        case 17:
            if (bartender->dwFlags & ActorFlagActionAnimDone)
            {
                bartender->dwFlags &= ~ActorFlagActionAnimDone;
                g_ServePumpkinJuice.aabTapPouring[g_ServePumpkinJuice.dwLane][0] = 0;
                bartender->bActionState = 16;
                bartender->wTimedMoveTicks = 0;
                SetActorAnimData(bartender, &g_ServePumpkinJuiceBartenderSprite,
                                 g_aabServePumpkinJuiceBartenderAnims[ServePumpkinJuiceBartenderAnimDrop], 0);
            }
            break;
        case 16:
            bartender->wTimedMoveTicks++;
            if (bartender->dwFlags & ActorFlagActionAnimDone)
            {
                bartender->dwFlags &= ~ActorFlagActionAnimDone;
                bartender->pLinkedActor_candidate = NULL;
                g_GameModeStackContext.dwModeState = ServePumpkinJuiceStateNextRound;
                bartender->bActionState = 0;
            }
            else if (bartender->pLinkedActor_candidate == NULL && bartender->wTimedMoveTicks == 21)
            {
                GetActorAnchor(bartender, 0, &anchor);
                bartender->pLinkedActor_candidate =
                    SpawnActor(0, (bartender->pos.x >> 16) + anchor.x, (bartender->pos.y >> 16) + anchor.y,
                               (const ObjPalette *)gPumpkin044Palette);
                bartender->pLinkedActor_candidate->moveTarget.x = (bartender->pos.x >> 16) + anchor.x;
                bartender->pLinkedActor_candidate->moveTarget.y = (bartender->pos.y >> 16) + anchor.y;
                bartender->pLinkedActor_candidate->oam.priority = 1;
                bartender->pLinkedActor_candidate->pfnTick = TickServePumpkinJuiceDroppedGoblet;
                SetActorAnimData(bartender->pLinkedActor_candidate, &g_ServePumpkinJuiceGobletSprite,
                                 g_aabServePumpkinJuiceGobletAnims[ServePumpkinJuiceGobletAnimEmptyFalling], 0);
                bartender->pLinkedActor_candidate->bActionState = 0;
                bartender->pLinkedActor_candidate->wTimedMoveTicks = 0;
            }
            break;
        default:
            bartender->dwFlags &= ~ActorFlagActionAnimDone;
            bartender->oam.hFlip = 0;
            bartender->bActionState = 17;
            g_ServePumpkinJuice.aabTapPouring[g_ServePumpkinJuice.dwLane][0] = 1;
            g_ServePumpkinJuice.dwLane = 1;
            SpawnServePumpkinJuicePuff(bartender->pos.x >> 16, bartender->pos.y >> 16);
            SnapActorPosition(bartender, g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].x << 16,
                              g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].y << 16);
            SetActorAnimData(bartender, &g_ServePumpkinJuiceBartenderSprite,
                             g_aabServePumpkinJuiceBartenderAnims[ServePumpkinJuiceBartenderAnimFill], 0);
            break;
        }
    }

    if (g_GameModeStackContext.dwModeState == ServePumpkinJuiceStateResults)
        SetActorAnimFrame(bartender, 17);

    if (g_GameModeStackContext.dwModeState != ServePumpkinJuiceStatePlaying)
        return;

    if (bartender->bActionState == 4)
    {
        bartender->dwFlags = (bartender->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        return;
    }

    if (!(g_wKeysHeld & KeyA) && bartender->bActionState == 1 && (bartender->dwFlags & ActorFlagActionAnimDone))
    {
        bartender->dwFlags &= ~ActorFlagActionAnimDone;
        bartender->bActionState = 2;
        SetActorAnimData(bartender, &g_ServePumpkinJuiceBartenderSprite,
                         g_aabServePumpkinJuiceBartenderAnims[ServePumpkinJuiceBartenderAnimServe], 0);
        bartender->oam.hFlip = 0;
    }

    if (bartender->bActionState == 2 && (bartender->dwFlags & ActorFlagActionAnimDone))
    {
        bartender->dwFlags &= ~ActorFlagActionAnimDone;
        bartender->bActionState = 0;
        SetActorAnimFrame(bartender, 18);
        SpawnServePumpkinJuiceFullGoblet();
    }

    if (g_wKeysHeld & (KeyLeft | KeyRight))
    {
        if (bartender->bActionState != 8)
        {
            SetActorAnimData(bartender, &g_ServePumpkinJuiceBartenderSprite,
                             g_aabServePumpkinJuiceBartenderAnims[ServePumpkinJuiceBartenderAnimRun], 0);
            bartender->wTimedMoveTicks = 0;
        }
        else
        {
            bartender->wTimedMoveTicks++;
        }

        if (bartender->wTimedMoveTicks % 8 == 0)
            bartender->bActionState = 8;

        if (g_wKeysHeld & KeyLeft)
        {
            bartender->oam.hFlip = 1;
            x = (bartender->pos.x >> 16) - 3;
            if (x < 0)
                x = 0;
        }
        else
        {
            bartender->oam.hFlip = 0;
            x = (bartender->pos.x >> 16) + 3;
            if (x > g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].x)
                x = g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].x;
        }

        SetActorMoveTargetWithDuration(bartender, x, g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].y, 1);
    }

    if ((!(g_wKeysHeld & (KeyLeft | KeyRight)) && bartender->bActionState == 8) || bartender->bActionState == 0)
    {
        bartender->bActionState = 0;
        SetActorAnimFrame(bartender, 18);
    }

    if (StepCursorUpDown(&g_ServePumpkinJuice.dwLane, 0, 2, 1, 0))
    {
        SpawnServePumpkinJuicePuff(bartender->pos.x >> 16, bartender->pos.y >> 16);
        bartender->bActionState = 0;
        SetActorMoveTargetWithDuration(bartender, g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].x,
                                       g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].y, 3);
        if (bartender->oam.hFlip)
            SetActorAnimFrame(bartender, 18);
        else
            SetActorAnimFrame(bartender, 19);
    }

    if (g_wKeysHeld == KeyA)
    {
        SetActorMoveTargetWithDuration(bartender, g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].x,
                                       g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].y, 3);
        if (bartender->bActionState == 0
            && g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].x - (bartender->pos.x >> 16) <= 5)
        {
            bartender->bActionState = 1;
            SetActorAnimData(bartender, &g_ServePumpkinJuiceBartenderSprite,
                             g_aabServePumpkinJuiceBartenderAnims[ServePumpkinJuiceBartenderAnimFill], 0);
            bartender->oam.hFlip = 0;
            g_ServePumpkinJuice.aabTapPouring[g_ServePumpkinJuice.dwLane][0] = 1;
        }
    }
    else
    {
        if (g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].x - (bartender->pos.x >> 16) <= 5
            && !bartender->oam.hFlip && bartender->bActionState == 0)
            SetActorAnimFrame(bartender, 19);

        g_ServePumpkinJuice.aabTapPouring[g_ServePumpkinJuice.dwLane][0] = 0;
    }
}
