#include "types.h"
#include "actor.h"

void SetActorScaleStep(Actor *actor, u32 step)
{
    SetActorAffineTransform(actor, g_adwActorScaleSteps[step], g_adwActorScaleSteps[step], 0, 3);
}
