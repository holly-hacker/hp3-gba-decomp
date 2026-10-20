#include "types.h"
#include "actor.h"
#include "random.h"
#include "pouring_minigame.h"

// A customer is a body and a second part linked to it. queuePos spaces the lane's
// customers 10 pixels apart from the left edge.
void SpawnServePumpkinJuiceCustomer(s32 lane, u32 type, u32 queuePos)
{
    s32 x = queuePos * 10;
    Actor *customer;
    Actor *part;

    customer = SpawnActor(0, x, g_ServePumpkinJuice.aLanePos[lane].y - 38,
                          g_aapServePumpkinJuiceCustomerPalettes[type][Mt19937RandRange(
                              1, g_abServePumpkinJuiceCustomerPaletteCounts[type])]);
    part = SpawnActor(0, x, g_ServePumpkinJuice.aLanePos[lane].y - 38, g_aapServePumpkinJuiceCustomerPalettes[type][0]);
    part->pOwnerActor = customer;
    customer->pLinkedActor_candidate = part;
    SetActorAssetRecord(customer, g_aapServePumpkinJuiceCustomerSpriteRows[type][0]);
    SetActorAssetRecord(part, g_aapServePumpkinJuiceCustomerSpriteRows[type][1]);
    SetActorAnimFrame(customer, 0);
    SetActorAnimFrame(part, 0);

    customer->oam.priority = 1;
    customer->pfnTick = TickServePumpkinJuiceCustomer;
    customer->apfnCollisionCallback[0] = HandleServePumpkinJuiceCustomerTouch;
    customer->dwFlags |= ActorFlagWantsCollisionCheck;
    customer->bRoomActorKind_candidate = ServePumpkinJuiceActorCustomer;
    customer->wCharacterId_candidate = type;
    customer->bActionState = 0;
    customer->bActionSubState = lane;
    customer->wTimedMoveTicks = 0;
    customer->wActionVariant = 0;

    part->oam.priority = 1;
    part->pfnTick = TickServePumpkinJuiceCustomerPart;
    part->wCharacterId_candidate = type;
    part->wActionVariant = 0;
    part->bActionState = 0;

    g_ServePumpkinJuice.adwCustomerCount[lane]++;
}
