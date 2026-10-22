#include "types.h"
#include "actor.h"
#include "area.h"
#include "world_actors.h"

// Shows a world actor in its used state (animation 2, e.g. a pressed switch) and runs its chain.
void MarkRoomActorConsumed(Actor *pActor)
{
    u8 kind = WORLD_ACTOR_STATE(pActor)->bKind;

    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0xFF;
    SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 2);
    SetActorActionState(pActor, 0);
    pActor->dwFlags &= ~ActorFlagWantsCollisionCheck;

    if (WORLD_ACTOR_STATE(pActor)->bChainRow != 0)
        RespawnGroupAndRunChain(0, WORLD_ACTOR_STATE(pActor)->bChainRow);
}
