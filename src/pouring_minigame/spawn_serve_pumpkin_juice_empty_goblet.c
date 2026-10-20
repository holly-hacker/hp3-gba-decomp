#include "types.h"
#include "actor.h"
#include "pouring_minigame.h"
#include "gen/graphics/minigames/pumpkin.h"

void SpawnServePumpkinJuiceEmptyGoblet(u32 lane, s32 x)
{
    Actor *goblet = SpawnActor(0, x, g_ServePumpkinJuice.aLanePos[lane].y - 28, (const ObjPalette *)gPumpkin044Palette);

    goblet->oam.priority = 1;
    goblet->pfnTick = TickServePumpkinJuiceEmptyGoblet;
    goblet->apfnCollisionCallback[0] = HandleServePumpkinJuiceGobletTouch;
    SetActorAnimData(goblet, &g_ServePumpkinJuiceGobletSprite,
                     g_aabServePumpkinJuiceGobletAnims[ServePumpkinJuiceGobletAnimEmpty], 0);
    goblet->dwFlags |= ActorFlagWantsCollisionCheck;
    goblet->bRoomActorKind_candidate = ServePumpkinJuiceActorEmptyGoblet;
    goblet->bActionState = 0;
    goblet->bActionSubState = lane;
    goblet->wTimedMoveTicks = 0;
}
