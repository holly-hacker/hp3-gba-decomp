#include "types.h"
#include "actor.h"
#include "move.h"

// Runs the terrain pass for one actor: finds the terrain under its box, applies the response
// to blocking terrain and, for actors that follow the room's depth layers, updates the draw
// layer.
void ResolveActorTerrain(Actor *actor)
{
    TerrainBox box;
    u32 type;

    if (actor->dwFlags & (ActorFlagTerrainCollision | ActorFlagSpellTerrainCollision))
    {
        g_adwEdgeEndpointTypes[0] = 0xFF;
        type = GetActorTerrainType(actor, &box);
        if (actor->wActorType == RoomActorType_FieldSpellEffect && IsBlockingCollisionType(type) && (s32)actor->vel.y <= 0)
        {
            actor->posPrev.y += 0x180000;
            type = GetActorTerrainType(actor, &box);
            actor->posPrev.y -= 0x180000;
        }
        RespondToTerrain(actor, type);
    }

    if (actor->dwFlags & ActorFlagTerrainDrawLayer)
        actor->oam.priority = GetCollisionLayerAtPixel((PixelPoint){ (s16)(actor->posPrev.x >> 16), (s16)(actor->posPrev.y >> 16) });
}
