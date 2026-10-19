#include "types.h"
#include "actor.h"
#include "particles.h"
#include "vram.h"

// Allocates OBJ tiles for every frame of record and loads them into entry `entry` of
// graphics pool `pool`. Returns the first tile, or 0xFFFF when no run is free.
u16 LoadParticleGfx(u32 pool, u32 entry, const ActorAssetRecord *record)
{
    u32 pixelCount;
    ActorFrameData *frameData;
    ActorFrameDesc *frameDesc;
    u32 i;

    pixelCount = 0;
    frameData = record->pFrameData;
    for (i = 0; i < record->pFrameData->wFrameCount; i++)
    {
        g_apParticleGfxPools[pool][entry].awFrameTiles[i] = pixelCount / 64;
        frameDesc = (ActorFrameDesc *)&frameData->awFrameOffsets[record->pFrameData->awFrameOffsets[i] / 2];
        pixelCount += frameDesc->bWidth * frameDesc->bHeight;
    }

    g_apParticleGfxPools[pool][entry].wTileAllocId =
        AllocObjVramTiles((ActorAssetRecord *)record, pixelCount, 0);
    g_apParticleGfxPools[pool][entry].bFrameCount = record->pFrameData->wFrameCount;
    g_apParticleGfxPools[pool][entry].wPixelCount = pixelCount;
    g_apParticleGfxPools[pool][entry].pSprite = (const ParticleSprite *)record;
    return g_apParticleGfxPools[pool][entry].wTileAllocId;
}
