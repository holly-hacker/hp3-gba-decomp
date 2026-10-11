#include "actor.h"
#include "math.h"

// Steps a move started by StartActorMove: sets the velocity that covers the
// remaining distance in the remaining ticks, snapping to the target once it is
// less than a pixel away on both axes.
void TickActorMove(Actor *actor)
{
    s32 distX;
    s32 distY;
    s8 signX;
    s8 signY;
    s32 velX;
    s32 velY;

    actor->wMoveDuration--;

    if ((s32)actor->moveTarget.x > (s32)actor->pos.x) {
        distX = actor->moveTarget.x - actor->pos.x;
        signX = 1;
    }
    else {
        distX = actor->pos.x - actor->moveTarget.x;
        signX = -1;
    }

    if ((s32)actor->moveTarget.y > (s32)actor->pos.y) {
        distY = actor->moveTarget.y - actor->pos.y;
        signY = 1;
    }
    else {
        distY = actor->pos.y - actor->moveTarget.y;
        signY = -1;
    }

    if ((distX >> 16) == 0 && (distY >> 16) == 0) {
        actor->wMoveDuration = 0;
        actor->vel.x = 0;
        actor->vel.y = 0;
        actor->pos.x = actor->moveTarget.x;
        actor->pos.y = actor->moveTarget.y;
        actor->posPrev.x = actor->moveTarget.x;
        actor->posPrev.y = actor->moveTarget.y;
    }

    if (actor->wMoveDuration != 0) {
        velX = FixedDivide(distX, actor->wMoveDuration << 16) * signX;
        velY = FixedDivide(distY, actor->wMoveDuration << 16) * signY;
        actor->vel.x = velX;
        actor->vel.y = velY;
    }
    else {
        actor->vel.x = 0;
        actor->vel.y = 0;
    }
}
