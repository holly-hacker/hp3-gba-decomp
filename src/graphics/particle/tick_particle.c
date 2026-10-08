#include "types.h"
#include "graphics/graphics.h"
#include "game/game_modes.h"

// Collision type 1 frees the particle. A full OAM queue sets
// g_bParticleSpawnBlocked.
s8 TickParticle(Particle *particle)
{
    s32 result;
    u8 collision;

    result = 0;
    if (--particle->sLife == -1)
        goto free;

    switch (particle->bMode) {
    case ParticleModeStill:
        TickParticleStill(particle);
        break;
    case ParticleModeDirectional:
        TickParticleDirectional(particle);
        break;
    case ParticleModeRandomDirection:
        TickParticleMoving(particle);
        break;
    case ParticleModeRandomVelocity:
        TickParticleWithGravity(particle);
        break;
    default:
        TickParticleMoving(particle);
        break;
    }
    particle->nDrawX = particle->nX;
    particle->nDrawY = particle->nY;

    if (!(particle->wFlags & ParticleEmitterFlagNoCollision))
        collision = UpdateParticleCollision(particle);
    else
        collision = 0;

    if (!(g_dwGameModeFlags & 0x440000)) {
        if (collision == 1)
            goto free;
        result = DrawParticle(particle);
        if (result == -1) {
            g_bParticleSpawnBlocked = 1;
            return result;
        }
    }
    return result;

free:
    FreeParticle(particle);
    return result;
}
