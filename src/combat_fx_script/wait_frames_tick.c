#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "particles.h"

// BSOP_WaitFrames tick: resumes the script once wActionVariant frames have passed.
void WaitFramesTick(Actor *actor)
{
    TickParticleEmitters();
    if (++actor->dwStateTimer == actor->wActionVariant)
        actor->pfnTick = InterpretActorScript;
    ProcessActorFlagBehaviors(actor);
}
