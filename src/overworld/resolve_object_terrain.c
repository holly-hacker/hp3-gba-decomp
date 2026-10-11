#include "types.h"
#include "actor.h"
#include "overworld/terrain.h"

// Runs the terrain pass for one object: finds the terrain under its box, applies the response
// to blocking terrain and, for objects that follow the room's depth layers, updates the draw
// layer.
void ResolveObjectTerrain(Actor *obj)
{
    TerrainBox box;
    u32 type;

    if (obj->dwFlags & (ActorFlagTerrainCollisionA_candidate | ActorFlagTerrainCollisionB_candidate))
    {
        g_adwEdgeEndpointTypes[0] = 0xFF;
        type = GetObjectTerrainType(obj, &box);
        if (obj->wActorType == 0xF && IsBlockingCollisionType(type) && (s32)obj->vel.y <= 0)
        {
            obj->posPrev.y += 0x180000;
            type = GetObjectTerrainType(obj, &box);
            obj->posPrev.y -= 0x180000;
        }
        RespondToTerrain(obj, type);
    }

    if (obj->dwFlags & ActorFlagTerrainDrawLayer)
        obj->oam.priority = GetCollisionLayerAtPixel((PixelPoint){ (s16)(obj->posPrev.x >> 16), (s16)(obj->posPrev.y >> 16) });
}
