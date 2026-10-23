#include "types.h"
#include "actor.h"
#include "event_actors.h"
#include "overworld/room_script.h"

Actor *SpawnScriptEffectActor(u32 kind)
{
    Actor *actor = AllocActorOfType(RoomActorType_ScriptEffect);

    actor->dwFlags = ActorFlagHasTickLogic | ActorFlagTickHandlerSuspendsMovement;
    actor->bKind = kind;
    SetActorActionState(actor, 0);
    actor->pfnTick = g_apfnScriptEffectActorTicks[kind];
    return actor;
}
