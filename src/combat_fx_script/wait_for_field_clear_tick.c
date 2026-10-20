#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "particles.h"

// BSOP_WaitForFieldClear tick: once the actor's move has finished, resumes the
// script in the same frame.
void WaitForFieldClearTick(Actor *actor)
{
    TickParticleEmitters();
    actor->dwStateTimer++;
    ProcessActorFlagBehaviors(actor);
    if (actor->wMoveDuration == 0 && actor->dwStateTimer != 0)
    {
        actor->pfnTick = InterpretActorScript;
        actor->dwStateTimer = 0;
        actor->pfnTick(actor);
    }
}
