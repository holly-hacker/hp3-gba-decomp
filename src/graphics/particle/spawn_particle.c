#include "types.h"
#include "battle/effect_script.h"
#include "graphics/graphics.h"
#include "graphics/object.h"
#include "mt19937.h"

// Spawns one particle from an emitter. Position, lifetime and direction draws use the visual RNG
// cursor (Mt19937*2); modes 6, 7 and 8 draw their velocity from the gameplay cursor.
void SpawnParticle(ParticleEmitter *emitter)
{
    Particle *particle;
    ScreenPoint pos;
    ScreenPoint endPos;
    s32 spread;
    s32 t;
    s32 dx;
    s32 dy;

    particle = AllocParticle();

    spread = emitter->wSpread;
    if (emitter->wFlags & ParticleEmitterFlagScreenPosition)
    {
        pos.x = emitter->pTarget->oam.x;
        pos.y = emitter->pTarget->oam.y;
    }
    else if (emitter->bMode == ParticleModeStillAlt
             || emitter->bMode == ParticleModeRandomDirectionAlt)
    {
        if (!sub_08001AA8(emitter->pTarget, 2, &pos))
        {
            FreeParticle(particle);
            return;
        }
        if (!sub_08001AA8(emitter->pTarget, 3, &endPos))
        {
            FreeParticle(particle);
            return;
        }

        if (emitter->pTarget->bFacing > 4)
        {
            pos.x = emitter->pTarget->nXPrev - (pos.x << 16);
            endPos.x = emitter->pTarget->nXPrev - (endPos.x << 16);
        }
        else
        {
            pos.x = emitter->pTarget->nXPrev + (pos.x << 16);
            endPos.x = emitter->pTarget->nXPrev + (endPos.x << 16);
        }
        pos.y = emitter->pTarget->nYPrev + (pos.y << 16);
        endPos.y = emitter->pTarget->nYPrev + (endPos.y << 16);

        dx = endPos.x - pos.x;
        dy = endPos.y - pos.y;
        t = Mt19937RandRange2(0, 0xFFFF);
        endPos.x = FixedMultiply(dx, t);
        endPos.y = FixedMultiply(dy, t);
        pos.x += endPos.x;
        pos.y += endPos.y;
        pos.x >>= 16;
        pos.y >>= 16;
    }
    else if (emitter->wFlags & ParticleEmitterFlagAnchorPosition)
    {
        if (!sub_08001AA8(emitter->pTarget, emitter->bParam43, &pos))
        {
            FreeParticle(particle);
            return;
        }

        if (emitter->pTarget->bFacing > 4)
            pos.x = emitter->pTarget->nXPrev - (pos.x << 16);
        else
            pos.x = emitter->pTarget->nXPrev + (pos.x << 16);
        pos.y = emitter->pTarget->nYPrev + (pos.y << 16);
        pos.x = (s32)pos.x >> 16;
        pos.y = (s32)pos.y >> 16;
    }
    else if (emitter->wFlags & ParticleEmitterFlagFixedPosition)
    {
        pos.x = emitter->sPosX;
        pos.y = emitter->sPosY;
    }
    else
    {
        pos.x = (s16)(emitter->pTarget->nXPrev >> 16);
        pos.y = (s16)(emitter->pTarget->nYPrev >> 16);
    }

    particle->nX = Mt19937RandRange2(pos.x - spread, pos.x + spread) << 16;
    particle->nY = Mt19937RandRange2(pos.y - spread, pos.y + spread) << 16;

    if (emitter->wLifetimeRange != 0)
    {
        if (emitter->wLifetimeRange == 5)
            particle->sLife = emitter->wLifetimeBase + 5;
        else
            particle->sLife = emitter->wLifetimeBase + Mt19937RandRange2(emitter->wLifetimeRange, 5);
    }
    else
        particle->sLife = emitter->wLifetimeBase + Mt19937RandRange2(1, 5);

    particle->oam.objMode = 0;
    particle->oam.bpp8 = 0;
    if (emitter->wFlags & ParticleEmitterFlagPriorityFromTarget)
        particle->oam.priority = emitter->pTarget->oam.priority;
    else if (emitter->wFlags & ParticleEmitterFlagScreenPosition)
        particle->oam.priority = 1;
    else if (emitter->wFlags & ParticleEmitterFlagPriorityAbove)
        particle->oam.priority = emitter->pTarget->oam.priority + 1;
    else if (emitter->wFlags & ParticleEmitterFlagPriorityBelow_candidate)
    {
        if (particle->oam.priority != 0)
            particle->oam.priority = emitter->pTarget->oam.priority - 1;
        else
            particle->oam.priority = 0;
    }
    else
        particle->oam.priority = 2;
    particle->oam.paletteNum = emitter->bResourceCacheSlot;

    particle->wTileAllocId = emitter->wTileAllocId;
    particle->pSprite = emitter->pSprite;
    if (emitter->wFlags & ParticleEmitterFlagAnimTicksFixed)
        particle->bAnimTicks = emitter->bAnimTicks;
    else if (particle->sLife >= particle->pSprite->pHeader->wFrameCount_candidate)
        particle->bAnimTicks = particle->sLife / particle->pSprite->pHeader->wFrameCount_candidate;
    else
        particle->bAnimTicks = 1;

    particle->bFrame = 0;
    particle->wFrameCounter = 0;
    particle->bMode = emitter->bMode;
    particle->wFlags = emitter->wFlags;
    particle->oam.size = emitter->bOamSize;
    particle->oam.shape = 0;
    particle->pAnimData = emitter->pAnimData;
    particle->bUnk44 = 0;

    switch (particle->bMode)
    {
    case ParticleModeStill:
        particle->nVelX = 0;
        particle->nVelY = 0;
        particle->bParam = emitter->pTarget->bFacing;
        break;

    case ParticleModeDirectional:
        if (particle->wFlags & ParticleEmitterFlagFourWayDirections)
        {
            particle->bParam = g_abOppositeDirection4[emitter->bDirection];
            particle->dwSpeed = emitter->dwSpeed;
            particle->nVelX = FixedMultiply(g_aDirection4Vectors[particle->bParam][0], particle->dwSpeed);
            particle->nVelY = FixedMultiply(g_aDirection4Vectors[particle->bParam][1], particle->dwSpeed);
            particle->dwInitialSpeed = particle->dwSpeed;
        }
        else
        {
            particle->bParam = g_abOppositeDirection8[emitter->bDirection];
            particle->dwSpeed = emitter->dwSpeed;
            particle->nVelX = FixedMultiply(g_aDirection8Vectors[particle->bParam][0], particle->dwSpeed);
            particle->nVelY = FixedMultiply(g_aDirection8Vectors[particle->bParam][1], particle->dwSpeed);
            particle->dwInitialSpeed = particle->dwSpeed;
        }
        break;

    case ParticleModeRandomDirection:
        particle->bParam = Mt19937RandRange2(0, 7);
        particle->dwSpeed = emitter->dwSpeed;
        particle->dwInitialSpeed = particle->dwSpeed;
        particle->nVelX = FixedMultiply(g_aDirection8Vectors[particle->bParam][0], particle->dwSpeed);
        particle->nVelY = FixedMultiply(g_aDirection8Vectors[particle->bParam][1], particle->dwSpeed);
        break;

    case ParticleModeFixedDirection:
        particle->bParam = emitter->bDirection;
        particle->dwSpeed = emitter->dwSpeed;
        particle->nVelX = FixedMultiply(g_aDirection8Vectors[particle->bParam][0], particle->dwSpeed);
        particle->nVelY = FixedMultiply(g_aDirection8Vectors[particle->bParam][1], particle->dwSpeed);
        particle->dwInitialSpeed = particle->dwSpeed;
        particle->bMode = ParticleModeDirectional;
        break;

    case ParticleModeRandomSpeed:
        particle->bParam = emitter->bDirection;
        particle->dwSpeed = Mt19937RandMax(emitter->dwSpeed) << 8;
        particle->nVelX = FixedMultiply(g_aDirection8Vectors[particle->bParam][0], particle->dwSpeed);
        particle->nVelY = FixedMultiply(g_aDirection8Vectors[particle->bParam][1], particle->dwSpeed);
        particle->dwInitialSpeed = particle->dwSpeed;
        particle->bMode = ParticleModeDirectional;
        break;

    case ParticleModeRandomSpeedVector:
        particle->dwSpeed = Mt19937RandMax(emitter->dwSpeed) << 8;
        particle->nVelX = FixedMultiply(emitter->nVelX, particle->dwSpeed);
        particle->nVelY = FixedMultiply(emitter->nVelY, particle->dwSpeed);
        particle->dwInitialSpeed = particle->dwSpeed;
        particle->bMode = ParticleModeDirectional;
        break;

    case ParticleModeStillAlt:
        particle->nVelX = 0;
        particle->nVelY = 0;
        particle->bParam = emitter->pTarget->bFacing;
        break;

    case ParticleModeRandomDirectionAlt:
        particle->bParam = Mt19937RandRange2(0, 7);
        particle->dwSpeed = emitter->dwSpeed;
        particle->dwInitialSpeed = particle->dwSpeed;
        particle->nVelX = FixedMultiply(g_aDirection8Vectors[particle->bParam][0], particle->dwSpeed);
        particle->nVelY = FixedMultiply(g_aDirection8Vectors[particle->bParam][1], particle->dwSpeed);
        break;

    case ParticleModeRandomVelocity:
        particle->nVelX = Mt19937RandRange(emitter->abVelRange[0] << 8, emitter->abVelRange[1] << 8) * 4;
        particle->nVelY = -(Mt19937RandRange(emitter->abVelRange[2] << 12, emitter->abVelRange[3] << 12) * 2);
        particle->wParam46 = emitter->wParam38;
        particle->bMode = ParticleModeRandomVelocity;
        break;
    }
}
