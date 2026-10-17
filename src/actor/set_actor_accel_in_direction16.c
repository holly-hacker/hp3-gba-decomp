#include "types.h"
#include "math.h"
#include "particles.h"
#include "actor.h"

// Accelerates the actor along one of 16 directions, clockwise from up.
void SetActorAccelInDirection16(Actor *actor, u32 direction, s32 magnitude)
{
    actor->accel.x = FixedMultiply(g_aDirection16Vectors[direction][0], magnitude);
    actor->accel.y = FixedMultiply(g_aDirection16Vectors[direction][1], magnitude);
}
