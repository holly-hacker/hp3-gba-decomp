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

extern OverworldControlState g_OverworldControlState;

extern Actor *g_pPlayerActor;
// The two party followers' actors; NULL while the slot is empty.
extern Actor *g_pFollowerActor0;
extern Actor *g_pFollowerActor1;
// Character ids of the leader and the two follower slots.
extern u8 g_bPartyCharId0;
extern u8 g_bPartyCharId1;
extern u8 g_bPartyCharId2;

// Spawns the effect actor of field spell `spell` (an Actor.bFighterIndex value) at
// the caster's anchor 0.
extern void SpawnFieldSpellEffect_candidate(Actor *caster, u8 spell);
// Starts the cast of the selected field spell (action state 0x13).
extern void StartFieldSpellCast(Actor *actor);
// Sets (1) or clears (0) ActorFlagVisible on g_pPlayerShadowActor_candidate.
extern void SetPlayerShadowVisible(u32 visible);
extern void TickHeldRewardActor(Actor *actor);  // pfnTick of the item TickActorReceiveReward spawns
extern Actor *g_pPlayerShadowActor_candidate;
// Index into the 9-entry field spell table at 0x08060BAC: {u32 spell,
// u8 FighterType, u8 minimum bKnownSpellCount}. Flipendo, Lumos and Diffindo
// for Harry, Flipendo, Reparo and Glacius for Hermione, Flipendo, Alohomora
// and Spongify for Ron; Diffindo and Spongify need 5 known spells, Glacius 6.
// CyclePartyLeaderSelection_candidate steps it; it is saved with the party.
extern u8 g_bSelectedFieldSpell;
// HUD actors, cleared by ResetPartyState and freed by sub_08024BD4.
extern Actor *g_pFieldSpellNameActor;       // selected spell's name text (sub_08023A2C)
extern Actor *g_pMapNameTextActor;          // room name text (ShowMapNamePopup)
extern Actor *g_pFieldSpellPortraitActor;   // face portrait of the spell's character (sub_08023A2C)
extern Actor *g_pMapNamePopupActor;         // 240x16 bar sprite behind the room name (ShowMapNamePopup)
extern u32 g_dwUnk030033A8;  // zeroed by ResetPartyState and sub_080248E8; no reader found



extern u8 g_bControlSlotTicks_candidate;
// Updates g_CameraPosition_candidate from the followed actor and streams BG
// tiles on demand as it crosses tile boundaries.
extern void UpdateOverworldCamera_candidate(u32 mode);
// Set by the room chain runner while it processes a chain; consumed (cleared)
// once per frame by HandleOverworldPauseMenuInput.
extern u32 g_dwRoomChainRanThisFrame_candidate;
// 1 while RestoreRoomActorState respawns the room's saved actors, and set
// when the overworld pushes a pause menu; the room actor constructed by
// sub_08044C00 and its callbacks branch on it.
extern u8 g_bRestoringRoomActors_candidate;

// Nonzero blocks the overworld Start/Select menus (SetPauseMenuLocked).
extern u32 g_dwPauseMenuLocked;
// Frames until Start/Select may open a menu again; 4 after room init and
// each menu open, counted down by UpdateOverworld.
extern u32 g_dwPauseMenuCooldown;


// Overworld teardown helpers called by ExitOverworldScreen.
extern void FreeRoomSharedTileset(void);
