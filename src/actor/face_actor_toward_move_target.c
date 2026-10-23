#include "types.h"
#include "actor.h"
#include "hero.h"

// Faces the actor toward moveTarget; returns 1, facing down and stopped, once it is
// within nMoveSpeed of it.
s32 FaceActorTowardMoveTarget(Actor *actor)
{
    u32 direction;
    FixedPoint pos;
    FixedPoint target;

    pos = actor->pos;
    target = actor->moveTarget;
    direction = GetDirectionToTarget(actor->dwFlags, pos, target, actor->nMoveSpeed);
    if (direction == DirectionNone) {
        SetActorActionSubState(actor, 2);
        StopActorMotion(actor);
        if (actor == g_pPlayerActor)
            actor->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagHasAnimation | ActorFlagTerrainCollision);
        actor->bFacing = DirectionDown;
        return 1;
    }

    if (actor->bFacing != direction) {
        actor->bFacing = direction;
        actor->bActionFlags |= 0x10;
    }
    return 0;
}
