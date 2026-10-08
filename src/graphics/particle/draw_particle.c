#include "types.h"
#include "graphics/graphics.h"
#include "graphics/object.h"
#include "overworld/room.h"

// Returns 2 when offscreen, else QueueOamEntry's result. Only the low byte of
// the frame offset is used.
s8 DrawParticle(Particle *particle)
{
    s32 pos[2];
    const ParticleSpriteHeader *header;
    const u16 *offsets;
    s32 entryOffset;
    ObjectFrameDesc *frameDesc;
    u32 width;
    u32 height;

    GetCameraPosition(pos);
    if (particle->wFlags & ParticleEmitterFlagScreenPosition) {
        pos[0] = (s16)(particle->nDrawX >> 16);
        pos[1] = (s16)(particle->nDrawY >> 16);
    }
    else {
        pos[0] = (s16)(particle->nDrawX >> 16) - pos[0];
        pos[1] = (s16)(particle->nDrawY >> 16) - pos[1];
    }
    if ((u32)pos[0] > 240 || pos[1] < 0 || pos[1] > 160)
        return 2;

    header = particle->pSprite->pHeader;
    entryOffset = particle->bFrame * sizeof(u16);
    offsets = header->awFrameOffsets;
    frameDesc = (ObjectFrameDesc *)((u8 *)offsets + *((u8 *)offsets + entryOffset));
    particle->oam.tileNum = particle->wTileAllocId + *(u16 *)((u32)entryOffset + (u32)particle->pAnimData);
    particle->oam.x = pos[0];
    particle->oam.y = pos[1];
    width = frameDesc->bWidth >> 4;
    height = frameDesc->bHeight >> 4;
    if (width == 4)
        width = 3;
    if (height == 4)
        height = 3;
    particle->oam.size = g_abOamSizeForDims[height][width];
    particle->oam.shape = g_abOamShapeForDims[height][width];
    return QueueOamEntry(g_bOamEntryCount, &particle->oam);
}
