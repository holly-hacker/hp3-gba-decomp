#pragma once

#include "types.h"
#include "actor.h"

// Controllable-character slots: each 16-byte entry starts with the Actor the
// player steers; only slot 0 is ever populated.
typedef struct OverworldControlSlot {
    Actor *pActor;
    u8 abUnused[12];  // no access found
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
// The player's collision callback: touching a prop actor (RoomActorType_ScriptedTrigger) with
// bPropBlocksPlayer_candidate set and bRoomActorArg67_candidate 0xFF stops the player in place,
// unless casting (action state 0x13).
extern void HandlePlayerPropCollision(Actor *self, Actor *other);
extern void RefreshFieldSpellHud(Actor *iconActor);
// Marks the actor, its linked actor and its shadow for destruction.
extern void DestroyPartyMemberActor(Actor *actor);

