#pragma once

#include "types.h"
#include "battle.h"
#include "encounters.h"

// Wandering-monster overworld state (see docs/formats/encounters.md).
// Touching a wandering monster records its encounter id and kind here;
// every fifth touch respawns replacements via TrySpawnWanderingMonster
// (see HandleWanderingMonsterTouch). Cleared on room load by
// SpawnOverworldMonsterEncounters below.
extern u8 g_bTouchedMonsterRecordCount;
extern u8 g_abTouchedMonsterRecords[20];
extern Object *g_pTouchedWanderingMonster;

// 8-byte wandering-monster spawn-position record, two words.
// Only the low halves reach SpawnWanderingMonsterObject;
// FindWanderingMonsterSpawnPosition fills both words.
typedef struct SpawnPosition {
    u32 x;
    u32 y;
} SpawnPosition;

// Room load: spawn each kind's level-table count (offsets 0x74-0x76) of
// wandering monsters for encounter id (level-table offset 0x77), picking
// each spawn's random variant up front. See docs/formats/encounters.md.
void SpawnOverworldMonsterEncounters(u32 countA, u32 countB, u32 countC, u32 encounterId);
// Collision-type table lookup by encounter kind, selecting the spawn
// terrain for that kind.
u32 GetEncounterKindTerrainType(u32 kind);
// Find a valid spawn position for one monster, recording it in the
// placed-position buffer for overlap checks. Returns 0 after 200 failed
// attempts.
s32 FindWanderingMonsterSpawnPosition(u32 *pOutPos, u32 terrainType, SpawnPosition *pPlacedPositions, u32 placedCount);
// Strongest-damage monster id among one variant cell's slots 0-2.
u32 PickMaxDamageMonster(const u8 *pSlots);
// Create one wandering-monster object.
void SpawnWanderingMonsterObject(u8 monsterId, u16 x, u16 y, u8 encounterId, u8 variant, u8 kind);

// Controllable-character slots: each 16-byte entry starts with the Object the
// player steers; only slot 0 is ever populated.
typedef struct OverworldControlSlot {
    Object *pObject;
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

extern Object *g_pPlayerObject;
// The two party followers' objects; NULL while the slot is empty.
extern Object *g_pFollowerObject0;
extern Object *g_pFollowerObject1;
// Character ids of the leader and the two follower slots.
extern u8 g_bPartyCharId0;
extern u8 g_bPartyCharId1;
extern u8 g_bPartyCharId2;

// Per-slot scripted camera effect, started by room script opcodes 0x10
// (QueueTileObjectMove: pan the camera focus to an object) and 0x12
// (SetAllQueuedMoveParams: shake). One 0x2C-byte record per control slot,
// ticked by TickCameraFocus_candidate. See docs/memory-map/frame_systems.md.
typedef struct CameraEffect {
    Object *pTarget;           // 0x00, pan target
    u32 nSavedVelX;            // 0x04, the controlled object's velocity, restored when the pan ends
    u32 nSavedVelY;            // 0x08
    u8 pad_0C[0x08];           // -> 0x14
    s32 nStep;                 // 0x14, pan speed; shake amplitude (posX << 16) in state 3
    u32 dwFramesLeft;          // 0x18, shake duration in frames
    u32 dwRunForever;          // 0x1C, shake: nonzero when the duration operand was 0
    u16 wCounter;              // 0x20, pan: frames to wait; shake: 0/1 toggle
    u8 pad_22;                 // -> 0x23
    u8 bRespawnRow;            // 0x23, first argument to RespawnRowAndRunChain_candidate
    u8 bChainRow;              // 0x24, second argument to RespawnRowAndRunChain_candidate
    u8 bState;                 // 0x25, 0 = idle, 1 = pan, 3 = shake
    u8 bSavedActionSubState;   // 0x26, controlled object's bActionSubState when the pan began
    u8 bChainRan;              // 0x27, set once the pan's chain has run
    u32 dwResumeScript;        // 0x28, nonzero: resume the yielded room script when the pan ends
} CameraEffect;
extern CameraEffect g_aCameraEffects_candidate[];

// Per-slot camera focus point: what UpdateOverworldCamera_candidate centres the
// screen on (16.16 world coordinates). Follows pTarget unless wPinned is nonzero.
typedef struct CameraFocusSlot {
    s32 nX;                    // 0x00
    s32 nY;                    // 0x04
    u8 pad_08[0x10];           // -> 0x18
    s32 nLatchedX;             // 0x18, copy of the focus point; see SetCameraFollowTarget_candidate
    s32 nLatchedY;             // 0x1C
    u8 pad_20[0x10];           // -> 0x30
    Object *pTarget;           // 0x30, object the focus follows
    u16 wPinned;               // 0x34, 0 = follow pTarget every frame, 1 = hold
    u8 pad_36[0x02];           // -> 0x38
} CameraFocusSlot;
extern CameraFocusSlot g_aCameraFocusSlots[];

extern u8 g_bControlSlotTicks_candidate;
extern void TickOverworldBeforeObjects_candidate(void);
// Ticks slot's camera focus: follows the target object, or runs the active pan/shake
// effect and its completion chain.
extern void TickCameraFocus_candidate(u8 slot);
// Updates g_CameraPosition_candidate from the followed object and streams BG
// tiles on demand as it crosses tile boundaries.
extern void UpdateOverworldCamera_candidate(u32 mode);
// Counts down the room's timed tile-change entries and applies each one when it expires.
extern void TickRoomTileAnimations_candidate(void);
extern void HandleOverworldPauseMenuInput(void);
// Set by the room chain runner while it processes a chain; consumed (cleared)
// once per frame by HandleOverworldPauseMenuInput.
extern u32 g_dwRoomChainRanThisFrame_candidate;
extern u8 g_bUnk03005E18;
// Records wandering-monster touches and respawns replacements; see the
// wandering-monster notes above.
extern void HandleWanderingMonsterTouch(void);

// Nonzero blocks the overworld Start/Select menus (SetPauseMenuLocked).
extern u32 g_dwPauseMenuLocked;
// Frames until Start/Select may open a menu again; 4 after room init and
// each menu open, counted down by UpdateOverworld.
extern u32 g_dwPauseMenuCooldown;

// Multi-slot bookkeeping that only acts when the slot count exceeds 1.
// Always returns 0.
s32 TickOverworldControlSlots_candidate(void);
// Advances the Owl Care Kit's timers and need counters while walking around.
void TickOwlCareKitFromOverworld(void);

// Overworld teardown helpers called by ExitOverworldScreen.
extern void sub_08005D88(void);
extern void sub_0802DDAC(void);
extern void sub_0802B210(void);
extern void sub_0802B08C(void);
extern void sub_08024918(void);
extern void sub_08007AA8(u32 arg0);
extern void sub_080203CC(void);
