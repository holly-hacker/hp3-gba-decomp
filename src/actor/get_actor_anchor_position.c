#include "actor.h"

// Writes the 16.16 position of anchor point `index`, mirrored horizontally
// when the actor faces left. Returns 0, leaving a zero offset in out, when
// the frame has no such anchor.
s32 GetActorAnchorPosition(Actor *actor, u32 index, IntPoint *out)
{
    u32 lastRightFacing;

    lastRightFacing = (actor->dwFlags & ActorFlagSixteenWayDirections) ? 8 : DirectionDown;

    if (GetActorFrameAnchor(actor, actor->anim.pAnimTable->pFrameData, index, out) == 1) {
        out->y = actor->pos.y + (out->y << 16);
        if (actor->bFacing > lastRightFacing)
            out->x = actor->pos.x - (out->x << 16);
        else
            out->x = actor->pos.x + (out->x << 16);
        return 1;
    }

    return 0;
}
