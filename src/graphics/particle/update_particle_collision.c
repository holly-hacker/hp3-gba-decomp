#include "types.h"
#include "graphics/graphics.h"
#include "overworld/terrain.h"

// Also sets the OAM priority from bits 6-7 of the collision byte, plus 1.
u8 UpdateParticleCollision(Particle *particle)
{
    u8 collision;

    collision = GetCollisionTypeAtPixel_candidate(
        (PixelPoint){ (s16)(particle->nDrawX >> 16), (s16)(particle->nDrawY >> 16) });
    particle->oam.priority = (collision >> 6) + 1;
    return collision;
}
