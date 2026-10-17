#pragma once

#include "types.h"
#include "camera.h"
#include "battle/battle.h"
#include "battle/encounters.h"

// Controllable-character slots: each 16-byte entry starts with the Actor the
// player steers; only slot 0 is ever populated.
typedef struct OverworldControlSlot {
    Actor *pActor;
    u8 aUnknown4[12];
} OverworldControlSlot;

typedef struct OverworldControlState {
    OverworldControlSlot aSlots[2];
    // Set to 1 by InitializeOverworld; no other writer found.
    u8 bSlotCount;
    // Active entry of aSlots.
    u8 bSlotIndex;
} OverworldControlState;

// Starts the cast of the selected field spell (action state 0x13).
extern void StartFieldSpellCast(Actor *actor);
// Sets (1) or clears (0) ActorFlagVisible on g_pPlayerShadowActor_candidate.
extern void SetPlayerShadowVisible(u32 visible);
extern void TickHeldRewardActor(Actor *actor);  // pfnTick of the item TickActorReceiveReward spawns

