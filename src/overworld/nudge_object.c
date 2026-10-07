#include "types.h"
#include "graphics/object.h"
#include "overworld/terrain.h"

static inline u32 IsBlockingTerrainType(u32 type)
{
    return type >= 1 && type <= 25;
}

// Nudges an object's previous position by delta quarter pixels along or against its
// velocity, whichever the dot product favors. Returns nonzero if the nudge was refused (or the
// velocity is perpendicular to it).
u32 NudgeAlongVelocity(Object *obj, PixelVector delta)
{
    PixelVector nudge;
    s32 dot = obj->nVelX * delta.x + obj->nVelY * delta.y;

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

    return TryNudgeObject(obj, nudge);
}

// Adds (dx, dy) to the object's previous position and checks the terrain there. Returns nonzero
// and undoes the move if the terrain blocks it.
u32 TryNudgeObject(Object *obj, PixelVector delta)
{
    TerrainBox box;
    FixedPoint saved = *(FixedPoint *)&obj->nXPrev;
    u32 type;

    obj->nXPrev += delta.x;
    obj->nYPrev += delta.y;
    type = GetObjectTerrainType(obj, &box);
    if (obj->wObjectType == 0xF && IsBlockingTerrainType(type) && (s32)obj->nVelY <= 0)
    {
        obj->nYPrev += 0x180000;
        type = GetObjectTerrainType(obj, &box);
        obj->nYPrev -= 0x180000;
    }

    if (IsBlockingTerrainType(type))
    {
        *(FixedPoint *)&obj->nXPrev = saved;
        return 1;
    }

    return 0;
}
