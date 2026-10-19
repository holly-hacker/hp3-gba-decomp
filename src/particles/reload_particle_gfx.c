#include "types.h"
#include "actor.h"
#include "particles.h"
#include "vram.h"

// As LoadParticleGfx, but loads record's tiles into the entry's existing tile allocation
// and stores pixelCount instead of the computed total. Returns the first tile.
u16 ReloadParticleGfx(u32 pool, u32 entry, const ActorAssetRecord *record, u32 pixelCount)
{
    u32 total;
    ActorFrameData *frameData;
    ActorFrameDesc *frameDesc;
    u32 i;

    total = 0;
    frameData = record->pFrameData;
    for (i = 0; i < record->pFrameData->wFrameCount; i++)
    {
        g_apParticleGfxPools[pool][entry].awFrameTiles[i] = total / 64;
        frameDesc = ACTOR_FRAME_DESC(frameData, i);
        total += frameDesc->bWidth * frameDesc->bHeight;
    }

    g_apParticleGfxPools[pool][entry].wPixelCount = pixelCount;
    g_apParticleGfxPools[pool][entry].bFrameCount = record->pFrameData->wFrameCount;
    g_apParticleGfxPools[pool][entry].pSprite = (const ParticleSprite *)record;
    LoadObjVramTilesAt(record, g_apParticleGfxPools[pool][entry].wPixelCount, 0,
                       g_apParticleGfxPools[pool][entry].wTileAllocId);
    return g_apParticleGfxPools[pool][entry].wTileAllocId;
}
