#include "types.h"
#include "graphics/graphics.h"
#include "graphics/object.h"

// Takes an emitter from the free list (at most 9 are live at once) and binds it to entry
// `entryIndex` of graphics pool `poolIndex`. Returns NULL when the emitter limit is reached.
ParticleEmitter *AllocParticleEmitter(const ObjPalette *pPalette, u32 poolIndex, u32 entryIndex)
{
    ParticleEmitter *emitter;

    if (g_wActiveParticleEmitterCount <= 8)
    {
        emitter = AllocObjectFromFreeList(&g_pParticleEmitterFreeListHead,
                                          &g_pParticleEmitterActiveListHead,
                                          sizeof(ParticleEmitter));
        g_wActiveParticleEmitterCount++;
        if (g_wActiveParticleEmitterCount > g_wParticleEmitterHighWaterMark)
            g_wParticleEmitterHighWaterMark = g_wActiveParticleEmitterCount;

        emitter->bResourceCacheSlot = AttachObjectPalette(NULL, pPalette);
        emitter->wTileAllocId = g_apParticleGfxPools[poolIndex][entryIndex].wTileAllocId;
        emitter->pSprite = g_apParticleGfxPools[poolIndex][entryIndex].pSprite;
        emitter->dwSpeed = 0x20000;
        emitter->pAnimData = g_apParticleGfxPools[poolIndex][entryIndex].aAnimData;
        return emitter;
    }

    return NULL;
}
