#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "particles.h"

// BSOP_WaitForCasterTimedMove tick: once the caster's timed move has finished,
// resumes the script in the same frame.
void WaitForCasterTimedMoveTick(Actor *actor)
{
    TickParticleEmitters();
    ProcessActorFlagBehaviors(actor);
    if (g_pFightState->pFighters[g_effectStaging.bCasterIndex].pActor->wTimedMoveTicks == 0)
    {
        actor->pfnTick = InterpretActorScript;
        actor->pfnTick(actor);
    }
}
