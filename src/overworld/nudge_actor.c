#include "types.h"
#include "actor.h"
#include "overworld/terrain.h"

static inline u32 IsBlockingTerrainType(u32 type)
{
    return type >= 1 && type <= 25;
}

// Nudges an actor's previous position by delta quarter pixels along or against its
// velocity, whichever the dot product favors. Returns nonzero if the nudge was refused (or the
// velocity is perpendicular to it).
u32 NudgeAlongVelocity(Actor *actor, PixelVector delta)
{
    PixelVector nudge;
    s32 dot = actor->vel.x * delta.x + actor->vel.y * delta.y;

    if (dot > 0)
    {
        nudge.x = delta.x << 14;
        nudge.y = delta.y << 14;
    }
    else if (dot < 0)
    {
        nudge.x = -delta.x << 14;
        nudge.y = -delta.y << 14;
    }
    else
        return 1;

    return TryNudgeActor(actor, nudge);
}

// Adds (dx, dy) to the actor's previous position and checks the terrain there. Returns nonzero
// and undoes the move if the terrain blocks it.
u32 TryNudgeActor(Actor *actor, PixelVector delta)
{
    TerrainBox box;
    FixedPoint saved = actor->posPrev;
    u32 type;

    actor->posPrev.x += delta.x;
    actor->posPrev.y += delta.y;
    type = GetActorTerrainType(actor, &box);
    if (actor->wActorType == 0xF && IsBlockingTerrainType(type) && (s32)actor->vel.y <= 0)
    {
        actor->posPrev.y += 0x180000;
        type = GetActorTerrainType(actor, &box);
        actor->posPrev.y -= 0x180000;
    }

    if (IsBlockingTerrainType(type))
    {
        actor->posPrev = saved;
        return 1;
    }

    return 0;
}
