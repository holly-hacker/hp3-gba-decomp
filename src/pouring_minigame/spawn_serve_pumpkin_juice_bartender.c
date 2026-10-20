#include "types.h"
#include "actor.h"
#include "pouring_minigame.h"
#include "gen/graphics/minigames/pumpkin.h"

// Also resets the lane, round, score and customer types for a new game.
void SpawnServePumpkinJuiceBartender(void)
{
    Actor *bartender;
    Actor *arm;

    g_ServePumpkinJuice.dwLane = 0;
    g_ServePumpkinJuice.dwRound = 1;
    g_ServePumpkinJuice.dwScore = 0;
    g_ServePumpkinJuice.dwCustomerTypesInUse = 0;
    bartender = SpawnActor(0, g_ServePumpkinJuice.aLanePos[0].x, g_ServePumpkinJuice.aLanePos[0].y,
                           (const ObjPalette *)gPumpkin045Palette);
    arm = SpawnActor(0, g_ServePumpkinJuice.aLanePos[0].x, g_ServePumpkinJuice.aLanePos[0].y,
                     (const ObjPalette *)gPumpkin046Palette);
    arm->pOwnerActor = bartender;
    bartender->pLinkedActor_candidate = NULL;

    bartender->oam.priority = 1;
    bartender->pfnTick = TickServePumpkinJuiceBartender;
    bartender->apfnCollisionCallback[0] = HandleServePumpkinJuiceBartenderTouch;
    SetActorAssetRecord(bartender, &g_ServePumpkinJuiceBartenderSprite);
    bartender->dwFlags |= ActorFlagWantsCollisionCheck;
    bartender->bRoomActorKind_candidate = ServePumpkinJuiceActorBartender;
    bartender->bActionState = 0;
    SetActorAnimFrame(bartender, 4);
    GetActorAnchor(bartender, 0, &g_ServePumpkinJuice.pourOffset);
    SetActorAnimFrame(bartender, 18);
    bartender->oam.hFlip = 1;

    arm->oam.priority = 1;
    arm->pfnTick = TickServePumpkinJuiceBartenderArm;
    SetActorAssetRecord(arm, &g_ServePumpkinJuiceBartenderArmSprite);
    SetActorAnimFrame(arm, 0);
    arm->dwFlags &= ~ActorFlagVisible;
    arm->bRoomActorKind_candidate = ServePumpkinJuiceActorBartender;
    arm->bActionState = 0;
}
