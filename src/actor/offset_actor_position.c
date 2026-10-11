#include "actor.h"

// Moves the actor by whole pixels from its current pixel, dropping the
// fractional part, with no interpolation pending (see SetActorPosition).
void OffsetActorPosition(Actor *actor, s32 dx, s32 dy)
{
    s32 x;
    s32 y;

    x = (s16)(actor->pos.x >> 16);
    y = (s16)(actor->pos.y >> 16);
    x += dx;
    y += dy;
    actor->pos.x = x << 16;
    actor->pos.y = y << 16;
    actor->posPrev.x = actor->pos.x;
    actor->posPrev.y = actor->pos.y;
}
