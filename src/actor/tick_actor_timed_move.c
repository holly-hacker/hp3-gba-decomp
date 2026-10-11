#include "types.h"
#include "hw/bios.h"
#include "actor.h"

// Steps a move started by StartActorTimedMove: like TickActorMove, but counts
// down wTimedMoveTicks and divides with the BIOS. Returns 1 once the actor is
// less than a pixel from the target on both axes, after snapping it there.
s32 TickActorTimedMove(Actor *actor)
{
    s32 arrived;
    s32 distX;
    s32 distY;
    s8 signX;
    s8 signY;

    arrived = 0;
    actor->wTimedMoveTicks--;

    if (actor->moveTarget.x > actor->pos.x) {
        distX = actor->moveTarget.x - actor->pos.x;
        signX = 1;
    }
    else {
        distX = actor->pos.x - actor->moveTarget.x;
        signX = -1;
    }

    if (actor->moveTarget.y > actor->pos.y) {
        distY = actor->moveTarget.y - actor->pos.y;
        signY = 1;
    }
    else {
        distY = actor->pos.y - actor->moveTarget.y;
        signY = -1;
    }

    if ((distX >> 16) == 0 && (distY >> 16) == 0) {
        SetActorVelocity(actor, 0, 0);
        SnapActorPosition(actor, actor->moveTarget.x, actor->moveTarget.y);
        arrived = 1;
    }
    else {
        SetActorVelocity(actor, bios_Div(distX, actor->wTimedMoveTicks) * signX,
                         bios_Div(distY, actor->wTimedMoveTicks) * signY);
    }

    return arrived;
}
