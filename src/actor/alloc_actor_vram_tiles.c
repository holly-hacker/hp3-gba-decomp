#include "vram.h"
#include "actor.h"

// Allocates OBJ VRAM tiles for the actor's wVramPixelCount pixels.
void AllocActorVramTiles(Actor *actor, ActorAssetRecord *record)
{
    actor->wVramTileAllocId = AllocObjVramTiles(record, actor->wVramPixelCount, actor->oam.bpp8);
}
