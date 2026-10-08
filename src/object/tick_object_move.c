#include "graphics/object.h"
#include "divide.h"

// Steps a move started by StartObjectMove: sets the velocity that covers the
// remaining distance in the remaining ticks, snapping to the target once it is
// less than a pixel away on both axes.
void TickObjectMove(Object *obj)
{
    s32 distX;
    s32 distY;
    s8 signX;
    s8 signY;
    s32 velX;
    s32 velY;

    obj->wMoveDuration--;

    if ((s32)obj->nMoveTargetX > (s32)obj->nX) {
        distX = obj->nMoveTargetX - obj->nX;
        signX = 1;
    }
    else {
        distX = obj->nX - obj->nMoveTargetX;
        signX = -1;
    }

    if ((s32)obj->nMoveTargetY > (s32)obj->nY) {
        distY = obj->nMoveTargetY - obj->nY;
        signY = 1;
    }
    else {
        distY = obj->nY - obj->nMoveTargetY;
        signY = -1;
    }

    if ((distX >> 16) == 0 && (distY >> 16) == 0) {
        obj->wMoveDuration = 0;
        obj->nVelX = 0;
        obj->nVelY = 0;
        obj->nX = obj->nMoveTargetX;
        obj->nY = obj->nMoveTargetY;
        obj->nXPrev = obj->nMoveTargetX;
        obj->nYPrev = obj->nMoveTargetY;
    }

    if (obj->wMoveDuration != 0) {
        velX = FixedDivide(distX, obj->wMoveDuration << 16) * signX;
        velY = FixedDivide(distY, obj->wMoveDuration << 16) * signY;
        obj->nVelX = velX;
        obj->nVelY = velY;
    }
    else {
        obj->nVelX = 0;
        obj->nVelY = 0;
    }
}
