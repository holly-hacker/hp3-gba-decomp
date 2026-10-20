#include "types.h"
#include "event_actors.h"

void (*const g_apfnScriptEffectActorTicks[ScriptEffectKind_Count])(Actor *actor) = {
    [ScriptEffectKind_CameraCutaway] = TickCameraCutawayActor,
    [ScriptEffectKind_DelayedRespawn] = TickDelayedRespawnActor,
};
