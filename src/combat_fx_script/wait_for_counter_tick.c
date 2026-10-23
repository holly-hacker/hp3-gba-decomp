#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "particles.h"

// BSOP_WaitForCounter tick: resumes the script once the animation's event
// counter reaches wActionVariant, or once the animation has finished.
void WaitForCounterTick(Actor *actor)
{
    TickParticleEmitters();
    actor->dwStateTimer++;
    if (actor->anim.param.bEventMarker == actor->wActionVariant)
        actor->pfnTick = InterpretActorScript;
    if (actor->dwFlags & ActorFlagActionAnimDone)
        actor->pfnTick = InterpretActorScript;
    ProcessActorFlagBehaviors(actor);
}
