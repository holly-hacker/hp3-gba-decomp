#include "types.h"
#include "actor.h"
#include "overworld/terrain.h"

// Runs ResolveObjectTerrain for an actor that is moving or was flagged to be rechecked, unless
// the terrain pass is skipped for this tick, then clears the one-tick flags.
void CheckActorTerrainCollision(Actor *actor)
{
    u32 flags = actor->dwFlags;

    if (actor->vel.x != 0 || actor->vel.y != 0 || (actor->wFlags_0xAC & 1))
    {
        if ((flags & (ActorFlagTerrainDrawLayer | ActorFlagTerrainCollisionB_candidate
                      | ActorFlagTerrainCollisionA_candidate))
            && !(flags & ActorFlagSkipTerrainOnce_candidate))
            ResolveObjectTerrain(actor);
    }

    actor->wFlags_0xAC = 0;
    actor->dwFlags &= ~ActorFlagSkipTerrainOnce_candidate;
}
