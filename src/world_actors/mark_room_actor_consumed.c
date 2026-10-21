#include "types.h"
#include "actor.h"
#include "area.h"
#include "world_actors.h"

// Shows a prop in its used state (animation 2, e.g. a pressed switch) and runs its chain.
void MarkRoomActorConsumed(Actor *pActor)
{
    u8 kind = ROOM_ACTOR_TRIGGER_STATE(pActor)->bKind;

    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0xFF;
    SetActorAnimData(pActor, g_apRoomActorTriggerAnimFrames[kind], g_abRoomActorTriggerAnimData[kind], 2);
    SetActorActionState(pActor, 0);
    pActor->dwFlags &= ~ActorFlagWantsCollisionCheck;

    if (ROOM_ACTOR_TRIGGER_STATE(pActor)->bChainRow != 0)
        RespawnGroupAndRunChain(0, ROOM_ACTOR_TRIGGER_STATE(pActor)->bChainRow);
}
