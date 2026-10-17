#include "types.h"
#include "particles.h"

void ReleaseParticle(Particle *particle)
{
    FreeParticle(particle);
}
