#include "types.h"
#include "actor.h"
#include "pouring_minigame.h"
#include "gen/graphics/minigames/pumpkin.h"

void SpawnServePumpkinJuiceFullGoblet(void)
{
    Actor *goblet = SpawnActor(0,
                               g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].x + g_ServePumpkinJuice.pourOffset.x,
                               g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].y + g_ServePumpkinJuice.pourOffset.y,
                               (const ObjPalette *)gPumpkin044Palette);

    goblet->oam.priority = 1;
    goblet->pfnTick = TickServePumpkinJuiceFullGoblet;
    goblet->apfnCollisionCallback[0] = HandleServePumpkinJuiceGobletTouch;
    SetActorAnimData(goblet, &g_ServePumpkinJuiceGobletSprite,
                     g_aabServePumpkinJuiceGobletAnims[ServePumpkinJuiceGobletAnimFull], 0);
    goblet->dwFlags |= ActorFlagWantsCollisionCheck;
    goblet->bRoomActorKind_candidate = ServePumpkinJuiceActorFullGoblet;
    goblet->bActionState = 0;
    goblet->bActionSubState = g_ServePumpkinJuice.dwLane;
    goblet->wTimedMoveTicks = 0;
    SetActorMoveTargetWithDuration(goblet, (goblet->pos.x >> 16) - 15,
                                   g_ServePumpkinJuice.aLanePos[g_ServePumpkinJuice.dwLane].y - 28, 5);
}
