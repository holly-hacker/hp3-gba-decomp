#pragma once

#include "types.h"
#include "actor.h"

// Total record length in bytes, opcode word included, per opcode.
extern const u8 g_abRoomScriptOpcodeLengths[93];  // ROM 0x0805EB34

// SpawnScriptEffectActor kinds (Actor.bRoomActorKind_candidate), indexing
// g_apfnScriptEffectActorTicks.
enum {
    ScriptEffectKind_CameraCutaway = 0,
    ScriptEffectKind_DelayedRespawn = 1,
    ScriptEffectKind_Count
};

extern void (*const g_apfnScriptEffectActorTicks[ScriptEffectKind_Count])(Actor *actor);

extern void TickCameraCutawayActor(Actor *actor);
extern void TickDelayedRespawnActor(Actor *actor);
