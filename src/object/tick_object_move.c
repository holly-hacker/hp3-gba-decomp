#include "graphics/object.h"
#include "math.h"

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

    if ((s32)obj->moveTarget.x > (s32)obj->pos.x) {
        distX = obj->moveTarget.x - obj->pos.x;
        signX = 1;
    }
    else {
        distX = obj->pos.x - obj->moveTarget.x;
        signX = -1;
    }

    if ((s32)obj->moveTarget.y > (s32)obj->pos.y) {
        distY = obj->moveTarget.y - obj->pos.y;
        signY = 1;
    }
    else {
        distY = obj->pos.y - obj->moveTarget.y;
        signY = -1;
    }

    if ((distX >> 16) == 0 && (distY >> 16) == 0) {
        obj->wMoveDuration = 0;
        obj->vel.x = 0;
        obj->vel.y = 0;
        obj->pos.x = obj->moveTarget.x;
        obj->pos.y = obj->moveTarget.y;
        obj->posPrev.x = obj->moveTarget.x;
        obj->posPrev.y = obj->moveTarget.y;
    }

    if (obj->wMoveDuration != 0) {
        velX = FixedDivide(distX, obj->wMoveDuration << 16) * signX;
        velY = FixedDivide(distY, obj->wMoveDuration << 16) * signY;
        obj->vel.x = velX;
        obj->vel.y = velY;
    }
    else {
        obj->vel.x = 0;
        obj->vel.y = 0;
    }
}
