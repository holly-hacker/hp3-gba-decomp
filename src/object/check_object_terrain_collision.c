#include "types.h"
#include "graphics/object.h"
#include "overworld/terrain.h"

// Runs ResolveObjectTerrain for an object that is moving or was flagged to be rechecked, unless
// the terrain pass is skipped for this tick, then clears the one-tick flags.
void CheckObjectTerrainCollision(Object *obj)
{
    u32 flags = obj->dwFlags;

    if (obj->vel.x != 0 || obj->vel.y != 0 || (obj->wFlags_0xAC & 1))
    {
        if ((flags & (ObjectFlagTerrainDrawLayer | ObjectFlagTerrainCollisionB_candidate
                      | ObjectFlagTerrainCollisionA_candidate))
            && !(flags & ObjectFlagSkipTerrainOnce_candidate))
            ResolveObjectTerrain(obj);
    }

    obj->wFlags_0xAC = 0;
    obj->dwFlags &= ~ObjectFlagSkipTerrainOnce_candidate;
}
