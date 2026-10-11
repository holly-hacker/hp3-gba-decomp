#include "types.h"
#include "math.h"
#include "graphics/graphics.h"
#include "actor.h"

// Writes the vector of length `speed` in a direction: a 16-way direction or a
// Direction4 when actorFlags selects one, otherwise a Direction.
void GetDirectionVector(FixedPoint *out, u32 actorFlags, u32 direction, s32 speed)
{
    if (actorFlags & ActorFlagSixteenWayDirections) {
        out->x = FixedMultiply(g_aDirection16Vectors[direction][0], speed);
        out->y = FixedMultiply(g_aDirection16Vectors[direction][1], speed);
    }
    else if (actorFlags & ActorFlagFourWayDirections_candidate) {
        out->x = FixedMultiply(g_aDirection4Vectors[direction][0], speed);
        out->y = FixedMultiply(g_aDirection4Vectors[direction][1], speed);
    }
    else {
        out->x = FixedMultiply(g_aDirection8Vectors[direction][0], speed);
        out->y = FixedMultiply(g_aDirection8Vectors[direction][1], speed);
    }
}
