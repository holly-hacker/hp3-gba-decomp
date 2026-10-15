#include "types.h"
#include "actor.h"

// Runs the overworld behavior of the actor's bActionState.
void TickActorActionState(Actor *actor)
{
    switch (actor->bActionState) {
    case 0:
        break;
    case 1:
        if (actor->pLinkedActor_candidate != 0)
            actor->pLinkedActor_candidate->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        actor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;
    case 6:
        if (--actor->wPauseTimer == 0xFFFF)
            SetActorActionState(actor, actor->bResumeActionState);
        break;
    case 7:
    case 10:
        TickActorWalkRouteLoop(actor);
        break;
    case 8:
    case 11:
    case 13:
        TickActorWalkRouteOnce(actor);
        break;
    case 9:
    case 12:
        TickActorWalkRoutePingPong(actor);
        break;
    case 0x20:
        TickActorWalkToTarget(actor);
        break;
    case 15:
        TickActorScriptWalk(actor);
        break;
    case 0x10:
        TickActorSpongifyJump(actor);
        break;
    case 0x11:
        TickActorPadWalk(actor);
        break;
    case 0x12:
        TickActorFollow(actor);
        break;
    case 0x14:
        TickActorRespawnRow(actor);
        break;
    case 0x21:
        TickPlayerControl(actor);
        break;
    case 0x17:
        TickActorReceiveReward(actor);
        break;
    case 3:
        TickActorStopAndStand(actor);
        break;
    case 0x1B:
        TickActorTurnAround(actor);
        break;
    case 0x13:
        TickActorCastFieldSpell(actor);
        break;
    case 0x24:
        TickActorInDialog(actor);
        break;
    }
}
